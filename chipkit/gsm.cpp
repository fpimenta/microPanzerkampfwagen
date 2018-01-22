#include <TinyGPS++.h>

TinyGPSPlus gps; // This library parses NMEA data, here we create and object of the TinyGPSPlus class

char answer[120]; // Holds the returned data
 
void setup() {
 Serial1.begin(9600); // The chipkit provides two Serial interfaces in hardware,  one will communicate with the computer via USB and the other will communicate with the SIM808
 Serial.begin(9600);
 pinMode(29,INPUT); // Three buttons to interface with the chipkit while not connected to the computer
 pinMode(30,INPUT);
 pinMode(31,INPUT);
 pinMode(2,OUTPUT); // Two LEDs will help to know the program state whenever the chipkit is not connected to the computer
 pinMode(3,OUTPUT);
 sendAT("AT", "OK", 1000,0); // Check connection
 sendAT("AT+CPIN?", "OK", 1000,0); // Unlock SIM
 while ( sendAT("AT+CREG?", "+CREG: 0,1", 1000,0) == 0 ) // Loops until it finds gsm signal
  delay(100);
 digitalWrite(3,HIGH); // Ready to make calls and send messages, light up LED for one second
 Serial.println("Connected.");
 sendAT("AT+CLIP=1\r", "OK", 1000,0); // Activate call identification
 sendAT("AT+CMGF=1\r", "OK", 1000,0); // Activate SMS
 sendAT("AT+CGPSPWR=1\r", "OK", 1000,0); // Power up the GPS
 delay(1000);
 digitalWrite(3,LoW);
}
 
void loop() {
  char r = 0;
 // Read a char from the Serial monitor
 if (Serial.available() > 0){
  r = Serial.read();
 }
 if(r == 'c' || digitalRead(29) == HIGH){ // Make a call. The number is hardcoded for simplification
  Serial.println("Making a call");
  digitalWrite(3,HIGH);
  sendAT("ATDXXXXXXXXX;", "OK", 1000,0);
  digitalWrite(3,LOW);
 }
 if(r == 's'  || digitalRead(30) == HIGH){ // Send a message with the position data -in this case, latitude, longitude and altitude
  char sms[60]; // Holds the data to send
  sprintf(sms, "Lat: %f\nLon: %f\nAlt:%f\x1A \r\n", gps.location.lat(),gps.location.lng(),gps.altitude.meters());
  char aux_str[120];
  Serial.println("Sending SMS...");
  digitalWrite(3,HIGH);
  sprintf(aux_str, "AT+CMGS=\"XXXXXXXXX\"", strlen(sms)); // Number to send SMS
  //AT commands to send the SMS
  if (sendAT(aux_str, ">", 10000,0) == 1)
      sendAT(sms, "OK", 10000,0);
    
  Serial.println("SMS sent");
  digitalWrite(3,LOW); 
 }
 if(r == 'g' || digitalRead(31) == HIGH){ // Loops until it finds gps signal, after that it just updates the data
   Serial.println("Finding GPS");
   digitalWrite(2, HIGH);
  
   while ( sendAT("AT+CGPSSTATUS?", "+CGPSSTATUS: Location 3D Fix", 1000,0) == 0 ) // It usually takes a lot to find signal
    delay(5000);
    
   sendAT("AT+CGPSOUT\r", "OK",1000,1); // Asks for position data in NMEA format

    Serial.println(gps.location.lat(),6); // Prints some data for debugging
    Serial.println(gps.location.lng(), 6);
    Serial.println(gps.altitude.meters());
    Serial.println(gps.speed.kmph());
    delay(1000);
    digitalWrite(2,LOW);
 }
 
}

/*
The main part of the program was sending AT commands and listen to the responses, so I created a function to do just that.
The functions expects a String with the required AT command (with a \r at the end if that's needed for that particular command),
a vector of chars that holds the correct return code, an unsigned int that holds the maximum time the command is suposed to take
executing and a boolean to make sure only the command that returns position data is then decoded by the TinyGPS library
*/

int sendAT(String ATcommand, char* return_code, unsigned int time, bool loc)
{
 
  int x = 0;
  bool b = 0;
  unsigned long old;
 
  answer[119] = '\0'; // Terminate string
  
  while ( Serial1.available() > 0) Serial1.read(); // Empty the data buffer
  Serial1.println(ATcommand); // Send AT command. Adds the required \n at the end.
  x = 0;
 
  old = millis();
  
  do {
    
    if (Serial1.available() != 0)
    {
      answer[x] = Serial1.read();
       
      if(loc)
      gps.encode(answer[x]);
       
      x++;
      
      if (strstr(answer, return_code) != NULL)
        b = 1;
    }
  }
 
  while ((b == 0) && ((millis() - old) < time));
  Serial.println(answer);
 
  return b;
 
  }
