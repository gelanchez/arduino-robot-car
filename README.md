# Arduino 4-wheel robot car
Program to control a 4-wheel robot car based on Arduino Uno. The code has been tested for the [Elegoo Smart Robot Car Kit V3.0 Plus](https://www.elegoo.com/download/), but can be easily adatped for other similar ones.

The robot consists of 4 [DC motors](https://en.wikipedia.org/wiki/DC_motor) driven by a [H-bridge](https://en.wikipedia.org/wiki/H-bridge) with dual output, connecting the two left wheels and the two right ones to its outputs. The car is remotely controlled either by Bluetooth, through the Elegoo Tool app, or by [infrared](https://en.wikipedia.org/wiki/Infrared). An [ultrasonic distance sensor](https://en.wikipedia.org/wiki/Ultrasonic_transducer) attached to a servo motor measures the front distance to objects. A line tracking sensor on the base, with 3 pairs of LED + photoresistor, allows to follow a line drawn on the floor, going around objects placed over it.

Some extra functionalities have been added in the software compared to the official Elegoo code:
- Better obstacle avoidance mode. The servo motor checks more angles and behaves consequently. The robot also moves at a variable speed depending on the distance to the object in front.
- Better line tracking mode. When the robot finds an object in front placed on the line, it will try go around it until it finds the line again, continuing afterwards.
- Park mode. To activate this mode, edit a button in the app to send the command {"N":100}. The robot will park in between two objects placed next to it.
- Custom mode. The ability to program the robot from the app has not been implemented, as it is relatively easy to use the custom mode by modifying the code.

Have fun! :smiley: :robot: :car:

## Requirements

### Development
- [C++11](https://en.wikipedia.org/wiki/C%2B%2B11) version and its recommendations.
- [PlatformIO](https://platformio.org/) IDE for VSCode has been used to program the robot.

### Libraries
Apart from the standard Arduino libraries, some other ones must be installed (these are automatic if you use the included platformio.ini in PlatformIO):
- [ArduinoJson](https://arduinojson.org)
- [IRRemote](https://github.com/z3t0/Arduino-IRremote). Version 3.x required.
- [Servo](https://www.arduino.cc/reference/en/libraries/servo/)

## Installation
1. Install the required libraries (Arduino IDE only).
2. Download the repository and flash the Arduino. If using the Arduino IDE, consider changing the name of the src folder and src.ino to something appropriate.

## Usage
The oficial "Elegoo Ble Tool" application for Android / iPhone / iPad must be downloaded to interact with the robot. Nevertheless, changing the initial robot mode in the code will allow you to use it without the app.

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## License
[GPL-3.0](https://choosealicense.com/licenses/gpl-3.0/)