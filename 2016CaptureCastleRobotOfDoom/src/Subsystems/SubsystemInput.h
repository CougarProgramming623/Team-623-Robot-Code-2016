/*
 * SubsystemInput.h
 *
 *  Created on: Feb 6, 2016
 *      Author: CougarRobotics
 */

#ifndef SRC_SUBSYSTEMS_SUBSYSTEMINPUT_H_
#define SRC_SUBSYSTEMS_SUBSYSTEMINPUT_H_
#include "Commands/Subsystem.h"
#include "WPILib.h"

class SubsystemInput : public Subsystem {
	public:
		AnalogPotentiometer* potentiometer;
		AnalogAccelerometer* accelerometer;
		AnalogGyro* gyro;
		SubsystemInput();
		void InitDefaultCommand();
};

#endif /* SRC_SUBSYSTEMS_SUBSYSTEMINPUT_H_ */
