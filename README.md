# Arduino 4-wheel robot car
Program to control a 4-wheel robot car based on Arduino Uno. The code has been tested for the [Elegoo Smart Robot Car Kit V3.0 Plus](https://www.elegoo.com/download/), but can be easily adatped for other similar ones.

The robot consists of 4 DC motors driven by a H-bridge with dual output, connecting the two left wheels and the two right ones to its outputs. The car is remotely controlled either by Bluetooth, through the Elegoo Tool app, or by infrared. An ultrasonic sensor attached to a servo motor measures the front distance to objects. A line tracking sensor on the base, with 3 pairs of LED + photoresistor, allows to follow a line drawn on the floor, going around objects placed over it.

Some extra functionalities have been added in the software compared to the official Elegoo code:
- Better obstacle avoidance mode. The servo motor checks more angles and behaves consequently. The robot also moves at a variable speed depending on the distance to the object in front.
- Better line tracking mode. When the robot finds an object in front placed on the line, it will try go around it until it finds the line again, continuing afterwards.
- Park mode. To activate this mode, edit a button in the app to send the command {"N":100}. The robot will park in between two objects placed next to it.
- Custom mode. The ability to program the robot from the app is not implemented, as it can be relatively easy to using the custom mode, modifying the code.

:smiley: Have fun! :robot: :car:

## Requirements
Apart from the standard Arduino libraries, some other ones must be installed:
- [ArduinoJson](https://arduinojson.org)
- [IRRemote](https://github.com/z3t0/Arduino-IRremote)
- [Servo](https://www.arduino.cc/reference/en/libraries/servo/)

## Installation
1. Install the required libraries.
2. Download the repository and flash the Arduino. For VSCode, modify the includePath to use the downloaded libraries; if using the Arduino IDE, change the name of the src folder to something appropriate.

## Usage
The oficial "Elegoo Ble Tool" application for Android / iPhone / iPad must be downloaded to interact with the robot. Nevertheless, changing the initial robot mode in the code will allow you to use it without the app.

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## License
[GPL-3.0](https://choosealicense.com/licenses/gpl-3.0/)