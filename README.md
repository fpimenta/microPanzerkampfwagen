# microPanzerkampfwagen

In the scope of the Computers discipline we (@fpimenta @ ) had to develop a final project to apply all the knowledge learned during the course. We developed a chipkit UNO32 based Panzer, connected trough bluetooth to an app we developed using MIT App Inventor. The robot also informs it's location via GPS/GSM module.

## The Robot
We used a car kit we had laying around, similar to the one in the image

![car kit](/images/robot_car_kit.jpeg)

We powered the car with 3x 18650 batteries and the CHIPkits with a 5V powerbank. Overall, excluding parts used for fixing everything and the chassis itself and some additional circuitry (relay, switches,...), the materials consisted in:

2x L298n motor drivers
4x DC brush motors
1x Servo motor
2x Chipkit UNO32
1x 5V Powerbank
1x HC-06 Bluetooth Module
1x High Voltage Converter
1x SIM808 GSM/GPS module

### Motors
We used 4x DC brushed motors, so to control them we opted for a L298N controller. The controller came out very easy to use. 
![l298n](/images/l298n.jpg)

1/14- + Motor Pins
2/13- - Motor Pins
3- We leaved this jumper as the power we were supplying was around +12V DC
4- + 12V DC
5- GND
6- + 5V Output
7/12 - This is the enable pin for each motor. By giving a PWM signal to it we can control the motors speed.
8/9 - This pins are used to control the direction of movement of the motor 1.
10/11 - This pins are used to controll the direction of movement of the motor 2.

The direction was given by the Android app and by turning off and on certain motors, we made the robot go the wanted direction

### Servo
The Servo was used to controlled the tank gun direction. The input was used by a slider in the Android app.
### Tank Gun

### Bluetooth

## The GPS and GPS

### GPS

### GSM


## The App
