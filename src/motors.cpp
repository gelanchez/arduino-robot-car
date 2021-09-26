/**
 * @file motors.cpp
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Library for dealing with motors.
 * @version 1.0.1
 * @date 2021-09-25
 * @copyright GPL-3.0
 */

#include "constants.h"
#include "motors.h"

Motors::Motors() : m_leftSpeed{0}, m_rightSpeed{0} // Member initializer lists
{
    // Pins used for motors
    pinMode(Pins::motorsEnA, OUTPUT);
    pinMode(Pins::motorsIn1, OUTPUT);
    pinMode(Pins::motorsIn2, OUTPUT);
    pinMode(Pins::motorsEnB, OUTPUT);
    pinMode(Pins::motorsIn3, OUTPUT);
    pinMode(Pins::motorsIn4, OUTPUT);

    off();
}

Motors::~Motors()
{
    off();
}

short Motors::getLeftSpeed() const
{
    return m_leftSpeed;
}

short Motors::getRightSpeed() const
{
    return m_rightSpeed;
}

void Motors::off()
{
    stop();
    digitalWrite(Pins::motorsIn1, LOW);
    digitalWrite(Pins::motorsIn2, LOW);
    digitalWrite(Pins::motorsIn3, LOW);
    digitalWrite(Pins::motorsIn4, LOW);
}

void Motors::stop()
{
    digitalWrite(Pins::motorsEnA, LOW);
    digitalWrite(Pins::motorsEnB, LOW);
    m_leftSpeed = 0;
    m_rightSpeed = 0;
}

void Motors::move(short leftSpeed, short rightSpeed)
{
    // Return if no speed change
    if ((m_leftSpeed == leftSpeed) && (m_rightSpeed == rightSpeed))
        return;

    // Limit values
    leftSpeed = constrain(leftSpeed, -255, 255);
    rightSpeed = constrain(rightSpeed, -255, 255);

    // Prevent buzzing at low speeds
    unsigned char minLeftSpeed = (m_leftSpeed == 0) ? Constants::crankSpeed : Constants::idleSpeed;
    unsigned char minRightSpeed = (m_rightSpeed == 0) ? Constants::crankSpeed : Constants::idleSpeed;

    // Member variables update
    m_leftSpeed = (abs(leftSpeed) < minLeftSpeed) ? 0 : leftSpeed;
    m_rightSpeed = (abs(rightSpeed) < minRightSpeed) ? 0 : rightSpeed;

    if (m_leftSpeed < 0)
    {
        digitalWrite(Pins::motorsIn3, HIGH);
        digitalWrite(Pins::motorsIn4, LOW);
        analogWrite(Pins::motorsEnB, abs(m_leftSpeed));
    }
    else if (m_leftSpeed == 0)
        analogWrite(Pins::motorsEnB, 0);
    else
    {
        digitalWrite(Pins::motorsIn3, LOW);
        digitalWrite(Pins::motorsIn4, HIGH);
        analogWrite(Pins::motorsEnB, m_leftSpeed);
    }

    if (m_rightSpeed < 0)
    {
        digitalWrite(Pins::motorsIn1, LOW);
        digitalWrite(Pins::motorsIn2, HIGH);
        analogWrite(Pins::motorsEnA, abs(m_rightSpeed));
    }
    else if (m_rightSpeed == 0)
        analogWrite(Pins::motorsEnA, 0);
    else
    {
        digitalWrite(Pins::motorsIn1, HIGH);
        digitalWrite(Pins::motorsIn2, LOW);
        analogWrite(Pins::motorsEnA, m_rightSpeed);
    }
}

void Motors::forward(unsigned char speed)
{
    move(speed, speed);
}

void Motors::backward(unsigned char speed)
{
    move(-speed, -speed);
}

void Motors::rotateLeft(unsigned char speed)
{
    move(-speed, speed);
}

void Motors::rotateRight(unsigned char speed)
{
    move(speed, -speed);
}

bool Motors::isStopped() const
{
    if ((m_leftSpeed == 0) && (m_rightSpeed == 0))
        return true;
    return false;
}

bool Motors::isRotatingLeft() const
{
    if ((m_leftSpeed < 0) && (m_rightSpeed > 0))
        return true;
    return false;
}

bool Motors::isRotatingRight() const
{
    if ((m_leftSpeed > 0) && (m_rightSpeed < 0))
        return true;
    return false;
}