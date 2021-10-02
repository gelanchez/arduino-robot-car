/**
 * @file myservo.h
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Library that inherits from Servo.h.
 * @version 1.0.2
 * @date 2021-10-02
 * @copyright GPL-3.0
 */

#ifndef MYSERVO_H
#define MYSERVO_H

#include <Servo.h>

class MyServo : public Servo
{
private:
    unsigned char m_servoPin; // Servo pin
    unsigned int m_servo0;    // 0 deg PWM position
    unsigned int m_servo180;  // 180 deg PWM position
public:
    MyServo(unsigned char servoPin, unsigned int servo0, unsigned int servo180);
    ~MyServo();
    void begin();
};

#endif