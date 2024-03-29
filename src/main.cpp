/**
 * @file main.ino
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Main program.
 * @version 1.1.3
 * @date 2022-04-18
 * @copyright GPL-3.0
 */

#include "bluetooth.h"
#include "constants.h"
#include "robot.h"

static Robot g_robot = Robot();                     // Initialization of the Robot object
static Bluetooth g_bluetooth = Bluetooth();         // Initialization of the bluetooth object
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
    g_bluetooth.receiveData();
    if (g_bluetooth.getData() != "")
        g_bluetooth.decodeElegooJSON();
    if (g_mode != g_bluetooth.getMode())
        g_robot.restartState();

    switch (g_bluetooth.getMode())
    {
    case RobotMode::REMOTECONTROL:
        g_mode = RobotMode::REMOTECONTROL;
        g_robot.remoteControlMode(g_bluetooth.getOrder(), g_bluetooth.getSpeed(), g_bluetooth.getSpeed());
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
