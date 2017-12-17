# microPanzerkampfwagen

In the scope of the Computers discipline we ([Francisco Pimenta](https://github.com/fpimenta) and [João Morais] ) had to develop a final project to apply all the knowledge learned during the course. We developed a chipkit UNO32 based Panzer, connected trough bluetooth to an app we developed using MIT App Inventor. The robot also informs it's GPS location via GSM, by posting it to a server mounted on Heroku and sending an SMS when requested.

## The Robot
We used a car kit we had laying around, similar to the one in the image

![car kit](/images/robot_car_kit.jpeg)

We powered the car with 3x 18650 batteries and the CHIPkits with a 5V powerbank. Overall, excluding parts used for fixing everything and the chassis itself and some additional circuitry (relay, switches,...), the materials consisted in:

**2x L298n motor drivers<br>
4x DC brush motors<br>
1x Servo motor<br>
2x Chipkit UNO32<br>
1x 5V Powerbank<br>
1x HC-06 Bluetooth Module<br>
1x High Voltage Converter<br>
1x SIM808 GSM/GPS module**<br>

### Motors
We used 4x DC brushed motors, so to control them we opted for a L298N controller. The controller came out very easy to use. 
![l298n](/images/l298n.jpg)

**1/14-** + Motor Pins<br>
**2/13-**- Motor Pins<br>
**3-** We leaved this jumper as the power we were supplying was around +12V DC<br>
**4-** + 12V DC<br>
**5-** GND<br>
**6-** + 5V Output<br>
**7/12-** This is the enable pin for each motor. By giving a PWM signal to it we can control the motors speed.<br>
**8/9-** This pins are used to control the direction of movement of the motor 1.<br>
**10/11-** This pins are used to controll the direction of movement of the motor 2.<br>

|         | IN1  | IN2  |
|---------|------|------|
| BRAKE   | HIGH | HIGH |   
| FRONT   | HIGH | LOW  |   
| BACK    | LOW  | BACK |  
| NEUTRAL | LOW  | LOW  |  

The direction was given by the Android app and by turning off and on certain motors, we made the robot go the wanted direction

### Servo
The Servo was used to controlled the tank gun direction. The input was used by a slider in the Android app which sended to the chipKit an integer between 0 and 180, which corresponded to the angle to turn the servo.
### Tank Gun

### Bluetooth

## The GPS and GPS

### GPS

### GSM


## The App
The course was about microcontrollers, so we didn't want to spend much time writing the application, so we used the **MIT App Inventor** which lets you easily develop an Android app by dragging and dropping blocks of code, similar to **Scratch**.
We made a simple user interface with some arrows like a typical console controller and a slider to control the angle of the tank gun. We also added two buttons to connect/disconnect with the **HC-06** bluetooth module. To keep things simple, the only thing the app sends the robot is a 1 byte number [0-255]. The numbers between 0-180 are seen by the robot as the angle to turn the servo and the following numbers are used to tell the robot where to go or what to do (181 turn left, 185 shoot, etc). This is not the most transparent approach but is the most easy and minimal, keeping the microcontroller code simple and small.

## The Server
Using Heroku, we created a simple server using PHP and PostGreSQL to receive the data from the GPS and store it online. Basically, the server retrieves the data that is sent to it via a HTTP POST request and then stores it in a database, using a simples SQL query. This data can be then acessed in browser or in the app.
