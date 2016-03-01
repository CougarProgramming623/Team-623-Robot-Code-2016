/*
 * SubsystemInput.cpp
 *
 *  Created on: Feb 6, 2016
 *      Author: CougarRobotics
 */
#include "SubsystemInput.h"
#include "../RobotMap.h"

SubsystemInput::SubsystemInput() :
	Subsystem("Subsystem Input") {

	potentiometer = RobotMap::potentiometer;
	accelerometer = RobotMap::accelerometer;
	ultrasonicPing = RobotMap::ultrasonicPing;
	ultrasonicEcho = RobotMap::ultrasonicEcho;
	gyro = RobotMap::robotMap->gyro;
}

void
SubsystemInput::InitDefaultCommand() {

}

