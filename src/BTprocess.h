/**
 * @file BTprocess.h
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Library for receiving and processing the data from the serial bluetooth JSON.
 * @version 1.1.0
 * @date 2020-08-30
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
        uint8_t m_parameter1;
        uint8_t m_parameter2;

    public:
        BTprocess();
        ~BTprocess();
        void decodeElegooJSON();
        String getBTData();
        RobotMode getMode();
        uint8_t getParameter1();
        uint8_t getParameter2();
        void receiveBTData();
};

#endif