/**
 * @file robot.h
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Library for controling the robot.
 * @version 1.1.0
 * @date 2020-08-29
 * @copyright GPL-3.0
 */
#ifndef ROBOT_H
#define ROBOT_H

#include "infrared.h"
#include "motors.h"
#include "myservo.h"
#include "linetracking.h"
#include "ultrasonic.h"
#include <Arduino.h>

class RobotControl
{
private:
    Motors m_motors;
    MyServo m_servo;
    Ultrasonic m_ultrasonic;
    LineTracking m_lineTracking;
    uint16_t m_sonarMap[5];
    RobotModeState m_state;  // State of the RobotMode
    uint8_t m_previousAngle; // Previous angle of the servo
    unsigned long m_lastUpdate;
    uint16_t m_interval;

public:
    Infrared m_infrared; // Member variable as public to enable from main
    RobotControl();
    ~RobotControl();
    void restartState();
    void begin();

    void remoteControlMode(RemoteOrder order);
    void IRControlMode();
    void obstacleAvoidanceMode();
    void lineTrackingMode();
    void parkMode();
    void customMode();

protected:
    void speedControl();
    uint8_t mapAngle(uint8_t angle);
    void moveServoSequence();
    uint8_t calculateSpeed(uint16_t distance, uint16_t minDistance = Constants::minDistance, uint16_t maxDistance = Constants::maxDistance, uint8_t minSpeed = Constants::crankSpeed);
};

#endif