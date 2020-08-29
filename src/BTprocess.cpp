/**
 * @file BTprocess.cpp
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Library for receiving and processing the data from the serial bluetooth.
 * @version 1.0.0
 * @date 2020-08-29
 * @copyright GPL-3.0
 */

#include "BTprocess.h"

BTprocess::BTprocess()
{
}

BTprocess::~BTprocess()
{
}

String BTprocess::getBTData()
{
    m_dataBT = "";
    while ((Serial.available() > 0) && (m_dataBT.endsWith("}") == false))
    {
        m_dataBT += static_cast<char>(Serial.read());
        delay(3);
    }
    if ((m_dataBT.length() > 0) && m_dataBT.endsWith("}"))
        return m_dataBT;
    else
        return "";
}