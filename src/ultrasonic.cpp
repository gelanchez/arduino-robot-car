/**
 * @file ultrasonic.cpp
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Library for using the ultrasonic sensor HC-SR04.
 * @version 1.0.1
 * @date 2021-09-25
 * @copyright GPL-3.0
 */

#include <Arduino.h>
#include "constants.h"
#include "ultrasonic.h"

Ultrasonic::Ultrasonic()
{
    pinMode(Pins::trigPin, OUTPUT);
    digitalWrite(Pins::trigPin, LOW);
    pinMode(Pins::echoPin, INPUT);
}

Ultrasonic::~Ultrasonic()
{
}

/**
 * @brief Mesaures the distance using the ultrasonic sensor.
 * @param maxDistance Max distance to be considered.
 * @return unsigned short Distance measured in cm.
 */
unsigned short Ultrasonic::getDistance(unsigned short maxDistance)
{
    digitalWrite(Pins::trigPin, LOW);
    delayMicroseconds(3);
    digitalWrite(Pins::trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(Pins::trigPin, LOW);
    // noInterrupts();
    unsigned long duration = pulseIn(Pins::echoPin, HIGH, maxDistance * 2 / Constants::soundSpeed);
    // interrupts();

    if (duration == 0)
        return maxDistance;

    // Calculate distance (cm)
    unsigned short distance = static_cast<unsigned short>((duration / 2) * Constants::soundSpeed);
    return distance;
}