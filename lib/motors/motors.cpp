/**
 * @file motors.cpp
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Library for driving 4 motors through a H-bridge.
 * @version 1.0.2
 * @date 2021-10-03
 * @copyright GPL-3.0
 */

#include "motors.h"

/**
 * @brief Construct a new Motors::Motors object.
 * @param enableA Right motor enable.
 * @param input1 Left motor input1.
 * @param input2 Left motor input2.
 * @param enableB Left motor enable.
 * @param input3 Left motor input3.
 * @param input4 Left motor input4.
 * @param crankSpeed Minimun crank speed.
 * @param idleSpeed Minimum idle speed.
 */
Motors::Motors(unsigned char enableA, unsigned char input1, unsigned char input2, unsigned char enableB, unsigned char input3, unsigned char input4, unsigned char crankSpeed, unsigned char idleSpeed)
    : m_enableA{enableA}, m_input1{input1}, m_input2{input2}, m_enableB{enableB}, m_input3{input3}, m_input4{input4}, m_crankSpeed{crankSpeed}, m_idleSpeed{idleSpeed}, m_leftSpeed{0}, m_rightSpeed{0}
{
    pinMode(enableA, OUTPUT);
    pinMode(input1, OUTPUT);
    pinMode(input2, OUTPUT);
    pinMode(enableB, OUTPUT);
    pinMode(input3, OUTPUT);
    pinMode(input4, OUTPUT);

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
    unsigned char minLeftSpeed = (m_leftSpeed == 0) ? m_crankSpeed : m_idleSpeed;
    unsigned char minRightSpeed = (m_rightSpeed == 0) ? m_crankSpeed : m_idleSpeed;

    // Member variables update first
    m_leftSpeed = (abs(leftSpeed) < minLeftSpeed) ? 0 : leftSpeed;
    m_rightSpeed = (abs(rightSpeed) < minRightSpeed) ? 0 : rightSpeed;

    if (m_leftSpeed < 0)
    {
        digitalWrite(m_input3, HIGH);
        digitalWrite(m_input4, LOW);
        analogWrite(m_enableB, abs(m_leftSpeed));
    }
    else if (m_leftSpeed == 0)
        analogWrite(m_enableB, 0);
    else
    {
        digitalWrite(m_input3, LOW);
        digitalWrite(m_input4, HIGH);
        analogWrite(m_enableB, m_leftSpeed);
    }

    if (m_rightSpeed < 0)
    {
        digitalWrite(m_input1, LOW);
        digitalWrite(m_input2, HIGH);
        analogWrite(m_enableA, abs(m_rightSpeed));
    }
    else if (m_rightSpeed == 0)
        analogWrite(m_enableA, 0);
    else
    {
        digitalWrite(m_input1, HIGH);
        digitalWrite(m_input2, LOW);
        analogWrite(m_enableA, m_rightSpeed);
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
void Motors::left(unsigned char speed)
{
    move(-speed, speed);
}

/**
 * @brief Rotate robot right.
 * @param speed Robot speed (0..255).
 */
void Motors::right(unsigned char speed)
{
    move(speed, -speed);
}

/**
 * @brief Move forward turning left.
 * @param speed Robot speed (0..255).
 */
void Motors::forwardLeft(unsigned char speed)
{
    move(speed/2, speed);
}

/**
 * @brief Move forward turning right.
 * @param speed Robot speed (0..255).
 */
void Motors::forwardRight(unsigned char speed)
{
    move(speed, speed/2);
}

/**
 * @brief Move backward turning left.
 * @param speed Robot speed (0..255).
 */
void Motors::backwardLeft(unsigned char speed)
{
    move(-speed/2, -speed);
}

/**
 * @brief Move backward turning right.
 * @param speed Robot speed (0..255).
 */
void Motors::backwardRight(unsigned char speed)
{
    move(-speed, -speed/2);
}

/**
 * @brief Stop and turn motors off.
 */
void Motors::off()
{
    stop();
    digitalWrite(m_input1, LOW);
    digitalWrite(m_input2, LOW);
    digitalWrite(m_input3, LOW);
    digitalWrite(m_input4, LOW);
}

/**
 * @brief Stop motors.
 */
void Motors::stop()
{
    digitalWrite(m_enableA, LOW);
    digitalWrite(m_enableB, LOW);
    m_leftSpeed = 0;
    m_rightSpeed = 0;
}