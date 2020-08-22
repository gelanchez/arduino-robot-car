/**
 * @file ultrasonic.cpp
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Library for using the ultrasonic sensor HC-SR04.
 * @version 1.0.0
 * @date 2020-08-22
 * @copyright GPL-3.0
 */

#include "constants.h"
#include "ultrasonic.h"
#include <Arduino.h>

Ultrasonic::Ultrasonic()
{
    pinMode(Constants::trigPin, OUTPUT);
    digitalWrite(Constants::trigPin, LOW);
    pinMode(Constants::echoPin, INPUT);
}

Ultrasonic::~Ultrasonic()
{
}

/**
 * @brief Mesaures the distance using the ultrasonic sensor.
 * @param maxDistance Max distance to be considered.
 * @return uint16_t Distance measured in cm.
 */
uint16_t Ultrasonic::getDistance(uint16_t maxDistance)
{
    digitalWrite(Constants::trigPin, LOW);
    delayMicroseconds(3);
    digitalWrite(Constants::trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(Constants::trigPin, LOW);
    // noInterrupts();
    unsigned long duration = pulseIn(Constants::echoPin, HIGH, maxDistance * 2 / Constants::soundSpeed);
    // interrupts();
    
    if (duration == 0)
        return maxDistance;

    // Calculate distance (cm)
    uint16_t distance = static_cast<uint16_t>((duration/2)*Constants::soundSpeed);
    return distance;
}