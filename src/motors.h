/**
 * @file motors.h
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Library for dealing with motors.
 * @version 1.0.0
 * @date 2020-08-22
 * @copyright GPL-3.0
 */

#ifndef MOTORS_H
#define MOTORS_H

#include "constants.h"
#include <Arduino.h>

class Motors
{
    private:
        int16_t m_leftSpeed, m_rightSpeed;

    public:
        Motors();
        ~Motors();
        int16_t getLeftSpeed();
        int16_t getRightSpeed();
        void off();
        void stop();
        void move(int16_t leftSpeed, int16_t rightSpeed);
        void forward(uint8_t speed = Constants::moveSpeed);
        void backward(uint8_t speed = Constants::moveSpeed);
        void rotateLeft(uint8_t speed = Constants::rotateSpeed);
        void rotateRight(uint8_t speed = Constants::rotateSpeed);
        bool isStopped();
        bool isRotatingLeft();
        bool isRotatingRight();
};

#endif