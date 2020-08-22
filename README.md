# arduino-robot-car
Source code to control a 4-wheel robot car based on Arduino Uno. The code has been tested for the "Elegoo Smart Robot Car Kit V3.0 Plus", but can be easily adatped for other similar ones.

The robot consists of a 4 DC motors driven by a H-Bridge with dual output, connecting the two left wheels and the two right ones to its outputs. The car is remotely controlled either by Bluetooth, through the Elegoo Tool app, or by infrared. An ultrasonic sensor attached to a servo motor measures the front distance to objects. A line tracking sensor on the base, with 3 pairs of LED + photoresistors, allows to follow a line drawn on the floor.
Some functionalities have been added in the software to the official Elegoo release.

## Requirements
Apart from the standard Arduino libraries, some other ones must be installed:
- ArduinoJson: https://arduinojson.org
- IRRemote: https://github.com/z3t0/Arduino-IRremote
- Servo: https://www.arduino.cc/reference/en/libraries/servo/

## Installation
1. Install the required libraries.
2. Download the repository and flash the Arduino. For VSCode, modify the includePath to use the downloaded libraries; if using the Arduino IDE, change the name of the src folder to something appropriate.

## Usage
The oficial Elegoo Tool application for Android must be downloaded to interact with the robot. Nevertheless, changing the initial robot mode will allow you to use it without the app.

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## License
[GPL-3.0](https://choosealicense.com/licenses/gpl-3.0/)