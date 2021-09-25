/**
 * @file infrared.cpp
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Library for receiving data from the IR sensor.
 * @version 1.1.1
 * @date 2021-09-25
 * @copyright GPL-3.0
 */

#include "constants.h"
#include "infrared.h"
#include <IRremote.h>

Infrared::Infrared() : m_previousKey{0xFFFFFFFF}
{
}

Infrared::~Infrared()
{
}

void Infrared::begin()
{
    IrReceiver.begin(Pins::IRPin, DISABLE_LED_FEEDBACK);
}

RemoteOrder Infrared::decodeIR()
{
    if (IrReceiver.decode())
    {
        unsigned long pressedKey = IrReceiver.decodedIRData.decodedRawData;
        IrReceiver.resume();

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