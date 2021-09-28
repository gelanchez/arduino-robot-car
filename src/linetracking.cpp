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

bool LineTracking::allLines() const
{
    return (leftLine() && midLine() && rightLine());
}

bool LineTracking::anyLine() const
{
    return (leftLine() || midLine() || rightLine());
}

bool LineTracking::leftLine() const
{
    return !digitalRead(Pins::ltLeftPin);
}

bool LineTracking::midLine() const
{
    return !digitalRead(Pins::ltMidPin);
}

void LineTracking::printLines() const
{
    Serial.print(leftLine());
    Serial.print(" ");
    Serial.print(midLine());
    Serial.print(" ");
    Serial.print(rightLine());
    Serial.println();
}

bool LineTracking::rightLine() const
{
    return !digitalRead(Pins::ltRightPin);
}