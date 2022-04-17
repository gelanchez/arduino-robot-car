/**
 * @file motors.h
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Library for driving 4 motors through a H-bridge.
 * @version 1.0.3
 * @date 2022-04-17
 * @copyright GPL-3.0
 */

#ifndef MOTORS_H
#define MOTORS_H

#include <Arduino.h>

class Motors
{
private:
    unsigned char m_enableA, m_input1, m_input2; // Right motors pins
    unsigned char m_enableB, m_input3, m_input4; // Left motors pins
    unsigned char m_crankSpeed, m_idleSpeed;     // Minimum speeds
    short m_leftSpeed, m_rightSpeed;

public:
    Motors(unsigned char enableA, unsigned char input1, unsigned char input2, unsigned char enableB, unsigned char input3, unsigned char input4, unsigned char crankSpeed, unsigned char idleSpeed);
    ~Motors();
    short getLeftSpeed() const;
    short getRightSpeed() const;
    bool isStopped() const;
    bool isRotatingLeft() const;
    bool isRotatingRight() const;
    void move(short leftSpeed, short rightSpeed);
    void forward(unsigned char speed);
    void backward(unsigned char speed);
    void left(unsigned char speed);
    void right(unsigned char speed);
    void forwardLeft(unsigned char speed);
    void forwardRight(unsigned char speed);
    void backwardLeft(unsigned char speed);
    void backwardRight(unsigned char speed);
    void off();
    void stop();
};

#endif