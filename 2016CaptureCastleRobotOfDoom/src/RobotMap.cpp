// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION
SpeedController* RobotMap::robotDriveTreadRightFront = NULL;
SpeedController* RobotMap::robotDriveTreadRightBack = NULL;
SpeedController* RobotMap::robotDriveTreadLeftFront = NULL;
SpeedController* RobotMap::robotDriveTreadLeftBack = NULL;
SpeedController* RobotMap::ballShooterSpinnerClockwise = NULL;
SpeedController* RobotMap::ballShooterSpinnerCounterclockwise = NULL;
SpeedController* RobotMap::ballShooterSpinnerSpringWinder = NULL;
SpeedController* RobotMap::lifter = NULL;
SpeedController* RobotMap::position = NULL;

RobotDrive* RobotMap::robotDrive41 = NULL;
RobotDrive* RobotMap::shooter = NULL;

AnalogPotentiometer* RobotMap::potentiometer = NULL;
AnalogAccelerometer* RobotMap::accelerometer = NULL;
AnalogGyro* RobotMap::gyro = NULL;

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION

void RobotMap::init() {
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	LiveWindow* lw = LiveWindow::GetInstance();

	//NOTE: This is where you set the where the wire on RoboRIO goes

	//Sensors
	accelerometer = new AnalogAccelerometer(ACCELEROMETER);
	potentiometer = new AnalogPotentiometer(POTENTIOMETER);
//	gyro = new AnalogGyro(GYRO); // TODO: Ask Tom

	//Drive
	robotDriveTreadRightFront = new Talon(FRONT_RIGHT);
	lw->AddActuator("Robot Drive" , "treadRightFront" ,	//NOTE 2-10-16: The mechanical people unplugged all of the wires on the RoboRIO, so they will ALL need to be RESET
	(Talon*) robotDriveTreadRightFront);

	robotDriveTreadRightBack = new Talon(BACK_RIGHT);
	lw->AddActuator("Robot Drive" , "treadRightBack" , (Talon*) robotDriveTreadRightBack);

	robotDriveTreadLeftFront = new Talon(FRONT_LEFT);
	lw->AddActuator("Robot Drive" , "treadLeftFront" , (Talon*) robotDriveTreadLeftFront);

	robotDriveTreadLeftBack = new Talon(BACK_LEFT);
	lw->AddActuator("Robot Drive" , "treadLeftBack" , (Talon*) robotDriveTreadLeftBack);

	robotDrive41 = new RobotDrive(robotDriveTreadLeftFront , robotDriveTreadLeftBack , robotDriveTreadRightFront , robotDriveTreadRightBack);

	robotDrive41->SetSafetyEnabled(true);
	robotDrive41->SetExpiration(0.1);
	robotDrive41->SetSensitivity(0.5);
	robotDrive41->SetMaxOutput(1.0);
	robotDrive41->SetInvertedMotor(RobotDrive::kFrontRightMotor , true);
	robotDrive41->SetInvertedMotor(RobotDrive::kRearRightMotor , true);

	//Ball Shooter
	ballShooterSpinnerClockwise = new Talon(SPINNER_CW);
	lw->AddActuator("Ball Shooter" , "clockwise spinner" , (Talon*) ballShooterSpinnerClockwise);

	ballShooterSpinnerCounterclockwise = new Talon(SPINNER_CCW);
	lw->AddActuator("Ball Shooter" , "clockwise spinner" , (Talon*) ballShooterSpinnerCounterclockwise);

	ballShooterSpinnerSpringWinder = new Talon(SPINNER_SPRING_WINDER);
	lw->AddActuator("Ball Shooter" , "spinner spring winder" , (Talon*) ballShooterSpinnerSpringWinder);

	shooter = new RobotDrive(ballShooterSpinnerClockwise , ballShooterSpinnerCounterclockwise , NULL , NULL);

	shooter->SetSafetyEnabled(true);
	shooter->SetExpiration(0.1);
	shooter->SetSensitivity(0.5);
	shooter->SetMaxOutput(0.5);
	shooter->SetInvertedMotor(RobotDrive::kRearLeftMotor , true);

	lifter = new Talon(LIFTER);
	lw->AddActuator("MCL" , "lifter" , (Talon*) lifter);

	position = new Talon(POSITION);
	lw->AddActuator("MCL" , "position" , (Talon*) position);

	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}
