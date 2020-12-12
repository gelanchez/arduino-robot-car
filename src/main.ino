/**
 * @file main.ino
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Main program.
 * @version 1.1.0
 * @date 2020-08-30
 * @copyright GPL-3.0
 */

#include "BTprocess.h"
#include "constants.h"
#include "robot.h"

RobotControl Robot = RobotControl();  // Initialization of the RobotControl object
BTprocess BTproc = BTprocess();  // Initialization of the BT processor object
RobotMode mode = RobotMode::REMOTECONTROL;  // Default mode

void setup() 
{
    Robot.begin();
    delay(500);  // To make Serial work
}

void loop()
{
    BTproc.receiveBTData();
    if (BTproc.getBTData() != "")
        BTproc.decodeElegooJSON();
    if (mode != BTproc.getMode())
        Robot.restartState();

    switch (BTproc.getMode())
    {
        case RobotMode::REMOTECONTROL:
            mode = RobotMode::REMOTECONTROL;
            Robot.remoteControlMode(static_cast<RemoteOrder>(BTproc.getParameter1()));
            break;
        
        case RobotMode::IRCONTROL:
            mode = RobotMode::IRCONTROL;
            Robot.m_IRreceiver.enable();
            Robot.IRControlMode();
            break;
        
        case RobotMode::OBSTACLEAVOIDANCE:
            mode = RobotMode::OBSTACLEAVOIDANCE;
            Robot.obstacleAvoidanceMode();
            break;
        
        case RobotMode::LINETRACKING:
            mode = RobotMode::LINETRACKING;
            Robot.lineTrackingMode();
            break;

        case RobotMode::PARK:
            Robot.parkMode();
            mode = RobotMode::REMOTECONTROL;
            Robot.restartState();
            break;
        
        case RobotMode::CUSTOM:
            Robot.customMode();
            break;
        
        default:
            break;
    }
}
