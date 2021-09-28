/**
 * @file motors.cpp
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Library for driving 4 motors through a H-bridge.
 * @version 1.0.1
 * @date 2021-09-25
 * @copyright GPL-3.0
 */

#include "constants.h"
#include "motors.h"

/**
 * @brief Construct a new Motors::Motors object.
 */
Motors::Motors() : m_leftSpeed{0}, m_rightSpeed{0}
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

/**
 * @brief Destroy the Motors::Motors object.
 */
Motors::~Motors()
{
    off();
}

/**
 * @brief Get left motors speed.
 * @return short left motors speed.
 */
short Motors::getLeftSpeed() const
{
    return m_leftSpeed;
}

/**
 * @brief Get right motors speed.
 * @return short right motors speed.
 */
short Motors::getRightSpeed() const
{
    return m_rightSpeed;
}

/**
 * @brief Return if motors are stopped.
 * @return true Motors stopped.
 * @return false Motors speeds non zero.
 */
bool Motors::isStopped() const
{
    if ((m_leftSpeed == 0) && (m_rightSpeed == 0))
        return true;
    return false;
}

/**
 * @brief Return if robot is rotating left.
 * @return true Robot rotating left.
 * @return false Robot not rotating left.
 */
bool Motors::isRotatingLeft() const
{
    if ((m_leftSpeed < 0) && (m_rightSpeed > 0))
        return true;
    return false;
}

/**
 * @brief Return if robot is rotating right.
 * @return true Robot rotating right.
 * @return false Robot not rotating right.
 */
bool Motors::isRotatingRight() const
{
    if ((m_leftSpeed > 0) && (m_rightSpeed < 0))
        return true;
    return false;
}

/**
 * @brief Drive the motors with a PWM signal.
 * @param leftSpeed PWM value: -255..255.
 * @param rightSpeed PWM value: -255..255.
 */
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

    // Member variables updatefirst
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

/**
 * @brief Move robot forward.
 * @param speed Robot speed (0..255).
 */
void Motors::forward(unsigned char speed)
{
    move(speed, speed);
}

/**
 * @brief Move robot backward.
 * @param speed Robot speed (0..255).
 */
void Motors::backward(unsigned char speed)
{
    move(-speed, -speed);
}

/**
 * @brief Rotate robot left.
 * @param speed Robot speed (0..255).
 */
void Motors::rotateLeft(unsigned char speed)
{
    move(-speed, speed);
}

/**
 * @brief Rotate robot right.
 * @param speed Robot speed (0..255).
 */
void Motors::rotateRight(unsigned char speed)
{
    move(speed, -speed);
}

/**
 * @brief Stop and turn motors off.
 */
void Motors::off()
{
    stop();
    digitalWrite(Pins::motorsIn1, LOW);
    digitalWrite(Pins::motorsIn2, LOW);
    digitalWrite(Pins::motorsIn3, LOW);
    digitalWrite(Pins::motorsIn4, LOW);
}

/**
 * @brief Stop motors.
 */
void Motors::stop()
{
    digitalWrite(Pins::motorsEnA, LOW);
    digitalWrite(Pins::motorsEnB, LOW);
    m_leftSpeed = 0;
    m_rightSpeed = 0;
}