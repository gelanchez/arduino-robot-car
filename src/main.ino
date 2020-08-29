/**
 * @file main.ino
 * @author José Ángel Sánchez (https://github.com/gelanchez)
 * @brief Main program.
 * @version 1.0.2
 * @date 2020-08-29
 * @copyright GPL-3.0
 */

#include "BTprocess.h"
#include "constants.h"
#include "robot.h"
#include <ArduinoJson.h>

RobotControl Robot = RobotControl();  // Initialization of the RobotControl object
BTprocess BTproc = BTprocess();  // Initialization of the BT processor object

/**
 * @brief Structure storing the JSON data received, which keeps the mode of the robot.
 */
struct Data
{
    RobotMode mode = RobotMode::REMOTECONTROL;  // Default mode
    //RobotMode mode = RobotMode::CUSTOM;  // Default mode
    uint8_t parameter1 = 0;
    uint8_t paremter2 = 0;
    uint8_t speed = 0;
    uint8_t time = 0;
};

Data data;  // Creation of the struct data
StaticJsonDocument<150> elegooDoc;

/**
 * @brief Decode Elegoo JSON object, setting the struct data.
 * Modes in bluetooth (Elegoo specifications):
 * {"N":5} square down bluetoothFollowing
 * {"N":3,"D1":1} line tracking
 * {"N":3,"D1":2} obstacle avoidance
 * {"N":2,"D1":1...5} joystick
 */
void decodeElegooJSON(const String &dataBT)
{
    DeserializationError error = deserializeJson(elegooDoc, dataBT);
    if (!error)
    {
        uint8_t N = elegooDoc["N"];
        uint8_t D1;
        switch (N)  // See Elegoo specifications
        {
            case 2:  // remoteControlMode
                D1 = elegooDoc["D1"];
                switch (D1)
                {
                    case 1:
                        data.parameter1 = static_cast<uint8_t>(RemoteOrder::ROTATELEFT);
                        return;
                    case 2:
                        data.parameter1 = static_cast<uint8_t>(RemoteOrder::ROTATERIGHT);
                        return;
                    case 3:
                        data.parameter1 = static_cast<uint8_t>(RemoteOrder::FORWARD);
                        return;
                    case 4:
                        data.parameter1 = static_cast<uint8_t>(RemoteOrder::BACKWARD);
                        return;
                    case 5:
                        data.parameter1 = static_cast<uint8_t>(RemoteOrder::STOP);
                        return;
                    default:
                        data.parameter1 = static_cast<uint8_t>(RemoteOrder::UNKNOWN);
                        return;
                }
            case 3:  // lineTrackingMode or obstacleAvoidanceMode
                D1 = elegooDoc["D1"];
                switch (D1)
                    {
                    case 1:
                        if (data.mode != RobotMode::LINETRACKING)
                        {
                            Robot.restartState();
                            data.mode = RobotMode::LINETRACKING;
                        }
                        return;
                    case 2:
                        if (data.mode != RobotMode::OBSTACLEAVOIDANCE)
                        {
                            Robot.restartState();   
                            data.mode = RobotMode::OBSTACLEAVOIDANCE;
                        }
                        return;                   
                    default:
                        return;
                }
            case 5:  // IRControlMode mode activation or deactivation (deactivate other modes)
                if (data.mode == RobotMode::REMOTECONTROL)
                    {
                        Robot.restartState();
                        data.mode = RobotMode::IRCONTROL;
                        Robot.m_IRreceiver.enable();
                        return;
                    }
                else
                    {
                        Robot.restartState();
                        data.mode = RobotMode::REMOTECONTROL;
                        return;
                    }            
            case 100:  // parkMode activation
                data.mode = RobotMode::PARK;
                return;
            default:
                data.mode = RobotMode::REMOTECONTROL;
                return;
        }
    }
}

void setup() 
{
    Robot.begin();
    delay(500);  // To make Serial work
}

void loop()
{
    String dataBT = BTproc.getBTData();
    if (dataBT != "")
        decodeElegooJSON(dataBT);

    switch (data.mode)
    {
        case RobotMode::REMOTECONTROL:
            Robot.remoteControlMode(static_cast<RemoteOrder>(data.parameter1));
            break;
        
        case RobotMode::IRCONTROL:
            Robot.IRControlMode();
            break;
        
        case RobotMode::OBSTACLEAVOIDANCE:
            Robot.obstacleAvoidanceMode();
            break;
        
        case RobotMode::LINETRACKING:
            Robot.lineTrackingMode();
            break;

        case RobotMode::PARK:
            Robot.parkMode();
            data.mode = RobotMode::REMOTECONTROL;
            Robot.restartState();
            break;
        
        case RobotMode::CUSTOM:
            Robot.customMode();
            break;
        
        default:
            break;
    }
}
