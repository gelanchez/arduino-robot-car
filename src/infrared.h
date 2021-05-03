/**
 * @file infrared.h
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Library for receiving data from the IR sensor.
 * @version 1.1.0
 * @date 2021-05-03
 * @copyright GPL-3.0
 */

#ifndef INFRARED_H
#define INFRARED_H

// To avoid using old versions of Arduino IDE, which used WPProgram.h instead or Arduino.h
// Also possible #define IRPRONTO
#ifndef ARDUINO
#define ARDUINO 108012 // Arduino IDE version used when writing the program
#endif

#include "constants.h"

class Infrared
{
private:
    unsigned long m_previousKey; // Store previous order for repeating key

public:
    Infrared();
    ~Infrared();
    void begin();
    RemoteOrder decodeIR();
};

#endif