#include "Arduino.h"
#include "Servo.h"
#include <SoftwareSerial.h>

#define pinServo 3

Servo motor;
SoftwareSerial BTSerial(12, 13); // RX 12, TX 13
int r;
void setup() {
    Serial.begin(9600);
    BTSerial.begin(9600);
    motor.attach(pinServo);
}
 
void loop() {
   if (BTSerial.available()) {
    r = BTSerial.read();
    Serial.println(r);
    if( r > -1 && r < 181){
       motor.write(r);
    }
  }
        
        

}
