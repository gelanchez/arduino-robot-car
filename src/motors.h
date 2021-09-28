/**
 * @file motors.h
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Library for driving 4 motors through a H-bridge.
 * @version 1.0.1
 * @date 2021-09-25
 * @copyright GPL-3.0
 */

#ifndef MOTORS_H
#define MOTORS_H

#include <Arduino.h>
#include "constants.h"

class Motors
{
private:
    short m_leftSpeed, m_rightSpeed;

public:
    Motors();
    ~Motors();
    short getLeftSpeed() const;
    short getRightSpeed() const;
    bool isStopped() const;
    bool isRotatingLeft() const;
    bool isRotatingRight() const;
    void move(short leftSpeed, short rightSpeed);
    void forward(unsigned char speed = Constants::moveSpeed);
    void backward(unsigned char speed = Constants::moveSpeed);
    void rotateLeft(unsigned char speed = Constants::rotateSpeed);
    void rotateRight(unsigned char speed = Constants::rotateSpeed);
    void off();
    void stop();
};

#endif