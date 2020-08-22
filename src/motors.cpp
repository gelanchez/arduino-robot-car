/**
 * @file motors.cpp
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Library for dealing with motors.
 * @version 1.0.0
 * @date 2020-08-22
 * @copyright GPL-3.0
 */

#include "constants.h"
#include "motors.h"

Motors::Motors() : m_leftSpeed(0), m_rightSpeed(0)  // Member initializer lists
{
    // Pins used for motors
    pinMode(Constants::motorsEnA, OUTPUT);
    pinMode(Constants::motorsIn1, OUTPUT);
    pinMode(Constants::motorsIn2, OUTPUT);
    pinMode(Constants::motorsEnB, OUTPUT);
    pinMode(Constants::motorsIn3, OUTPUT);
    pinMode(Constants::motorsIn4, OUTPUT);

    off();
}

Motors::~Motors()
{
    off();
}

int16_t Motors::getLeftSpeed()
{
    return m_leftSpeed;
}

int16_t Motors::getRightSpeed()
{
    return m_rightSpeed;
}

void Motors::off()
{
    stop();
    digitalWrite(Constants::motorsIn1, LOW);
    digitalWrite(Constants::motorsIn2, LOW);
    digitalWrite(Constants::motorsIn3, LOW);
    digitalWrite(Constants::motorsIn4, LOW);
}

void Motors::stop()
{
    digitalWrite(Constants::motorsEnA, LOW);
    digitalWrite(Constants::motorsEnB, LOW);
    m_leftSpeed = 0;
    m_rightSpeed = 0;
}

void Motors::move(int16_t leftSpeed, int16_t rightSpeed)
{
    // Return if no speed change
    if ((m_leftSpeed == leftSpeed) && (m_rightSpeed == rightSpeed))
        return;
    
    // Limit values
    leftSpeed = constrain(leftSpeed, -255, 255);
    rightSpeed = constrain(rightSpeed, -255, 255);

    // Prevent buzzing at low speeds
    uint8_t minLeftSpeed = (m_leftSpeed == 0) ? Constants::crankSpeed : Constants::idleSpeed;
    uint8_t minRightSpeed = (m_rightSpeed == 0) ? Constants::crankSpeed : Constants::idleSpeed;

    // Member variables update
    m_leftSpeed = (abs(leftSpeed) < minLeftSpeed) ? 0 : leftSpeed;
    m_rightSpeed = (abs(rightSpeed) < minRightSpeed) ? 0 : rightSpeed;

    if (m_leftSpeed<0)
    {
        digitalWrite(Constants::motorsIn3, HIGH);
        digitalWrite(Constants::motorsIn4, LOW);
        analogWrite(Constants::motorsEnB, abs(m_leftSpeed));
    }
    else if (m_leftSpeed==0)
        analogWrite(Constants::motorsEnB, 0);
    else
    {
        digitalWrite(Constants::motorsIn3, LOW);
        digitalWrite(Constants::motorsIn4, HIGH);
        analogWrite(Constants::motorsEnB, m_leftSpeed);
    }
    
    if (m_rightSpeed<0)
    {
        digitalWrite(Constants::motorsIn1, LOW);
        digitalWrite(Constants::motorsIn2, HIGH);
        analogWrite(Constants::motorsEnA, abs(m_rightSpeed));
    }
    else if (m_rightSpeed==0)
        analogWrite(Constants::motorsEnA, 0);
    else
    {
        digitalWrite(Constants::motorsIn1, HIGH);
        digitalWrite(Constants::motorsIn2, LOW);
        analogWrite(Constants::motorsEnA, m_rightSpeed);
    }
}

void Motors::forward(uint8_t speed)
{
    move(speed, speed);
}

void Motors::backward(uint8_t speed)
{
    move(-speed, -speed);
}

void Motors::rotateLeft(uint8_t speed)
{
    move(-speed, speed);
}

void Motors::rotateRight(uint8_t speed)
{
    move(speed, -speed);
}

bool Motors::isStopped()
{
    if ((m_leftSpeed == 0) && (m_rightSpeed == 0))
        return true;
    return false;
}

bool Motors::isRotatingLeft()
{
    if ((m_leftSpeed < 0) && (m_rightSpeed > 0))
        return true;
    return false;
}

bool Motors::isRotatingRight()
{
    if ((m_leftSpeed > 0) && (m_rightSpeed < 0))
        return true;
    return false;
}