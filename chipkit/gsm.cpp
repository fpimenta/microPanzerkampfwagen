/*


*/

#include <TinyGPS++.h>

TinyGPSPlus gps; // This library parses NMEA data
char answer[120];
 
void setup() {
 Serial1.begin(9600);
 Serial.begin(9600);
 delay(100);
 pinMode(2,OUTPUT);
 pinMode(3,OUTPUT);
 sendAT("AT", "OK", 1000,0); // Check connection
 sendAT("AT+CPIN?", "OK", 1000,0); // Unlock SIM
  while ( sendAT("AT+CREG?", "+CREG: 0,1", 1000,0) == 0 ) // Loops until it finds gsm signal
  {
    delay(100);
  }
  Serial.println("Connected.");
  sendAT("AT+CLIP=1\r", "OK", 1000,0); // Activate call identification
  sendAT("AT+CMGF=1\r", "OK", 1000,0); // Activate SMS
  sendAT("AT+CGPSPWR=1\r", "OK", 1000,0); // Power up the GPS
  digitalWrite(3,HIGH); // Ready to make calls and send messages
}
 
void loop() {
  char r = 0;
 // Read a char from the Serial monitor
 if (Serial.available() > 0){
  r = Serial.read();
 }
 if(r == 'c' || digitalRead(29) == HIGH){ // Make a call. The number is hardcoded for simplification
  Serial.println("Making a call");
  sendAT("ATD968174036;", "OK", 1000,0);
 }
 if(r == 's'  || digitalRead(30) == HIGH){ // Send a message with the position data
  char sms[60] ; 
  sprintf(sms, "Lat: %f\nLon: %f\nAlt:%f\x1A \r\n", gps.location.lat(),gps.location.lng(),gps.altitude.meters());
  char aux_str[120];
  Serial.println("Sending SMS...");
 
  sprintf(aux_str, "AT+CMGS=\"968174036\"", strlen(sms)); // Number to send SMS
    //SMS text
    if (sendAT(aux_str, ">", 10000,0) == 1)
    {
      sendAT(sms, "OK", 10000,0);
    }
    Serial.println("SMS sent");
   
 }
 if(r == 'g' || digitalRead(31) == HIGH){ // Loops until it finds gps signal, after that it just updates the data
    Serial.println("Finding GPS");
    digitalWrite(2, HIGH);
    while ( sendAT("AT+CGPSSTATUS?", "+CGPSSTATUS: Location 3D Fix", 1000,0) == 0 ) // It usually takes a lot to find signal
    {
    delay(5000);
    }
    sendAT("AT+CGPSOUT\r", "OK",1000,1); // Asks for position data in NMEA format
  
 
    Serial.println(gps.location.lat(),6);
    Serial.println(gps.location.lng(), 6);
    Serial.println(gps.altitude.meters());
    Serial.println(gps.speed.kmph());
    delay(1000);
    digitalWrite(2,LOW);
 }
 
}
  
int sendAT(String ATcommand, char* return_code, unsigned int time, int loc)
{
 
  int x = 0;
  bool b = 0;
 
  unsigned long old;
 
  memset(answer, '\0', 100); // Inicializa el string
  delay(100);
  while ( Serial1.available() > 0) Serial1.read(); // Limpia el buffer de entrada
  Serial1.println(ATcommand); // Envia el comando AT
  x = 0;
  old = millis();
  // Espera una respuesta
  do {
    // si hay datos el buffer de entrada del UART lee y comprueba la respuesta
    if (Serial1.available() != 0)
    {
       answer[x] = Serial1.read();
       if(loc)
       gps.encode(answer[x]);
       x++;
      // Comprueba si la respuesta es correcta
      if (strstr(answer, return_code) != NULL)
      {
        b = 1;
      }
    }
  }
  // Espera hasta tener una respuesta
  while ((b == 0) && ((millis() - old) < time));
  Serial.println(answer);
 
  return b;
 
  }
