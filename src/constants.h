/**
 * @file constants.h
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Constants used along the program
 * @version 1.0.1
 * @date 2020-08-28
 * @copyright GPL-3.0
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <Arduino.h>

namespace Constants
{
    const long serialBaud(9600);  // bps for Serial.begin

    // MOTORS
    // Right motors pins
    const uint8_t motorsEnA(6);
    const uint8_t motorsIn1(11);
    const uint8_t motorsIn2(9);
    // Left motors pins
    const uint8_t motorsEnB(5);
    const uint8_t motorsIn3(8);
    const uint8_t motorsIn4(7);
    // Motors min speed (measured)
    const uint8_t crankSpeed(140);  // Around 120 @ full battery
    const uint8_t idleSpeed(90);
    
    // DEFAULT speeds
    const uint8_t moveSpeed(170);
    const uint8_t rotateSpeed(150);
    const uint16_t rotate90Time(650);  // Time to rotate 90deg @ moveSpeed @ full battery
    const uint16_t rotate180Time(1200);  // Time to rotate 180deg @ rotateSpeed @ full battery

    // OBSTACLEAVOIDANCE constants
    const uint16_t updateInterval(250);  // Default update time for states
    const uint16_t minDistance(30);

    // LINETRACKING constants
    const uint8_t ltLeftPin(2);
    const uint8_t ltMidPin(4);
    const uint8_t ltRightPin(10);
    const uint16_t minDetourDistance(10);  // Distance to keep with the obstacle
    const uint16_t updateUltrasonicInterval(20);
    const uint16_t extraTime(100);  // Extra time to keep moving the robot to pass the object
    const uint16_t extraTimeLine(50);  // Extra time to pass the line
    const uint16_t timeUntilLost(1000);  // Wait time until LOSTLINE and turn back
    const uint16_t timeLost(5000);  // Time lost to find a new line
    const uint8_t marginObject(1);  // Margin +- distance to the object

    // PARK mode constants
    const uint16_t timeMoving(500);
    const uint16_t timeMoveAway(150);

    // SERVO
    // Servo pin
    const uint8_t servoPin(3);
    // 0deg and 180deg PWM positions
    const uint16_t servo0(500);  // Calibration 450, default 544
    const uint16_t servo180(2400);  // Calibration 2430, default 2400

    // ULTRASONIC SENSOR
    const uint8_t trigPin(A5);  // Pin 19
    const uint8_t echoPin(A4);  // Pin 18
    const float soundSpeed(0.0343);  // cm/s
    const uint16_t maxDistance(250);  // Maximun distance to meassure in cm
    const uint16_t maxDistanceLineTracking(100);  // Maximun distance to meassure in cm to be used in the linetraking mode

    // IRCONTROL constants
    const uint8_t IRPin(12);
    const unsigned long okKey(0xFF02FD);
    const unsigned long upKey(0xFF629D);
    const unsigned long downKey(0xFFA857);
    const unsigned long leftKey(0xFF22DD);
    const unsigned long rightKey(0xFFC23D);
    const uint16_t IRMovingInterval(500);  // Default time for moving in IR
}

/**
 * @brief Different modes for the robot
 */
enum class RobotMode
{
    REMOTECONTROL,
    IRCONTROL,
    OBSTACLEAVOIDANCE,
    LINETRACKING,
    PARK,
    CUSTOM,
};

/**
 * @brief Orders for the RemoteControl and IRControl modes
 */
enum class RemoteOrder
{
    STOP,
    FORWARD,
    BACKWARD,
    ROTATELEFT,
    ROTATERIGHT,
    UNKNOWN,
};

/**
 * @brief States for the different Robotmode
 */
enum class RobotModeState 
{
    START,
    FORWARD,
    OBSTACLE,
    ROTATE,
    BLOCKED,
    LINELOST,  // Only used in linetracking   
};

#endif