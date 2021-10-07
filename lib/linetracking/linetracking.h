/**
 * @file linetracking.h
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Library to handle the linetracking IR sensors.
 * @version 1.0.2
 * @date 2021-10-02
 * @copyright GPL-3.0
 */

#ifndef LINETRACKING_H
#define LINETRACKING_H

class LineTracking
{
private:
    unsigned char m_leftPin; // Left sensor pin
    unsigned char m_midPin; // Mid sensor pin
    unsigned char m_rightPin; // Right sensor pin
public:
    LineTracking(unsigned char leftPin, unsigned char midPin, unsigned char rightPin);
    ~LineTracking();
    bool allLines() const;
    bool anyLine() const;
    bool leftLine() const;
    bool midLine() const;
    void printLines() const;
    bool rightLine() const;
};

#endif