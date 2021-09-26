/**
 * @file BTprocess.cpp
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Library for receiving and processing the data from the serial bluetooth JSON.
 * @version 1.1.1
 * @date 2021-09-25
 * @copyright GPL-3.0
 */

#include <ArduinoJson.h>
#include "BTprocess.h"
#include "constants.h"

BTprocess::BTprocess()
    : m_dataBT{""}, m_mode{RobotMode::REMOTECONTROL}, // Default mode
      m_parameter1{0}, m_parameter2{0}
{
}

BTprocess::~BTprocess()
{
}

/**
 * @brief Decode Elegoo JSON object, setting the struct data.
 * Modes in bluetooth (Elegoo specifications):
 * {"N":5} square down bluetoothFollowing.
 * {"N":3,"D1":1} line tracking.
 * {"N":3,"D1":2} obstacle avoidance.
 * {"N":2,"D1":1...5} joystick.
 */
void BTprocess::decodeElegooJSON()
{
    DeserializationError error = deserializeJson(m_elegooDoc, m_dataBT);
    if (!error)
    {
        unsigned char N = m_elegooDoc["N"];
        unsigned char D1;
        switch (N) // See Elegoo specifications
        {
        case 2: // remoteControlMode
            m_mode = RobotMode::REMOTECONTROL;
            D1 = m_elegooDoc["D1"];
            switch (D1)
            {
            case 1:
                m_parameter1 = static_cast<unsigned char>(RemoteOrder::ROTATELEFT);
                return;
            case 2:
                m_parameter1 = static_cast<unsigned char>(RemoteOrder::ROTATERIGHT);
                return;
            case 3:
                m_parameter1 = static_cast<unsigned char>(RemoteOrder::FORWARD);
                return;
            case 4:
                m_parameter1 = static_cast<unsigned char>(RemoteOrder::BACKWARD);
                return;
            case 5:
                m_parameter1 = static_cast<unsigned char>(RemoteOrder::STOP);
                return;
            default:
                m_parameter1 = static_cast<unsigned char>(RemoteOrder::UNKNOWN);
                return;
            }
        case 3: // lineTrackingMode or obstacleAvoidanceMode
            D1 = m_elegooDoc["D1"];
            switch (D1)
            {
            case 1:
                if (m_mode != RobotMode::LINETRACKING)
                    m_mode = RobotMode::LINETRACKING;
                return;
            case 2:
                if (m_mode != RobotMode::OBSTACLEAVOIDANCE)
                    m_mode = RobotMode::OBSTACLEAVOIDANCE;
                return;
            default:
                return;
            }
        case 5: // IRControlMode mode activation or deactivation (deactivate other modes)
            if (m_mode == RobotMode::REMOTECONTROL)
                m_mode = RobotMode::IRCONTROL;
            else
                m_mode = RobotMode::REMOTECONTROL;
            return;
        case 100: // parkMode activation
            m_mode = RobotMode::PARK;
            return;
        default:
            m_mode = RobotMode::REMOTECONTROL;
            return;
        }
    }
}

String BTprocess::getBTData() const
{
    return m_dataBT;
}

RobotMode BTprocess::getMode() const
{
    return m_mode;
}

unsigned char BTprocess::getParameter1() const
{
    return m_parameter1;
}

unsigned char BTprocess::getParameter2() const
{
    return m_parameter2;
}

void BTprocess::receiveBTData()
{
    m_dataBT = "";
    while ((Serial.available() > 0) && (m_dataBT.endsWith("}") == false))
    {
        m_dataBT += static_cast<char>(Serial.read());
        delay(3);
    }
    if ((m_dataBT.length() > 0) && m_dataBT.endsWith("}"))
        return;
    else
        m_dataBT = "";
}