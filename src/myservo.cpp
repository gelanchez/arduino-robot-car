/**
 * @file myservo.cpp
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Library that inherits from Servo.h.
 * @version 1.0.1
 * @date 2021-09-25
 * @copyright GPL-3.0
 */

#include <Servo.h>
#include "constants.h"
#include "myservo.h"

/**
 * @brief Construct a new MyServo::MyServo object which inherits from Servo.
 */
MyServo::MyServo() : Servo()
{
}

/**
 * @brief Destroy the MyServo::MyServo object
 */
MyServo::~MyServo()
{
}

/**
 * @brief Servo initialization. It can not be done inside Robot constructor.
 */
void MyServo::begin()
{
    Servo::attach(Pins::servoPin, Constants::servo0, Constants::servo180);
    Servo::write(90);
}