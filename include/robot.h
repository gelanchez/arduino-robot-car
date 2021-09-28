/**
 * @file robot.h
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Library for controling the robot.
 * @version 1.1.1
 * @date 2021-09-25
 * @copyright GPL-3.0
 */

#ifndef ROBOT_H
#define ROBOT_H

#include <Arduino.h>
#include "infrared.h"
#include "linetracking.h"
#include "motors.h"
#include "myservo.h"
#include "ultrasonic.h"

class Robot
{
private:
    Motors m_motors;
    MyServo m_servo;
    Ultrasonic m_ultrasonic;
    LineTracking m_lineTracking;
    unsigned short m_sonarMap[5];
    RobotModeState m_state;        // State of the RobotMode
    unsigned char m_previousAngle; // Previous angle of the servo
    unsigned long m_lastUpdate;
    unsigned short m_interval;

protected:
    void speedControl();
    unsigned char mapAngle(unsigned char angle) const;
    void moveServoSequence();
    unsigned char calculateSpeed(unsigned short distance, unsigned short minDistance = Constants::minDistance, unsigned short maxDistance = Constants::maxDistance, unsigned char minSpeed = Constants::crankSpeed) const;

public:
    Infrared m_infrared; // Member variable as public to enable from main
    Robot();
    ~Robot();
    void restartState();
    void begin();

    void remoteControlMode(RemoteOrder order);
    void IRControlMode();
    void obstacleAvoidanceMode();
    void lineTrackingMode();
    void parkMode();
    void customMode();
};

#endif