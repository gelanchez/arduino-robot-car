/**
 * @file myservo.h
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Library that inherits from Servo.h.
 * @version 1.0.0
 * @date 2020-08-22
 * @copyright GPL-3.0
 */

#ifndef MYSERVO_H
#define MYSERVO_H

#include <Servo.h>

class MyServo: public Servo
{
    private:

    public:
        MyServo();
        ~MyServo();
        void begin();
};

#endif