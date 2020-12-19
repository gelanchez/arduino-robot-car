/**
 * @file BTprocess.cpp
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Library for receiving and processing the data from the serial bluetooth JSON.
 * @version 1.1.0
 * @date 2020-08-30
 * @copyright GPL-3.0
 */

#include <ArduinoJson.h>
#include "BTprocess.h"
#include "constants.h"

BTprocess::BTprocess(): m_dataBT { "" }, m_mode { RobotMode::REMOTECONTROL },  // Default mode
m_parameter1 { 0 }, m_parameter2 { 0 }
{
}

BTprocess::~BTprocess()
{
}

/**
 * @brief Decode Elegoo JSON object, setting the struct data.
 * Modes in bluetooth (Elegoo specifications):
 * {"N":5} square down bluetoothFollowing
 * {"N":3,"D1":1} line tracking
 * {"N":3,"D1":2} obstacle avoidance
 * {"N":2,"D1":1...5} joystick
 */
void BTprocess::decodeElegooJSON()
{
    DeserializationError error = deserializeJson(m_elegooDoc, m_dataBT);
    if (!error)
    {
        uint8_t N = m_elegooDoc["N"];
        uint8_t D1;
        switch (N)  // See Elegoo specifications
        {
            case 2:  // remoteControlMode
                m_mode = RobotMode::REMOTECONTROL;
                D1 = m_elegooDoc["D1"];
                switch (D1)
                {
                    case 1:
                        m_parameter1 = static_cast<uint8_t>(RemoteOrder::ROTATELEFT);
                        return;
                    case 2:
                        m_parameter1 = static_cast<uint8_t>(RemoteOrder::ROTATERIGHT);
                        return;
                    case 3:
                        m_parameter1 = static_cast<uint8_t>(RemoteOrder::FORWARD);
                        return;
                    case 4:
                        m_parameter1 = static_cast<uint8_t>(RemoteOrder::BACKWARD);
                        return;
                    case 5:
                        m_parameter1 = static_cast<uint8_t>(RemoteOrder::STOP);
                        return;
                    default:
                        m_parameter1 = static_cast<uint8_t>(RemoteOrder::UNKNOWN);
                        return;
                }
            case 3:  // lineTrackingMode or obstacleAvoidanceMode
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
            case 5:  // IRControlMode mode activation or deactivation (deactivate other modes)
                if (m_mode == RobotMode::REMOTECONTROL)
                    m_mode = RobotMode::IRCONTROL;
                else
                    m_mode = RobotMode::REMOTECONTROL;
                return;
            case 100:  // parkMode activation
                m_mode = RobotMode::PARK;
                return;
            default:
                m_mode = RobotMode::REMOTECONTROL;
                return;
        }
    }
}

String BTprocess::getBTData()
{
    return m_dataBT;
}

RobotMode BTprocess::getMode()
{
    return m_mode;
}

uint8_t BTprocess::getParameter1()
{
    return m_parameter1;
}

uint8_t BTprocess::getParameter2()
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