/**
 * @file ultrasonic.cpp
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Library for using the ultrasonic sensor HC-SR04 with pulseIn.
 * @version 1.0.3
 * @date 2021-17-04
 * @copyright GPL-3.0
 */

#include <Arduino.h>
#include "ultrasonic.h"

/**
 * @brief Construct a new Ultrasonic::Ultrasonic object.
 */
Ultrasonic::Ultrasonic(unsigned char triggerPin, unsigned char echoPin)
    : m_triggerPin{triggerPin}, m_echoPin{echoPin}
{
    pinMode(triggerPin, OUTPUT);
    digitalWrite(triggerPin, LOW);
    pinMode(echoPin, INPUT);
}

/**
 * @brief Destroy the Ultrasonic::Ultrasonic object.
 */
Ultrasonic::~Ultrasonic()
{
}

/**
 * @brief Mesaure the front distance using pulseIn Arduino function.
 * @param maxDistance Maximum measured distance.
 * @return unsigned short Distance measured in cm.
 */
unsigned short Ultrasonic::getDistance(unsigned short maxDistance)
{
    digitalWrite(m_triggerPin, LOW);
    delayMicroseconds(3);
    digitalWrite(m_triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(m_triggerPin, LOW);
    // noInterrupts();
    unsigned long duration = pulseIn(m_echoPin, HIGH, maxDistance / s_halfSpeedOfSound);
    // interrupts();

    if (duration == 0)
        return maxDistance;

    // Calculate distance (cm)
    return static_cast<unsigned short>(duration * s_halfSpeedOfSound);
}