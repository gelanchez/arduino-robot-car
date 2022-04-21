/**
 * @file linetracking.cpp
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Library to handle the linetracking IR sensors.
 * @version 1.0.2
 * @date 2021-10-02
 * @copyright GPL-3.0
 */

#include <Arduino.h>
#include "linetracking.h"

/**
 * @brief Construct a new Line Tracking::Line Tracking object.
 * @param leftPin Left sensor pin.
 * @param midPin Mid sensor pin.
 * @param rightPin Right sensor pin.
 */
LineTracking::LineTracking(unsigned char leftPin, unsigned char midPin, unsigned char rightPin)
: m_leftPin{leftPin}, m_midPin{midPin}, m_rightPin{rightPin}
{
    pinMode(leftPin, INPUT);
    pinMode(midPin, INPUT);
    pinMode(rightPin, INPUT);
}

/**
 * @brief Destroy the Line Tracking::Line Tracking object.
 */
LineTracking::~LineTracking()
{
}

/**
 * @brief Check all sensor lines status.
 * @return true All sensors ON.
 * @return false Not all sensors ON.
 */
bool LineTracking::allLines() const
{
    return (leftLine() && midLine() && rightLine());
}

/**
 * @brief Check all sensor lines status.
 * @return true Any sensors ON.
 * @return false All sensors OFF.
 */
bool LineTracking::anyLine() const
{
    return (leftLine() || midLine() || rightLine());
}

/**
 * @brief Check left sensor.
 * @return true Line detected.
 * @return false No line detected.
 */
bool LineTracking::leftLine() const
{
    return !digitalRead(m_leftPin);
}

/**
 * @brief Check mid sensor.
 * @return true Line detected.
 * @return false No line detected.
 */
bool LineTracking::midLine() const
{
    return !digitalRead(m_midPin);
}

/**
 * @brief Print current status of all sensors.
 */
void LineTracking::printLines() const
{
    Serial.print(leftLine());
    Serial.print(" ");
    Serial.print(midLine());
    Serial.print(" ");
    Serial.print(rightLine());
    Serial.println();
}

/**
 * @brief Check right sensor.
 * @return true Line detected.
 * @return false No line detected.
 */
bool LineTracking::rightLine() const
{
    return !digitalRead(m_rightPin);
}