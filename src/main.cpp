/**
 * @file main.ino
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Main program.
 * @version 1.1.2
 * @date 2021-09-26
 * @copyright GPL-3.0
 */

#include "BTprocess.h"
#include "constants.h"
#include "robot.h"

static Robot g_robot = Robot();                     // Initialization of the Robot object
static BTprocess g_BTprocess = BTprocess();         // Initialization of the BT processor object
static RobotMode g_mode = RobotMode::REMOTECONTROL; // Default robot mode

/**
 * @brief Main setup. Initialize robot.
 */
void setup()
{
    g_robot.begin();
    delay(Constants::serialDelay); // To make Serial work
}

/**
 * @brief Main loop. Process bluetooth order and run the mode.
 */
void loop()
{
    g_BTprocess.receiveBTData();
    if (g_BTprocess.getBTData() != "")
        g_BTprocess.decodeElegooJSON();
    if (g_mode != g_BTprocess.getMode())
        g_robot.restartState();

    switch (g_BTprocess.getMode())
    {
    case RobotMode::REMOTECONTROL:
        g_mode = RobotMode::REMOTECONTROL;
        g_robot.remoteControlMode(static_cast<RemoteOrder>(g_BTprocess.getParameter1()));
        break;

    case RobotMode::IRCONTROL:
        g_mode = RobotMode::IRCONTROL;
        g_robot.IRControlMode();
        break;

    case RobotMode::OBSTACLEAVOIDANCE:
        g_mode = RobotMode::OBSTACLEAVOIDANCE;
        g_robot.obstacleAvoidanceMode();
        break;

    case RobotMode::LINETRACKING:
        g_mode = RobotMode::LINETRACKING;
        g_robot.lineTrackingMode();
        break;

    case RobotMode::PARK:
        g_robot.parkMode();
        g_mode = RobotMode::REMOTECONTROL;
        g_robot.restartState();
        break;

    case RobotMode::CUSTOM:
        g_robot.customMode();
        break;

    default:
        break;
    }
}
