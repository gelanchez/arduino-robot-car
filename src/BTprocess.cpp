/**
 * @file BTprocess.cpp
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Library for receiving and processing the data from the serial bluetooth JSON.
 * @version 1.1.2
 * @date 2021-04-17
 * @copyright GPL-3.0
 */

#include <ArduinoJson.h>
#include "BTprocess.h"
#include "constants.h"

/**
 * @brief Construct a new BTprocess::BTprocess object.
 */
BTprocess::BTprocess()
    : m_dataBT{""}, m_mode{RobotMode::REMOTECONTROL}, // Default robot mode
      m_parameter1{0}, m_parameter2{0}
{
}

/**
 * @brief Destroy the BTprocess::BTprocess object.
 */
BTprocess::~BTprocess()
{
}

/**
 * @brief Decode Elegoo JSON object, setting the struct data.
 * Modes in bluetooth (Elegoo specifications):
 * {"N":5} square down bluetoothFollowing.
 * {"N":3,"D1":1} line tracking.
 * {"N":3,"D1":2} obstacle avoidance.
 * {"N":2,"D1":1..9} joystick.
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
                m_parameter1 = static_cast<unsigned char>(RemoteOrder::LEFT);
                return;
            case 2:
                m_parameter1 = static_cast<unsigned char>(RemoteOrder::RIGHT);
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
            case 6:
                m_parameter1 = static_cast<unsigned char>(RemoteOrder::FORWARD_LEFT);
                return;
            case 7:
                m_parameter1 = static_cast<unsigned char>(RemoteOrder::BACKWARD_LEFT);
                return;
            case 8:
                m_parameter1 = static_cast<unsigned char>(RemoteOrder::FORWARD_RIGHT);
                return;
            case 9:
                m_parameter1 = static_cast<unsigned char>(RemoteOrder::BACKWARD_RIGHT);
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

/**
 * @brief Return latest bluetooth data.
 * @return String bluetooth data.
 */
String BTprocess::getBTData() const
{
    return m_dataBT;
}

/**
 * @brief Return robot mode.
 * @return RobotMode.
 */
RobotMode BTprocess::getMode() const
{
    return m_mode;
}

/**
 * @brief Return first parameter of bluetooth communication.
 * @return unsigned char Parameter 1.
 */
unsigned char BTprocess::getParameter1() const
{
    return m_parameter1;
}

/**
 * @brief Return second parameter of bluetooth communication.
 * @return unsigned char Parameter 2.
 */
unsigned char BTprocess::getParameter2() const
{
    return m_parameter2;
}

/**
 * @brief Receive bluetooth data from Serial.
 */
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