/**
 * @file bluetooth.h
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Library for receiving and processing the data from the serial bluetooth JSON.
 * @version 1.2.0
 * @date 2022-04-18
 * @copyright GPL-3.0
 */

#ifndef BLUETOOTH
#define BLUETOOTH

#include <ArduinoJson.h>
#include "constants.h"

class Bluetooth
{
private:
    String m_data;
    StaticJsonDocument<150> m_elegooDoc;
    RobotMode m_mode;
    Order m_order;
    unsigned short m_speed;

public:
    Bluetooth();
    ~Bluetooth();
    void decodeElegooJSON();
    String getData() const;
    RobotMode getMode() const;
    Order getOrder() const;
    unsigned short getSpeed() const;
    void receiveData();
};

#endif