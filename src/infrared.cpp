/**
 * @file infrared.cpp
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Library for receiving data from the IR sensor.
 * @version 1.1.0
 * @date 2021-05-03
 * @copyright GPL-3.0
 */

#include "constants.h"
#include "infrared.h"

Infrared::Infrared() : m_irrecv{Constants::IRPin}, m_isEnabled{false},
                       m_previousKey{0xFFFFFFFF} // Member initializer lists; it can't go inside the constructor
{
}

Infrared::~Infrared()
{
}

void Infrared::enable()
{
    if (!m_isEnabled)
    {
        m_irrecv.enableIRIn();
        m_irrecv.blink13(false); // Disable blinking the LED 13 during reception
        m_isEnabled = true;
    }
}

RemoteOrder Infrared::decodeIR()
{
    if (m_irrecv.decode(&m_results))
    {
        unsigned long pressedKey = m_results.value;
        m_irrecv.resume();

        if (pressedKey == 0xFFFFFFFF) // Repeat previous key
            pressedKey = m_previousKey;
        else
            m_previousKey = pressedKey; // Update previous key to current key

        switch (pressedKey)
        {
        case Constants::okKey:
            return RemoteOrder::STOP;
        case Constants::upKey:
            return RemoteOrder::FORWARD;
        case Constants::downKey:
            return RemoteOrder::BACKWARD;
        case Constants::leftKey:
            return RemoteOrder::ROTATELEFT;
        case Constants::rightKey:
            return RemoteOrder::ROTATERIGHT;
        default:
            return RemoteOrder::UNKNOWN;
        }
    }
    return RemoteOrder::UNKNOWN;
}