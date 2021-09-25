/**
 * @file ultrasonic.h
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Library for using the ultrasonic sensor HC-SR04.
 * @version 1.0.1
 * @date 2021-09-25
 * @copyright GPL-3.0
 */
#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <Arduino.h>

class Ultrasonic
{
private:
public:
    Ultrasonic();
    ~Ultrasonic();
    unsigned short getDistance(unsigned short maxDistance = Constants::maxDistance);
};

#endif