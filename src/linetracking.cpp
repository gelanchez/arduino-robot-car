/**
 * @file linetracking.cpp
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Library to handle the linketracking sensors.
 * @version 1.0.0
 * @date 2020-08-22
 * @copyright GPL-3.0
 */

#include "constants.h"
#include "linetracking.h"

LineTracking::LineTracking()
{
    pinMode(Constants::ltLeftPin, INPUT);
    pinMode(Constants::ltMidPin, INPUT);
    pinMode(Constants::ltRightPin, INPUT);
}

LineTracking::~LineTracking()
{
}

bool LineTracking::leftLine()
{
    return !digitalRead(Constants::ltLeftPin);
}

bool LineTracking::midLine()
{
    return !digitalRead(Constants::ltMidPin);
}

bool LineTracking::rightLine()
{
    return !digitalRead(Constants::ltRightPin);
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