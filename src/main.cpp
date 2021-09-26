/**
 * @file main.ino
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Main program.
 * @version 1.1.1
 * @date 2021-09-25
 * @copyright GPL-3.0
 */

#include "BTprocess.h"
#include "constants.h"
#include "robot.h"

Robot robot = Robot();                     // Initialization of the Robot object
BTprocess BTproc = BTprocess();            // Initialization of the BT processor object
RobotMode mode = RobotMode::REMOTECONTROL; // Default mode

void setup()
{
    robot.begin();
    delay(Constants::serialDelay); // To make Serial work
}

void loop()
{
    BTproc.receiveBTData();
    if (BTproc.getBTData() != "")
        BTproc.decodeElegooJSON();
    if (mode != BTproc.getMode())
        robot.restartState();

    switch (BTproc.getMode())
    {
    case RobotMode::REMOTECONTROL:
        mode = RobotMode::REMOTECONTROL;
        robot.remoteControlMode(static_cast<RemoteOrder>(BTproc.getParameter1()));
        break;

    case RobotMode::IRCONTROL:
        mode = RobotMode::IRCONTROL;
        robot.IRControlMode();
        break;

    case RobotMode::OBSTACLEAVOIDANCE:
        mode = RobotMode::OBSTACLEAVOIDANCE;
        robot.obstacleAvoidanceMode();
        break;

    case RobotMode::LINETRACKING:
        mode = RobotMode::LINETRACKING;
        robot.lineTrackingMode();
        break;

    case RobotMode::PARK:
        robot.parkMode();
        mode = RobotMode::REMOTECONTROL;
        robot.restartState();
        break;

    case RobotMode::CUSTOM:
        robot.customMode();
        break;

    default:
        break;
    }
}
