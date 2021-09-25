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

class BTprocess
{
private:
    String m_dataBT;
    StaticJsonDocument<150> m_elegooDoc;
    RobotMode m_mode;
    unsigned char m_parameter1;
    unsigned char m_parameter2;

public:
    BTprocess();
    ~BTprocess();
    void decodeElegooJSON();
    String getBTData();
    RobotMode getMode();
    unsigned char getParameter1();
    unsigned char getParameter2();
    void receiveBTData();
};

#endif