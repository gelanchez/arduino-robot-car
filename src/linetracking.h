/**
 * @file linetracking.h
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Library to handle the linketracking sensors.
 * @version 1.0.0
 * @date 2020-08-22
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
        bool leftLine();
        bool midLine();
        bool rightLine();
        bool anyLine();
        bool allLines();
        void printLines();
};


#endif