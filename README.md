# microPanzerkampfwagen

In the scope of the Computers discipline I had to develop a final project to apply all the knowledge learned during the course. I developed a chipkit UNO32 based Panzer, connected trough bluetooth to an app developed using MIT App Inventor. The robot also informs it's GPS location via GSM, sending an SMS when requested. 

## The Robot
I used a car kit I had laying around, similar to the one in the image

![car kit](/images/robot_car_kit.jpeg)

The car and ChipKit were powered with 3x 18650 batteries. Overall, excluding parts used for fixing everything, the chassis itself and some additional circuitry (leds, switches,...), the materials consisted in:

**2x L298n motor drivers<br>
4x DC brush motors<br>
1x Servo motor<br>
2x Chipkit UNO32<br>
1x 5V Powerbank<br>
1x HC-06 Bluetooth Module<br>
1x High Voltage Converter<br>
1x SIM808 GSM/GPS module**<br>

### Motors
I used 4x DC brushed motors, so to control them I opted for two L298N controllers. The controllers came out very easy to use. 
![l298n](/images/l298n.jpg)

**1/14-** + Motor Pins<br>
**2/13-**- Motor Pins<br>
**3-** Leave this jumper if the voltage you are supplying is around +12V DC<br>
**4-** + 12V DC<br>
**5-** GND<br>
**6-** + 5V Output<br>
**7/12-** This is the enable pin for each motor. By giving a PWM signal to it we can control the motors speed.<br>
**8/9-** This pins are used to control the direction of movement of the motor 1.<br>
**10/11-** This pins are used to control the direction of movement of the motor 2.<br>

|         | IN1  | IN2  |  EN  |
|---------|------|------|------|
| BRAKE   | HIGH | HIGH | 1-255|
| FRONT   | HIGH | LOW  | 1-255|
| BACK    | LOW  | BACK | 1-255|
| NEUTRAL | x    |  x   |   0  |

The direction was given by the Android app and by turning off and on certain motors, the robot goes the wanted direction
Also, there are 5 speed levels which could be changed within the app.

### Servo
The Servo was used to control the tank gun direction. The input was given by a slider in the Android app which sends the chipKit an integer between 0 and 180, which corresponded directly to the angle to turn the servo.
The position was controlled by a PWM signal with 50Hz and a particular duty cicle. To generate it I used the [Servo](https://www.arduino.cc/en/Reference/Servo) library.

### Tank Gun

Of course, the Panzer wouldn't be complete if it wasn't capable of firing ammo. While not currently able to, I plan to add a cannon similar to [this](https://www.youtube.com/watch?v=QGj8xMDRSQ0) one. The ignition will be given by a [high voltage generator](https://pt.aliexpress.com/item/3-6V-High-Pressure-Generator-Module-Igniter-1-5A-Output-Voltage-20KV-20000KV-Boost-Step-up/32803789310.html) like this one controlled by a digital pin via a relay.

### Bluetooth

To control the tank via an Android app, I used bluetooth, making use of a bluetooth module (HC-06) to communicate with our phone. The communication between the chipKIT and the HC-06 was done using Serial communication, with a baud rate of 9600. 

## The GPS and GSM

Using a SIM808 module, I was able to both make calls and retrieve the location using GPS and then sending the location via SMS to a pre-defined number.
The interface with the module could be make by sending AT commands via Serial. As sending AT commands was the central part for the programm, I developed a function that sent an AT command and checked if the returned response was the one expected.
![sim808](/images/sim808.jpg)

### GPS

The SIM808 module supports GPS and you can interface with it via AT commands listed in the documentation. After the module finds its position (which usually takes some long minutes), you can query it for the location, which, in my case, was retrieved in the popular NMEA format. This data was passed to the [TinyGPS library](http://arduiniana.org/libraries/tinygpsplus/) for parsing, after that it was quite trivial to get the required data, latitude, longitude, speed and such.

### GSM

The module also supports functions based on the GSM network such as calls, sending and receiving messages or making HTTP or FTP requests. In this project, I added support for calls and SMS to send the location data. On the setup function, I made the device wait for network connection, after that, making calls was just sending the AT command **ATDXXXXXXXXX;"** (replacing XXX with the number you want to call), the module handled the microphone and speakers integration.
Sending the SMS required setting the number and the message to send.

The circuit used was something like 
![sim808_chem](/images/sim808.png)

## The App
The course was about microcontrollers, there was no point in spending much time writing the application, so I used the **MIT App Inventor** which lets you easily develop an Android app by dragging and dropping blocks of code, similar to **Scratch**.
I made a simple user interface with some arrows like a typical console controller and a slider to control the angle of the tank gun. Two buttons were added to connect/disconnect with the **HC-06** bluetooth module. To keep things simple, the only thing the app sends the robot is a 1 byte number [0-255]. The numbers between 0-180 are seen by the robot as the angle to turn the servo and the following numbers are used to tell the robot where to go or what to do (181 turn left, 185 shoot, etc). This is not the most transparent approach but is the most easy and minimal, keeping the microcontroller code simple and small.
If you want to start developing bluetooth based Android apps, you can check [this link](http://appinventor.pevest.com/?p=520).


## Acknowledgments

During this project the following libraries were used, which both are licensed under a [Creative Commons Attribution-ShareAlike 3.0 License](https://creativecommons.org/licenses/by-sa/3.0/) :

[Software Serial](https://www.arduino.cc/en/Reference/SoftwareSerial)<br>
[Servo](https://www.arduino.cc/en/Reference/Servo)<br>

[TinyGPS](https://github.com/mikalhart/TinyGPS) was also used to parse the GPS data which was encoded in the NMEA format.<br>

I also used the [MIT App Inventor](http://appinventor.mit.edu/) which is an incredible project and you should consider donating to it.<br>

This project is licensed under a [Beerware](https://en.wikipedia.org/wiki/Beerware) license. You are free to use the code if you find it suitable but give credit to those who wrote it.
