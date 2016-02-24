// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#ifndef _ROBOT_H
#define _ROBOT_H

#include "WPILib.h"
#include "Commands/Command.h"
#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "Commands/AutonomousCommand.h"
#include "Subsystems/SubsystemDrive.h"
#include "Subsystems/SubsystemInput.h"
#include "Subsystems/SubsystemBallShooter.h"

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "OI.h"

#define SAD_UP_POT 0
#define SAD_DOWN_POT 0
#define GRAVITY 9.82
#define MAX_REVOLUTIONS 0 //TODO: Get number of revolutions to lift robot
#define ROBOT_AUTO 1

class Robot : public IterativeRobot {
	public:
		Command *autonomousCommand;
		static OI *oi;
		LiveWindow *lw;
		// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
		static SubsystemDrive* subsystemDrive;
		static SubsystemInput* subsystemInput;
		static SubsystemBallShooter* subsystemBallShooter;
		double potentiometer_zero;

		// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
		virtual void RobotInit();
		virtual void DisabledInit();
		virtual void DisabledPeriodic();
		virtual void AutonomousInit();
		virtual void AutonomousPeriodic();
		virtual void TeleopInit();
		virtual void TeleopPeriodic();
		virtual void TestPeriodic();
		double getPoteniometerValue();
		void shoot();
		void turnRobot(double);
		void turnRobot(double , double);
		void moveRobotLinear(double);
		void moveRobotLinear(double, double);
		void stopRobot();
};
#endif
