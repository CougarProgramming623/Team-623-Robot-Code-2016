// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#include "Robot.h"
#include "Subsystems/ButtonBoard.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
SubsystemDrive* Robot::subsystemDrive = NULL;
SubsystemInput* Robot::subsystemInput = NULL;
SubsystemBallShooter* Robot::subsystemBallShooter = NULL;
OI* Robot::oi = 0;

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION

void Robot::RobotInit() {
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	subsystemDrive = new SubsystemDrive();
	subsystemInput = new SubsystemInput();
	subsystemBallShooter = new SubsystemBallShooter();

	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	// This MUST be here. If the OI creates Commands (which it very likely
	// will), constructing it during the construction of CommandBase (from
	// which commands extend), subsystems are not guaranteed to be
	// yet. Thus, their requires() statements may grab null pointers. Bad
	// news. Don't move it.
	oi = new OI();
	lw = LiveWindow::GetInstance();

	// instantiate the command used for the autonomous period
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
	autonomousCommand = new AutonomousCommand();

	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
}

/**
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */
void Robot::DisabledInit() {

}

void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	if(autonomousCommand != NULL)
		autonomousCommand->Start();
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to 
	// continue until interrupted by another command, remove
	// these lines or comment it out.
	if(autonomousCommand != NULL)
		autonomousCommand->Cancel();
}

void Robot::TeleopPeriodic() {
	const double linear_threshold = .05;	//NOTE:Change if rotate speed too slow or too fast
	const double twist_threshold = .05;	//NOTE: Change if rotate speed too slow or too fast
	Scheduler::GetInstance()->Run();
	//  Teleop Movement
	Joystick* joystick = oi->getJoystick1();
	double y = joystick->GetY() , twist = joystick->GetTwist();
	if(std::abs(y) > linear_threshold) {
		subsystemDrive->treadRightFront->Set(y);
		subsystemDrive->treadRightBack->Set(y);
		subsystemDrive->treadLeftFront->Set(y);
		subsystemDrive->treadLeftBack->Set(y);
	}
	if(std::abs(twist) > twist_threshold) {		//Left side of Robot already inverted (inverted in RobotBuilder)
		subsystemDrive->treadRightFront->Set(twist);
		subsystemDrive->treadRightBack->Set(twist);
		subsystemDrive->treadLeftFront->Set(-twist);
		subsystemDrive->treadLeftBack->Set(-twist);
	}

	//The Button of the All Mighty Board of Buttons
	ButtonBoard* btnBoard = oi->getBtnBoard();
	if(btnBoard->getPickupUp()) {
		subsystemBallShooter->spinnerCounterclockwise->Set(0);
		subsystemBallShooter->spinnerClockwise->Set(0);
//		TODO: Create something to move pickup up and down
	}

	if(btnBoard->getPickupDown()) {
		subsystemBallShooter->spinnerCounterclockwise->Set(-.5);
		subsystemBallShooter->spinnerClockwise->Set(-.5);
	}

	if(btnBoard->getShoot()) {
		subsystemBallShooter->spinnerCounterclockwise->Set(.5);
		subsystemBallShooter->spinnerClockwise->Set(.5);
		Wait(500);
		subsystemBallShooter->spinnerSpringWinder->Set(1);
		Wait(1000);
		subsystemBallShooter->spinnerSpringWinder->Set(0);
		subsystemBallShooter->spinnerCounterclockwise->Set(0);
		subsystemBallShooter->spinnerClockwise->Set(0);
	}
	if(btnBoard->getPos() != POS_NONE) {
		// TODO: Find values for potentiometers and replace 0s
		float newValue = RobotMap::robotMap->potentiometer->Get();
		switch(btnBoard->getPos()) {
			case POS_OBSTACLE:
				newValue = 0;
				break;
			case POS_BALL_PICKUP:
				newValue = 0;
				break;
			case POS_DEFAULT:
				newValue = 0;
				break;
			case POS_SHOOTING:
				newValue = 0;
				break;
			case POS_SAFTEY:
				newValue = 0;
				break;
		}
		float currentValue = RobotMap::robotMap->potentiometer->Get();
		float power = newValue - currentValue;
		if(power != 0) {
			RobotMap::robotMap->position->Set(power);
			//TODO: potentiometer value check
		}
	}
	if(btnBoard->getLifterPos() != LIFTER_POS_NONE) {
		// TODO: Find values for encoder and replace 0s
		float newValue = RobotMap::robotMap->potentiometer->Get();
		switch(btnBoard->getLifterPos()) {
			case LIFTER_POS_RELEASE:
				newValue = 0;
				break;
			case LIFTER_POS_UP:
				newValue = 0;
				break;
			case LIFTER_POS_DOWN:
				newValue = 0;
				break;
		}
		float currentValue = RobotMap::robotMap->potentiometer->Get();
		float power = newValue - currentValue;
		if(power < 0)
			power = -1;
		else if(power > 0)
			power = 1;
		else
			power = 0;
		RobotMap::robotMap->lifter->Set(power);
		//TODO: ENCODER COUNTER
		RobotMap::robotMap->lifter->Set(0);
	}
//	DriverStation::ReportError("Y: "  + std::to_string(y) + "   Twist: " + std::to_string(twist) + "\n"); //OLD: Used for making sure the wheels are set correctly
//	DriverStation::ReportError("Potentiometer: " + std::to_string(subsystemInput->potentiometer->Get()) + "\n"); //Used to test Potentiometer
}

void Robot::TestPeriodic() {
	lw->Run();
}

START_ROBOT_CLASS(Robot);

