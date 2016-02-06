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

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
SubsystemDrive* Robot::subsystemDrive = 0;
SubsystemInput* Robot::subsystemInput = 0;
OI* Robot::oi = 0;

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION

void Robot::RobotInit() {
	RobotMap::init();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	subsystemDrive = new SubsystemDrive();
	subsystemInput = new SubsystemInput();

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
	if (autonomousCommand != NULL)
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
	if (autonomousCommand != NULL)
		autonomousCommand->Cancel();
}

void Robot::TeleopPeriodic() {
	const double linear_threshold = .05;//Change if rotate speed too slow or too fast
	const double twist_threshold = .05;	//Change if rotate speed too slow or too fast
	Scheduler::GetInstance()->Run();
	//  Teleop Movement
	Joystick* joystick = oi->getJoystick1();
	double y = joystick->GetY(), twist = joystick->GetTwist();
	if (std::abs(y) > linear_threshold) {
		subsystemDrive->treadRightFront->Set(y);
		subsystemDrive->treadRightBack->Set(y);
		subsystemDrive->treadLeftFront->Set(y);
		subsystemDrive->treadLeftBack->Set(y);
	}
	if (std::abs(twist) > twist_threshold) {		//Left side already inverted
		subsystemDrive->treadRightFront->Set(twist);
		subsystemDrive->treadRightBack->Set(twist);
		subsystemDrive->treadLeftFront->Set(-twist);
		subsystemDrive->treadLeftBack->Set(-twist);
	}
//	DriverStation::ReportError("Y: "  + std::to_string(y) + "   Twist: " + std::to_string(twist) + "\n");
	DriverStation::ReportError("Potentiometer: " + std::to_string(subsystemInput->potentiometer->Get()) + "\n");
}

void Robot::TestPeriodic() {
	lw->Run();
}

START_ROBOT_CLASS(Robot);

