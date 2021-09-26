/**
 * @file linetracking.h
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Library to handle the linetracking IR sensors.
 * @version 1.0.1
 * @date 2021-09-25
 * @copyright GPL-3.0
 */

#ifndef LINETRACKING_H
#define LINETRACKING_H

class LineTracking
{
private:
public:
    LineTracking();
    ~LineTracking();
    bool leftLine() const;
    bool midLine() const;
    bool rightLine() const;
    bool anyLine() const;
    bool allLines() const;
    void printLines() const;
};

#endif