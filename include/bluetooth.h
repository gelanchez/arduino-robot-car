/**
 * @file BTprocess.h
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Library for receiving and processing the data from the serial bluetooth JSON.
 * @version 1.1.1
 * @date 2021-09-25
 * @copyright GPL-3.0
 */

#ifndef BTPROCESS
#define BTPROCESS

#include <ArduinoJson.h>
#include "constants.h"

class Bluetooth
{
private:
    String m_data;
    StaticJsonDocument<150> m_elegooDoc;
    RobotMode m_mode;
    unsigned char m_parameter1;
    unsigned char m_parameter2;

public:
    Bluetooth();
    ~Bluetooth();
    void decodeElegooJSON();
    String getData() const;
    RobotMode getMode() const;
    unsigned char getParameter1() const;
    unsigned char getParameter2() const;
    void receiveData();
};

#endif