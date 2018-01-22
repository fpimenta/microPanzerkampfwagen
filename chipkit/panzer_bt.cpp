#include "Arduino.h"
#include "Servo.h"
#include <SoftwareSerial.h>

#define pinServo 40

#define bt_rx 12
#define bt_tx 13

// DC Motors
#define en1 1 // to set speed
#define en2 2
#define en3 3
#define en4 4
#define dc1_1 30 // to control the motors
#define dc1_2 31
#define dc2_1 32 
#define dc2_2 33
#define dc3_1 34 
#define dc3_2 35
#define dc4_1 36 
#define dc4_2 37

void set_direction(String dir); // a function to set direction
void set_speed(int pwr); // a function to set vehicle speed

Servo motor; // Creates a Servo object
SoftwareSerial BTSerial(bt_rx, bt_tx); // RX 12, TX 13

int r; // Holds the data sent by the application


void setup() {
    pinMode(en1, OUTPUT); // Each enable controls the speed for a motor
    pinMode(en2, OUTPUT);
    pinMode(en3, OUTPUT);
    pinMode(en4, OUTPUT);
    pinMode(dc1_1, OUTPUT); // dcx_1 and dcx_2 control motor x according to the table in the project description
    pinMode(dc1_2, OUTPUT);
    pinMode(dc2_1, OUTPUT);
    pinMode(dc2_2, OUTPUT);
    pinMode(dc3_1, OUTPUT);
    pinMode(dc3_2, OUTPUT);
    pinMode(dc4_1, OUTPUT);
    pinMode(dc4_2, OUTPUT);
    Serial.begin(9600); // Print to Serial monitor for debugging
    BTSerial.begin(9600); // Initiate communication with the bluetooth module
    motor.attach(pinServo); // Tells the library which pin is used for the servo. The pin must have PWM support
    set_speed(200); // Set initial speed to 200
}
 
void loop() {
   if (BTSerial.available()) {
    r = BTSerial.read(); // Gets the integer sent by the app
    Serial.println(r);
    if( r > -1 && r < 181) // If between 0 and 180, turn the servo to that angle
       motor.write(r);
    if( r == 200){ // Between 200 and 205 change speed accordingly
      set_speed(50);
    }        
    if( r == 201){
      set_speed(80);
    }     
    if( r == 202){
      set_speed(110);
    }     
    if( r == 203){
      set_speed(160);
    }     
    if( r == 204){
      set_speed(200);  
    }    
    if( r == 205){
      set_speed(255);   
    } 
    if( r == 183){        // Between 181 and 186 is to change direction
      set_direction("front");   
    }
    if( r == 184){
      set_direction("back");   
    }
    if( r == 182){
      set_direction("right");   
    } 
    if( r == 181){
      set_direction("left");   
    }
    if( r == 186){
      set_direction("stop");   
    }         
  }
        
}        
void set_direction(String dir){ // To change direction we turn on/off certain motors
    if( dir == "front"){
      digitalWrite(dc1_1, HIGH);
      digitalWrite(dc1_2, LOW);
      digitalWrite(dc2_1, HIGH);
      digitalWrite(dc2_2, LOW);
      digitalWrite(dc3_1, HIGH);
      digitalWrite(dc3_2, LOW);
      digitalWrite(dc4_1, HIGH);
      digitalWrite(dc4_2, LOW);
    }
    if( dir == "back"){
      digitalWrite(dc1_1, LOW);
      digitalWrite(dc1_2, HIGH);
      digitalWrite(dc2_1, LOW);
      digitalWrite(dc2_2, HIGH);
      digitalWrite(dc3_1, LOW);
      digitalWrite(dc3_2, HIGH);
      digitalWrite(dc4_1, LOW);
      digitalWrite(dc4_2, HIGH);
    }
    if( dir == "right"){
      digitalWrite(dc1_1, HIGH);
      digitalWrite(dc1_2, LOW);
      digitalWrite(dc2_1, HIGH);
      digitalWrite(dc2_2, LOW);
      digitalWrite(dc3_1, LOW);
      digitalWrite(dc3_2, LOW);
      digitalWrite(dc4_1, LOW);
      digitalWrite(dc4_2, LOW);
    }
    if( dir == "left"){
      digitalWrite(dc1_1, LOW);
      digitalWrite(dc1_2, LOW);
      digitalWrite(dc2_1, LOW);
      digitalWrite(dc2_2, LOW);
      digitalWrite(dc3_1, HIGH);
      digitalWrite(dc3_2, LOW);
      digitalWrite(dc4_1, HIGH);
      digitalWrite(dc4_2, LOW);
    }
    if( dir == "stop"){
      digitalWrite(dc1_1, LOW);
      digitalWrite(dc1_2, LOW);
      digitalWrite(dc2_1, LOW);
      digitalWrite(dc2_2, LOW);
      digitalWrite(dc3_1, LOW);
      digitalWrite(dc3_2, LOW);
      digitalWrite(dc4_1, LOW);
      digitalWrite(dc4_2, LOW);
    }
}
void set_speed(int pwr){ // The speed is changed by sending a PWM modulated signal to each motor's enable
     analogWrite(en1, pwr);
     analogWrite(en2, pwr);
     analogWrite(en3, pwr);
     analogWrite(en4, pwr);    
}
