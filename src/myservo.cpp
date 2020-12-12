/**
 * @file myservo.cpp
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Library that inherits from Servo.h.
 * @version 1.0.0
 * @date 2020-08-22
 * @copyright GPL-3.0
 */

#include "constants.h"
#include "myservo.h"
#include <Servo.h>

MyServo::MyServo(): Servo()
{
}

MyServo::~MyServo()
{
}

/**
 * @brief Servo initialization can not be done inside Robot constructor.
 */
void MyServo::begin()
{
    Servo::attach(Constants::servoPin, Constants::servo0, Constants::servo180);
    Servo::write(90);
}