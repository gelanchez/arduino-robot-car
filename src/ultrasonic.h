/**
 * @file ultrasonic.h
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Library for using the ultrasonic sensor HC-SR04.
 * @version 1.0.0
 * @date 2020-08-22
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
        uint16_t getDistance(uint16_t maxDistance = Constants::maxDistance);
};

#endif