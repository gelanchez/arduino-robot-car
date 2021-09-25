/**
 * @file myservo.h
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Library that inherits from Servo.h.
 * @version 1.0.1
 * @date 2021-09-25
 * @copyright GPL-3.0
 */

#ifndef MYSERVO_H
#define MYSERVO_H

#include <Servo.h>

class MyServo : public Servo
{
private:
public:
    MyServo();
    ~MyServo();
    void begin();
};

#endif