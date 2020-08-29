/**
 * @file BTprocess.h
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Library for receiving and processing the data from the serial bluetooth.
 * @version 1.0.0
 * @date 2020-08-29
 * @copyright GPL-3.0
 */

#ifndef BTPROCESS
#define BTPROCESS

class BTprocess
{
    private:
        String m_dataBT = "";
    
    public:
        BTprocess();
        ~BTprocess();
        String getBTData();
};

#endif