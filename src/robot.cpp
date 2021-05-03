/**
 * @file robot.cpp
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Library for controling the robot.
 * @version 1.1.0
 * @date 2020-08-29
 * @copyright GPL-3.0
 */

#include "constants.h"
#include "infrared.h"
#include "linetracking.h"
#include "motors.h"
#include "myservo.h"
#include "robot.h"
#include "ultrasonic.h"
#include <Arduino.h>

RobotControl::RobotControl() // Member initializer lists
    : m_motors{}, m_servo{}, m_ultrasonic{}, m_lineTracking{},
      m_sonarMap{Constants::maxDistance, Constants::maxDistance, Constants::maxDistance, Constants::maxDistance, Constants::maxDistance},
      m_state{RobotModeState::START}, m_previousAngle{90}, m_interval{Constants::updateInterval}, m_infrared{}
{
    m_lastUpdate = millis();
}

RobotControl::~RobotControl()
{
    m_servo.detach();
}

void RobotControl::restartState()
{
    if (m_servo.read() != 90)
        m_servo.write(90);
    m_lastUpdate = millis();
    if (!m_motors.isStopped())
        m_motors.stop();
    m_state = RobotModeState::START;
    m_previousAngle = 90;
    m_interval = Constants::updateInterval;
    for (int i = 0; i < 5; i++)
    {
        m_sonarMap[i] = Constants::maxDistance; // Default values
    }
}

void RobotControl::begin()
{
    Serial.begin(Constants::serialBaud); // Can not be inside a constructor
    m_servo.begin();                     // Servo initialization can not be done inside Robot constructor
}

void RobotControl::remoteControlMode(RemoteOrder order)
{
    switch (order)
    {
    case RemoteOrder::STOP:
        m_motors.stop();
        return;
    case RemoteOrder::FORWARD:
        m_motors.forward();
        return;
    case RemoteOrder::BACKWARD:
        m_motors.backward();
        return;
    case RemoteOrder::ROTATELEFT:
        m_motors.rotateLeft();
        return;
    case RemoteOrder::ROTATERIGHT:
        m_motors.rotateRight();
        return;
    default:
        return;
    }
}

void RobotControl::IRControlMode()
{
    RemoteOrder order = m_infrared.decodeIR();
    switch (order) // Equal to remoteControlMode but updating the timer
    {
    case RemoteOrder::STOP:
        m_motors.stop();
        m_lastUpdate = millis();
        break;
    case RemoteOrder::FORWARD:
        m_motors.forward();
        m_lastUpdate = millis();
        break;
    case RemoteOrder::BACKWARD:
        m_motors.backward();
        m_lastUpdate = millis();
        break;
    case RemoteOrder::ROTATELEFT:
        m_motors.rotateLeft();
        m_lastUpdate = millis();
        break;
    case RemoteOrder::ROTATERIGHT:
        m_motors.rotateRight();
        m_lastUpdate = millis();
        break;
    default:
        break;
    }

    if ((millis() - m_lastUpdate) >= Constants::IRMovingInterval) // Stop after IRMovingInterval
    {
        m_lastUpdate = millis();
        m_motors.stop();
    }
}

void RobotControl::obstacleAvoidanceMode()
{
    if ((millis() - m_lastUpdate) >= m_interval)
    {
        m_lastUpdate = millis();
        m_sonarMap[mapAngle(m_servo.read())] = m_ultrasonic.getDistance();
        switch (m_state)
        {
        case RobotModeState::START:
            if (m_sonarMap[2] >= Constants::minDistance)
            {
                m_previousAngle = 30;
                moveServoSequence();
                m_motors.forward(calculateSpeed(m_sonarMap[2]));
                m_state = RobotModeState::FORWARD;
                m_interval = Constants::updateInterval; // Reset scan interval
            }
            else
            {
                m_previousAngle = 0;
                moveServoSequence();
                m_motors.stop();
                m_state = RobotModeState::OBSTACLE;
                m_interval = Constants::updateInterval; // Reset scan interval
            }
            break;
        case RobotModeState::FORWARD:
            if (m_sonarMap[2] < Constants::minDistance)
            {
                m_previousAngle = 0;
                moveServoSequence(); // Go to 180
                m_motors.stop();
                m_state = RobotModeState::OBSTACLE;
                m_interval = Constants::updateInterval; // Reset scan interval
            }
            else if (m_sonarMap[1] < Constants::minDistance)
            {
                if (!m_motors.isRotatingLeft())
                    m_motors.rotateLeft();
                m_interval = 0; // Scan faster and don't turn the servo
            }
            else if (m_sonarMap[3] < Constants::minDistance)
            {
                if (!m_motors.isRotatingRight())
                    m_motors.rotateRight();
                m_interval = 0; // Scan faster and don't turn the servo
            }
            else
            {
                moveServoSequence();
                m_motors.forward(calculateSpeed(m_sonarMap[2]));
                m_interval = Constants::updateInterval; // Reset scan interval
            }
            break;
        case RobotModeState::OBSTACLE:
            if (m_servo.read() != 0)
                moveServoSequence();
            else
            {
                moveServoSequence(); // Go back to 90
                if ((m_sonarMap[0] < Constants::minDistance) && (m_sonarMap[2] < Constants::minDistance) && (m_sonarMap[4] < Constants::minDistance))
                    m_state = RobotModeState::BLOCKED;
                else
                    m_state = RobotModeState::ROTATE;
            }
            break;
        case RobotModeState::ROTATE:
            (m_sonarMap[0] < m_sonarMap[4]) ? m_motors.rotateLeft() : m_motors.rotateRight(); // Condicional operator
            m_interval = Constants::rotate90Time;                                             // Rotate 90
            m_state = RobotModeState::START;
            m_sonarMap[1] = Constants::maxDistance; // Reset values
            m_sonarMap[3] = Constants::maxDistance; // Reset values
            break;
        case RobotModeState::BLOCKED:
            (m_sonarMap[0] < m_sonarMap[4]) ? m_motors.rotateLeft() : m_motors.rotateRight(); // Condicional operator
            m_interval = Constants::rotate180Time;                                            // Rotate 180
            m_state = RobotModeState::START;
            m_sonarMap[1] = Constants::maxDistance; // Reset values
            m_sonarMap[3] = Constants::maxDistance; // Reset values
            break;
        default:
            break;
        }
    }
}

void RobotControl::lineTrackingMode()
{
    switch (m_state)
    {
    case RobotModeState::START:
        if (m_lineTracking.allLines()) // Car not on the floor
            break;
        if ((millis() - m_lastUpdate) >= Constants::updateUltrasonicInterval)
        {
            m_sonarMap[mapAngle(90)] = m_ultrasonic.getDistance(Constants::maxDistanceLineTracking);
            m_lastUpdate = millis();
            if ((m_sonarMap[mapAngle(90)] >= Constants::minDetourDistance) && m_lineTracking.anyLine())
                m_state = RobotModeState::FORWARD; // Move only if no obstacle and any line detected
        }
        break;
    case RobotModeState::FORWARD:
        // Update ultrasonic map
        if ((millis() - m_lastUpdate) >= Constants::updateUltrasonicInterval)
        {
            m_lastUpdate = millis();
            m_sonarMap[2] = m_ultrasonic.getDistance(Constants::maxDistanceLineTracking);
            if (m_sonarMap[2] < Constants::minDetourDistance) // Obstacle found
            {
                m_motors.stop();
                m_servo.write(0); // Look right
                m_state = RobotModeState::ROTATE;
                m_motors.rotateLeft();
                m_lastUpdate = millis();
                delay(Constants::rotate90Time / 2); // To avoid the line detection in ROTATE
                return;
            }
        }

        if (m_lineTracking.leftLine())
            m_motors.rotateLeft();
        else if (m_lineTracking.rightLine())
            m_motors.rotateRight();
        else if (m_lineTracking.midLine())
            m_motors.forward(calculateSpeed(m_sonarMap[2], Constants::minDetourDistance, Constants::maxDistanceLineTracking, Constants::moveSpeed));
        else // No line detected
        {
            // Wait to avoid line missing in between sensors
            unsigned long timeNoLine = millis();
            while ((millis() - timeNoLine) < Constants::timeUntilLost)
            {
                if (m_lineTracking.anyLine())
                    return;
            }
            m_motors.stop();
            m_state = RobotModeState::LINELOST;
        }
        break;
    case RobotModeState::OBSTACLE:
        if (!m_lineTracking.midLine())
        {
            if ((millis() - m_lastUpdate) >= Constants::updateUltrasonicInterval)
            {
                m_sonarMap[0] = m_ultrasonic.getDistance(Constants::maxDistanceLineTracking);
                if (m_sonarMap[0] > (Constants::minDetourDistance - Constants::marginObject) && m_sonarMap[0] < (Constants::minDetourDistance + Constants::marginObject))
                    m_motors.forward(Constants::moveSpeed);
                else if (m_sonarMap[0] > Constants::minDetourDistance) // Go closer
                    m_motors.move(calculateSpeed(m_sonarMap[0], 0, 100, Constants::moveSpeed), 0);
                else // Go further
                    m_motors.move(0, calculateSpeed(m_sonarMap[0], 0, 100, Constants::moveSpeed));
            }
        }
        else // Going around finished, line detected, last rotation
        {
            m_motors.forward();
            delay(Constants::extraTimeLine); // Extra time to over pass the line
            m_motors.stop();
            m_servo.write(90); // Look front
            m_motors.rotateLeft();
            while (!m_lineTracking.midLine())
                ; // Keep rotating until you find the line
            m_state = RobotModeState::START;
            m_motors.stop();
        }
        break;
    case RobotModeState::ROTATE: // Rotate 90 deg
        if ((millis() - m_lastUpdate) >= Constants::rotate90Time)
        {
            m_motors.stop();
            m_lastUpdate = millis();
            m_state = RobotModeState::OBSTACLE;
        }
        break;
    case RobotModeState::LINELOST:
    {
        m_motors.rotateRight(); // Rotate 180 and find the line
        delay(Constants::rotate180Time);
        m_motors.forward(); // Try and find the line backwards

        // Wait and see if backwards you can find the line
        unsigned long timeNoLine = millis();
        while ((millis() - timeNoLine) < Constants::timeLost)
        {
            if (m_lineTracking.anyLine())
                break;
        }
        m_motors.stop();
        m_state = RobotModeState::START;
        break;
    }
    case RobotModeState::BLOCKED:
        break;
    default:
        break;
    }
}

void RobotControl::parkMode()
{
    for (int i = 0; i <= 1; i++)
    {
        m_servo.write(i * 180);
        delay(2 * Constants::updateInterval);
        m_sonarMap[mapAngle(m_servo.read())] = m_ultrasonic.getDistance();
    }
    if (m_sonarMap[mapAngle(0)] < m_sonarMap[mapAngle(180)]) // Park on the right
        m_servo.write(0);
    else
        m_servo.write(180); // Park on the left

    delay(2 * Constants::updateInterval); // Enough time to move the servo

    // Pass the 1st object
    while (m_ultrasonic.getDistance() < Constants::minDistance)
    {
        delay(20);
        m_motors.forward(Constants::crankSpeed);
    }

    // Arrive to the second object
    while (m_ultrasonic.getDistance() > Constants::minDistance)
    {
        delay(50);
        m_motors.forward(Constants::crankSpeed);
    }

    m_motors.backward(Constants::crankSpeed);
    delay(Constants::timeMoveAway); // Time to move away

    if (m_sonarMap[mapAngle(0)] < m_sonarMap[mapAngle(180)]) // Park on the right
        m_motors.rotateRight();
    else // Park on the left
        m_motors.rotateLeft();
    delay(Constants::rotate90Time);
    m_motors.stop();
    m_motors.forward(Constants::crankSpeed);
    delay(Constants::timeMoving);

    if (m_sonarMap[mapAngle(0)] < m_sonarMap[mapAngle(180)]) // Park on the right
        m_motors.rotateLeft();
    else // Park on the left
        m_motors.rotateRight();
    delay(Constants::rotate90Time);
    m_motors.stop();
}

void RobotControl::customMode()
{
    if (m_servo.read() != 0)
    {
        m_servo.write(0);
        delay(300);
        return;
    }
    m_sonarMap[0] = m_ultrasonic.getDistance(Constants::maxDistanceLineTracking);
    if (m_sonarMap[0] > (Constants::minDetourDistance - Constants::marginObject) && m_sonarMap[0] < (Constants::minDetourDistance + Constants::marginObject))
        m_motors.forward(Constants::moveSpeed);
    else if (m_sonarMap[0] > Constants::minDetourDistance) // Go closer
        m_motors.move(calculateSpeed(m_sonarMap[0], 0, 100, Constants::moveSpeed), 0);
    else // Go further
        m_motors.move(0, Constants::moveSpeed);
}

uint8_t RobotControl::mapAngle(uint8_t angle)
{
    switch (angle)
    {
    case 0:
        return 0;
    case 30:
        return 1;
    case 90:
        return 2;
    case 150:
        return 3;
    case 180:
        return 4;
    default:
        return 0;
    }
}

void RobotControl::moveServoSequence() // Sequences: {90, 150, 90, 30} {90, 180, 90, 0}
{
    uint8_t currentAngle = m_servo.read();
    if (currentAngle != 90)
        m_servo.write(90);
    else
    {
        if (m_previousAngle == 150)
            m_servo.write(30);
        else if (m_previousAngle == 30)
            m_servo.write(150);
        else if (m_previousAngle == 180)
            m_servo.write(0);
        else if (m_previousAngle == 0)
            m_servo.write(180);
    }
    m_previousAngle = currentAngle;
}

uint8_t RobotControl::calculateSpeed(uint16_t distance, uint16_t minDistance, uint16_t maxDistance, uint8_t minSpeed)
{
    return minSpeed + static_cast<uint8_t>((distance - minDistance) * (255 - minSpeed) / (maxDistance - minDistance));
}
