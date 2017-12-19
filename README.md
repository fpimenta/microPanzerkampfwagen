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

|         | IN1  | IN2  |  EN  |
|---------|------|------|------|
| BRAKE   | HIGH | HIGH | 1-255|
| FRONT   | HIGH | LOW  | 1-255|
| BACK    | LOW  | BACK | 1-255|
| NEUTRAL | x    |  x   |   0  |

The direction was given by the Android app and by turning off and on certain motors, we made the robot go the wanted direction
Also, we defined 5 speed levels which could be changed within the app using a slider.

### Servo
The Servo was used to control the tank gun direction. The input was used by a slider in the Android app which sended to the chipKit an integer between 0 and 180, which corresponded directly to the angle to turn the servo.

### Tank Gun
Of course, our Panzer wouldn't be complete if it wasn't capable of firing ammo. So we designed a cannon inspired in this [Lighter Cannon](https://www.youtube.com/watch?v=QGj8xMDRSQ0). The ignition was given by a [high voltage generator](https://pt.aliexpress.com/item/3-6V-High-Pressure-Generator-Module-Igniter-1-5A-Output-Voltage-20KV-20000KV-Boost-Step-up/32803789310.html) like this one controlled by a digital pin via a relay. The power supply for the generator was the same as for the car. The high peak current drain from the generator could make the tank stop, but this was not a problem as we were designing a tank and most 18650 batteries can deliver a high currents.
### Bluetooth
We decided to control the tank via an Android app, using bluetooth. This way, we added a bluetooth module (HC-06) to communicate with our phone. The communication between the chipKIT and the module was done using Serial communication, with a baud rate of 9600. The code used was something like
```c++
SoftwareSerial BTSerial(bt_rx, bt_tx); // RX 12, TX 13

int r;

void setup() {
    BTSerial.begin(9600);
}
void loop() {

   if (BTSerial.available()) {
    r = BTSerial.read();
   } 
}
```
## The GPS and GPS

### GPS

### GSM


## The App
The course was about microcontrollers, we didn't want to spend much time writing the application, so we used the **MIT App Inventor** which lets you easily develop an Android app by dragging and dropping blocks of code, similar to **Scratch**.
We made a simple user interface with some arrows like a typical console controller and a slider to control the angle of the tank gun. We also added two buttons to connect/disconnect with the **HC-06** bluetooth module. To keep things simple, the only thing the app sends the robot is a 1 byte number [0-255]. The numbers between 0-180 are seen by the robot as the angle to turn the servo and the following numbers are used to tell the robot where to go or what to do (181 turn left, 185 shoot, etc). This is not the most transparent approach but is the most easy and minimal, keeping the microcontroller code simple and small.

## The Server
Using Heroku, we created a simple server using PHP and PostGreSQL to receive the data from the GPS and store it online. Basically, the server retrieves the data that is sent to it via a HTTP GET request and then stores it in a database, using a simples SQL query. This data can be then acessed in browser or in the app.

## Acknowledgments

During this project we used the following libraries, which both are licensed under a [Creative Commons Attribution-ShareAlike 3.0 License](https://creativecommons.org/licenses/by-sa/3.0/) :

[Software Serial](https://www.arduino.cc/en/Reference/SoftwareSerial)<br>
[Servo](https://www.arduino.cc/en/Reference/Servo)<br>

We also used the [MIT App Inventor](http://appinventor.mit.edu/) which is an incredible project and you should consider donating to it.

This project is licensed under a Beerware license so, if you find this usefull you are encouraged to pay us a beer or drink one for us. 
