/**
 * @file ultrasonic.h
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Library for using the ultrasonic sensor HC-SR04 wiht pulseIn.
 * @version 1.0.2
 * @date 2021-10-02
 * @copyright GPL-3.0
 */
#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <Arduino.h>

class Ultrasonic
{
private:
    unsigned char m_triggerPin;                            // Trigger pin
    unsigned char m_echoPin;                               // Echo receiver pin
    static constexpr float s_halfSpeedOfSound{0.0343 / 2}; // Half of speed of sound in cm/s
public:
    Ultrasonic(unsigned char triggerPin, unsigned char echoPin);
    ~Ultrasonic();
    unsigned short getDistance(unsigned short maxDistance);
};

#endif