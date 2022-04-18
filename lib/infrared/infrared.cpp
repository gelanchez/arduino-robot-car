/**
 * @file infrared.cpp
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Library for receiving and processing data from the IR sensor.
 * @version 1.2.0
 * @date 2022-04-18
 * @copyright GPL-3.0
 */

#include <IRremote.hpp>
#include "infrared.h"

/**
 * @brief Construct a new Infrared::Infrared object.
 * @param IRPin IR receiver pin.
 */
Infrared::Infrared(unsigned char IRPin) : m_IRPin{IRPin}, m_previousKey{0}
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
    IrReceiver.begin(m_IRPin, DISABLE_LED_FEEDBACK);
}

/**
 * @brief Decode pressed key.
 * @return Key.
 */
Key Infrared::decodeIR()
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
        case 3208707840:
            return Key::keyOk;
        case 3108437760:
            return Key::keyUp;
        case 3927310080:
            return Key::keyDown;
        case 3141861120:
            return Key::keyLeft;
        case 3158572800:
            return Key::keyRight;
        case 2907897600:
            return Key::key0;
        case 3910598400:
            return Key::key1;
        case 3860463360:
            return Key::key2;
        case 4061003520:
            return Key::key3;
        case 4077715200:
            return Key::key4;
        case 3877175040:
            return Key::key5;
        case 2707357440:
            return Key::key6;
        case 4144561920:
            return Key::key7;
        case 3810328320:
            return Key::key8;
        case 2774204160:
            return Key::key9;
        case 3175284480:
            return Key::keyAsterisk;
        case 3041591040:
            return Key::keySharp;
        default:
            return Key::unkwown;
        }
    }
    return Key::unkwown;
}