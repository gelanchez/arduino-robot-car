/**
 * @file IRreceiver.h
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Library for receiving data from the IR sensor.
 * @version 1.0.0
 * @date 2020-08-22
 * @copyright GPL-3.0
 */

#ifndef IRRECEIVER_H
#define IRRECEIVER_H

// To avoid using old versions of Arduino IDE, which used WPProgram.h instead or Arduino.h
// Also possible #define IRPRONTO
#ifndef ARDUINO
    #define ARDUINO 108012  // Arduino IDE version used when writing the program
#endif

#include "constants.h"
#include <IRremote.h>

class IRreceiver
{
    private:
        IRrecv m_irrecv;  // Receiver object
        bool m_isEnabled;
        decode_results m_results;  // Struct to store the received information
        unsigned long m_previousKey;  // Store previous order for repeating key

    public:
        IRreceiver();
        ~IRreceiver();
        void enable();
        RemoteOrder decodeIR();
};

#endif