/**
 * @file motors.h
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Library for dealing with motors.
 * @version 1.0.1
 * @date 2021-09-25
 * @copyright GPL-3.0
 */

#ifndef MOTORS_H
#define MOTORS_H

#include "constants.h"
#include <Arduino.h>

class Motors
{
private:
    short m_leftSpeed, m_rightSpeed;

public:
    Motors();
    ~Motors();
    short getLeftSpeed() const;
    short getRightSpeed() const;
    void off();
    void stop();
    void move(short leftSpeed, short rightSpeed);
    void forward(unsigned char speed = Constants::moveSpeed);
    void backward(unsigned char speed = Constants::moveSpeed);
    void rotateLeft(unsigned char speed = Constants::rotateSpeed);
    void rotateRight(unsigned char speed = Constants::rotateSpeed);
    bool isStopped() const;
    bool isRotatingLeft() const;
    bool isRotatingRight() const;
};

#endif