/**
 * @file infrared.cpp
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Library for receiving data from the IR sensor.
 * @version 1.1.2
 * @date 2022-04-17
 * @copyright GPL-3.0
 */

#include <IRremote.hpp>
#include "constants.h"
#include "infrared.h"

/**
 * @brief Construct a new Infrared::Infrared object.
 */
Infrared::Infrared() : m_previousKey{0}
{
}

/**
 * @brief Destroy the Infrared::Infrared object.
 */
Infrared::~Infrared()
{
}

/**
 * @brief Start the IR receiver.
 */
void Infrared::begin()
{
    IrReceiver.begin(Pins::IRPin, DISABLE_LED_FEEDBACK);
}

/**
 * @brief Decode orcer received.
 * @return RemoteOrder.
 */
RemoteOrder Infrared::decodeIR()
{
    if (IrReceiver.decode())
    {
        unsigned long pressedKey = IrReceiver.decodedIRData.decodedRawData;
        IrReceiver.resume();

        if (pressedKey == 0) // Repeat previous key
            pressedKey = m_previousKey;
        else
            m_previousKey = pressedKey; // Update previous key to current key

        switch (pressedKey)
        {
        case Constants::keyOk:
            return RemoteOrder::STOP;
        case Constants::keyUp:
            return RemoteOrder::FORWARD;
        case Constants::keyDown:
            return RemoteOrder::BACKWARD;
        case Constants::keyLeft:
            return RemoteOrder::LEFT;
        case Constants::keyRight:
            return RemoteOrder::RIGHT;
        default:
            return RemoteOrder::UNKNOWN;
        }
    }
    return RemoteOrder::UNKNOWN;
}