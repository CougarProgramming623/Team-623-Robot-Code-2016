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
}

void SubsystemInput::InitDefaultCommand() {

}

