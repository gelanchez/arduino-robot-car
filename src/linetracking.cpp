/**
 * @file linetracking.cpp
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Library to handle the linetracking IR sensors.
 * @version 1.0.1
 * @date 2021-09-25
 * @copyright GPL-3.0
 */

#include "constants.h"
#include "linetracking.h"

LineTracking::LineTracking()
{
    pinMode(Pins::ltLeftPin, INPUT);
    pinMode(Pins::ltMidPin, INPUT);
    pinMode(Pins::ltRightPin, INPUT);
}

LineTracking::~LineTracking()
{
}

bool LineTracking::leftLine()
{
    return !digitalRead(Pins::ltLeftPin);
}

bool LineTracking::midLine()
{
    return !digitalRead(Pins::ltMidPin);
}

bool LineTracking::rightLine()
{
    return !digitalRead(Pins::ltRightPin);
}

bool LineTracking::anyLine()
{
    return (leftLine() || midLine() || rightLine());
}

bool LineTracking::allLines()
{
    return (leftLine() && midLine() && rightLine());
}

void LineTracking::printLines()
{
    Serial.print(leftLine());
    Serial.print(" ");
    Serial.print(midLine());
    Serial.print(" ");
    Serial.print(rightLine());
    Serial.println();
}