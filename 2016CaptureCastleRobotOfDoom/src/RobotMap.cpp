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
#include "AnalogGyro.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION
SpeedController* RobotMap::robotDriveTreadRightFront = nullptr;
SpeedController* RobotMap::robotDriveTreadRightBack = nullptr;
SpeedController* RobotMap::robotDriveTreadLeftFront = nullptr;
SpeedController* RobotMap::robotDriveTreadLeftBack = nullptr;
SpeedController* RobotMap::ballShooterSpinnerClockwise = nullptr;
SpeedController* RobotMap::ballShooterSpinnerCounterclockwise = nullptr;
SpeedController* RobotMap::shooterAimingDevice = nullptr;
Relay* RobotMap::ballShooterSpinnerSpringWinder = nullptr;
Relay* RobotMap::armsUpAndOut = nullptr;
SpeedController* RobotMap::scaleTower = nullptr;

RobotDrive* RobotMap::robotDrive41 = nullptr;

DigitalOutput* RobotMap::ultrasonicPing = nullptr;
AnalogInput* RobotMap::ultrasonicEcho = nullptr;
AnalogGyro* RobotMap::gyro = nullptr;

AnalogPotentiometer* RobotMap::potentiometer = nullptr;
BuiltInAccelerometer* RobotMap::accelerometer = nullptr;

DigitalInput* RobotMap::limitSpinnerSpringWinder = nullptr;
DigitalInput* RobotMap::limitSADPosBaseline = nullptr;
DigitalInput* RobotMap::heightCounter = nullptr;

DigitalInput* RobotMap::autoLowBar = nullptr;
DigitalInput* RobotMap::autoNotLowBar = nullptr;
DigitalInput* RobotMap::autoSpyBox = nullptr;
int RobotMap::autoSelector = -1;

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION

void
RobotMap::init() {
	CameraServer *camera = CameraServer::GetInstance();
	camera->SetQuality(25);
	camera->StartAutomaticCapture("cam1"); //If using 2015 robot use "cam0"     if using 2016 robot use ""

	autoLowBar = new DigitalInput(AUTO_LOW_BAR);
	autoSpyBox = new DigitalInput(AUTO_SPY_BOX);
	autoNotLowBar = new DigitalInput(AUTO_NOT_LOW_BAR);
	gyro = new AnalogGyro(PORT_GYRO);

	if(autoLowBar->Get()) {
		autoSelector = 0;
	}
	else if(autoLowBar->Get()) {
		autoSelector = 1;
	}
	else if(autoLowBar->Get()) {
		autoSelector = 2;
	}

	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	LiveWindow* lw = LiveWindow::GetInstance();

	//NOTE: This is where you set the where the wire on RoboRIO goes

	//Sensors
	accelerometer = new BuiltInAccelerometer(BuiltInAccelerometer::Range::kRange_8G);
	potentiometer = new AnalogPotentiometer(PORT_POTENTIOMETER);
	ultrasonicPing = new DigitalOutput(PORT_ULTRASONIC_PING);
	ultrasonicEcho = new AnalogInput(PORT_ULTRASONIC_ECHO);

	//Limit
	limitSpinnerSpringWinder = new DigitalInput(L_SPINNER_SPRING_WINDER);
	limitSADPosBaseline = new DigitalInput(L_SAD_POS_BASELINE);

	//Counter
	heightCounter = new DigitalInput(HEIGHT_COUNTER);

//Drive
	robotDriveTreadRightFront = new Talon(FRONT_RIGHT);
	lw->AddActuator("Robot Drive" , "treadRightFront" , (Talon*) robotDriveTreadRightFront);

	robotDriveTreadRightBack = new Talon(BACK_RIGHT);
	lw->AddActuator("Robot Drive" , "treadRightBack" , (Talon*) robotDriveTreadRightBack);

	robotDriveTreadLeftFront = new Talon(FRONT_LEFT);
	lw->AddActuator("Robot Drive" , "treadLeftFront" , (Talon*) robotDriveTreadLeftFront);

	robotDriveTreadLeftBack = new Talon(BACK_LEFT);
	lw->AddActuator("Robot Drive" , "treadLeftBack" , (Talon*) robotDriveTreadLeftBack);

	robotDrive41 = new RobotDrive(robotDriveTreadLeftFront , robotDriveTreadLeftBack , robotDriveTreadRightFront , robotDriveTreadRightBack);

	robotDrive41->SetSafetyEnabled(true);
	robotDrive41->SetExpiration(2);
	robotDrive41->SetSensitivity(0.5);
	robotDrive41->SetMaxOutput(1.0);
	robotDrive41->SetInvertedMotor(RobotDrive::kFrontLeftMotor , true);
	robotDrive41->SetInvertedMotor(RobotDrive::kRearLeftMotor , true);
	robotDrive41->SetInvertedMotor(RobotDrive::kFrontRightMotor , true);
	robotDrive41->SetInvertedMotor(RobotDrive::kRearRightMotor , true);

	//Ball Shooter
	shooterAimingDevice = new Talon(PORT_SAD);
	lw->AddActuator("Ball Shooter" , "SAD" , (Talon*) shooterAimingDevice);

	ballShooterSpinnerClockwise = new Talon(SPINNER_CW);
	lw->AddActuator("Ball Shooter" , "clockwise spinner" , (Talon*) ballShooterSpinnerClockwise);

	ballShooterSpinnerCounterclockwise = new Talon(SPINNER_CCW);
	lw->AddActuator("Ball Shooter" , "counterclockwise spinner" , (Talon*) ballShooterSpinnerCounterclockwise);

	ballShooterSpinnerSpringWinder = new Relay(SPINNER_SPRING_WINDER);
	lw->AddActuator("Ball Shooter" , "spinner spring winder" , (Relay*) ballShooterSpinnerSpringWinder);

	scaleTower = new Talon(SCALE_TOWER);
	lw->AddActuator("Scale Tower" , "Scale Tower" , (Relay*) scaleTower);

	armsUpAndOut = new Relay(ARMS_UP_AND_OUT);
	lw->AddActuator("MCL" , "lifter" , (Relay*) armsUpAndOut);

//	position->SetInverted(true);

	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}

double
RobotMap::degreeToPotentiometer(double degree) {
	return 0.07 + 0.004 * fmod(degree , 360);
}

double
RobotMap::potentiometerToDegree(double potentiometer) {
	return (potentiometer - 0.07) / 0.004;
}

double
RobotMap::getUlrasonicFeet() {
	RobotMap::ultrasonicPing->SetUpSourceEdge(false , true);
	Wait(.02);
	double distance = (ultrasonicEcho->GetVoltage() * 5000) / 1024 / .5;
	RobotMap::ultrasonicPing->SetUpSourceEdge(true , false);
	Wait(.02);
	return distance;
}

double
RobotMap::getUlrasonicMeters() {
	return getUlrasonicFeet() * .0348;
}
