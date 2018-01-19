 #include <DFRobot_sim808.h>

 #define PHONE_NUMBER "938431332"  
 
  DFRobot_SIM808 sim808(&Serial);
  
  int ini = 0;
  
  void setup() {
    //mySerial.begin(9600);
    Serial.begin(9600);

    //******** Initialize sim808 module *************
    while(!sim808.init()) {
        delay(1000);
        Serial.print("Sim808 init error\r\n");
        
    }

    //************* Turn on the GPS power************
    if( sim808.attachGPS())
        Serial.println("Open the GPS power success");
   
 else
        Serial.println("Open the GPS power failure");

  }
  void loop() {
    

     if( millis() - ini > 60000){
      ini = millis();
     
     if (sim808.getGPS()) {
          Serial.print("latitude :");
          Serial.println(sim808.GPSdata.lat);
          Serial.print("longitude :");
          Serial.println(sim808.GPSdata.lon);
          Serial.print("speed_kph :");
          Serial.println(sim808.GPSdata.speed_kph);
          Serial.print("heading :");
          Serial.println(sim808.GPSdata.heading);
          Serial.println();
          char data[100];
          sprintf(data, "lat: %f long: %f speed: %f", sim808.GPSdata.lat, sim808.GPSdata.lon,sim808.GPSdata.speed_kph);
           sim808.sendSMS(PHONE_NUMBER, data);
         
    }

  }

  }
