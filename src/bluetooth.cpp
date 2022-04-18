/**
 * @file bluetooth.cpp
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Library for receiving and processing the data from the serial bluetooth JSON.
 * @version 1.2.0
 * @date 2021-04-18
 * @copyright GPL-3.0
 */

#include <ArduinoJson.h>
#include "bluetooth.h"
#include "constants.h"

/**
 * @brief Construct a new Bluetooth::Bluetooth object.
 */
Bluetooth::Bluetooth()
    : m_data{""}, m_mode{RobotMode::REMOTECONTROL}, // Default robot mode
      m_order{Order::STOP}, m_speed{0}
{
}

/**
 * @brief Destroy the Bluetooth::Bluetooth object.
 */
Bluetooth::~Bluetooth()
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
void Bluetooth::decodeElegooJSON()
{
    DeserializationError error = deserializeJson(m_elegooDoc, m_data);
    if (!error)
    {
        unsigned char N = m_elegooDoc["N"];
        unsigned char D1;
        switch (N) // See Elegoo specifications
        {
        case 2: // remoteControlMode
            m_mode = RobotMode::REMOTECONTROL;
            D1 = m_elegooDoc["D1"];
            m_speed = m_elegooDoc["D2"];
            switch (D1)
            {
            case 1:
                m_order = Order::LEFT;
                return;
            case 2:
                m_order = Order::RIGHT;
                return;
            case 3:
                m_order = Order::FORWARD;
                return;
            case 4:
                m_order = Order::BACKWARD;
                return;
            case 5:
                m_order = Order::STOP;
                return;
            case 6:
                m_order = Order::FORWARD_LEFT;
                return;
            case 7:
                m_order = Order::BACKWARD_LEFT;
                return;
            case 8:
                m_order = Order::FORWARD_RIGHT;
                return;
            case 9:
                m_order = Order::BACKWARD_RIGHT;
                return;
            default:
                m_order = Order::UNKNOWN;
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
String Bluetooth::getData() const
{
    return m_data;
}

/**
 * @brief Return robot mode.
 * @return RobotMode.
 */
RobotMode Bluetooth::getMode() const
{
    return m_mode;
}

/**
 * @brief Return remote order.
 * @return Order.
 */
Order Bluetooth::getOrder() const
{
    return m_order;
}

/**
 * @brief Return requested speed.
 * @return int Requested speed.
 */
unsigned short Bluetooth::getSpeed() const
{
    return m_speed;
}

/**
 * @brief Receive bluetooth data from Serial.
 */
void Bluetooth::receiveData()
{
    m_data = "";
    while ((Serial.available() > 0) && (m_data.endsWith("}") == false))
    {
        m_data += static_cast<char>(Serial.read());
        delay(3);
    }
    if ((m_data.length() > 0) && m_data.endsWith("}"))
        return;
    else
        m_data = "";
}