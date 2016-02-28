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
#include <math.h>
#include "Subsystems/ButtonBoard.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
SubsystemDrive* Robot::subsystemDrive = NULL;
SubsystemInput* Robot::subsystemInput = NULL;
SubsystemBallShooter* Robot::subsystemBallShooter = NULL;
OI* Robot::oi = NULL;
Robot* Robot::robot = NULL;

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION

void
Robot::RobotInit() {
	RobotMap::init();
	robot = this;
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

double
Robot::getPoteniometerValue() {
	return RobotMap::potentiometer->Get() - potentiometer_zero;
}

//Shoots a ball
void
Robot::shoot() {
	double range;
	while(MAX_SHOOT_DISTANCE > (range = RobotMap::ultrasonic->GetRangeMM() / 1000)) {
		double power = range / MAX_SHOOT_DISTANCE - 1;
		if(power > 1)
			power = 1;
		moveRobotLinear(power / 2 + .5);
	}
	shoot(.5);
}

void
Robot::shoot(double power) {
	stopRobot();
	subsystemBallShooter->spinnerCounterclockwise->Set(power);
	subsystemBallShooter->spinnerClockwise->Set(power);
	Wait(.5); //TODO: Get time to wait
	subsystemBallShooter->spinnerSpringWinder->Set(Relay::Value::kForward);
	while(RobotMap::limitSpinnerSpringWinder->Get())
		;
	subsystemBallShooter->spinnerCounterclockwise->Set(0);
	subsystemBallShooter->spinnerClockwise->Set(0);
	subsystemBallShooter->spinnerSpringWinder->Set(Relay::Value::kReverse);
	while(!RobotMap::limitSpinnerSpringWinder->Get())
		;
	Wait(.5);
	subsystemBallShooter->spinnerSpringWinder->Set(Relay::Value::kOff);
}

//This turns the robot left or right with a specified power
void
Robot::turnRobot(double power) { //-1 = Left 1 = Right
	subsystemDrive->treadLeftFront->Set(power);
	subsystemDrive->treadLeftBack->Set(power);
	subsystemDrive->treadRightFront->Set(power);
	subsystemDrive->treadRightBack->Set(power);
}

//This turns the robot left or right with a specified power and and a specified degrees
void
Robot::turnRobot(double power , double degrees) {
	turnRobot(power);
	float gyroRotation = RobotMap::robotMap->gyro->GetAngle();
	while(fmod(3600 + RobotMap::robotMap->gyro->GetAngle() - gyroRotation - degrees , 360) > 5)
		;
	stopRobot();
}

//Moves robot forward or backward with a specified power
void
Robot::moveRobotLinear(double power) { // -1 = backward 1 = forwards
	subsystemDrive->treadLeftFront->Set(power);
	subsystemDrive->treadLeftBack->Set(power);
	subsystemDrive->treadRightFront->Set(power);
	subsystemDrive->treadRightBack->Set(power);
}

//Moves robot forward or backward a specified distance
void
Robot::moveRobotLinear(double power , double distance) { // in meters
	moveRobotLinear(power);
	time_t initTime , currentTime;
	time(&initTime);
	double distanceTravelled = 0 , velocity = 0 , seconds;
	while(distanceTravelled < distance) {
		seconds = difftime(time(&currentTime) , initTime);
		time(&initTime);
		double acceleration = getAcceleration() * GRAVITY;
		velocity += acceleration * seconds; // v = v0 + a * t
		distanceTravelled += velocity * seconds + acceleration * seconds * seconds; // d = d0 + v0*t + a*t^2
	}
	stopRobot();
}

double
Robot::getAcceleration() {
//	subsystemInput->accelerometer->
	return sqrt(pow(subsystemInput->accelerometer->GetX() , 2) + pow(subsystemInput->accelerometer->GetY() , 2));
}
void
Robot::stopRobot() {
	moveRobotLinear(0); //This makes the robot to STOP
}

/**
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */
void
Robot::DisabledInit() {

}

void
Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
}

void
Robot::AutonomousInit() {
	if(autonomousCommand != NULL)
		autonomousCommand->Start();

	RobotMap::shooterAimingDevice->Set(-1); // TODO: check direction

	while(!RobotMap::limitSADPosBaseline->Get()) {
	}

	potentiometer_zero = RobotMap::potentiometer->Get();
}

//Autonomous program (Look at notes for autonomous instructions)
void
Robot::AutonomousPeriodic() { //Start in center Area	//TODO: Write autonomous code
#if ROBOT_AUTO == 1
	turnRobot(-1 , 180);
	moveRobotLinear(1 , 1.85);
	turnRobot(1 , 90);
	moveRobotLinear(1 , 7.3);
	turnRobot(1 , 120);
	shoot();
#elif ROBOT_AUTO == 2	//Start in Spy Box
	shoot();
#endif
}

void
Robot::TeleopInit() {
// This makes sure that the autonomous stops running when
// teleop starts running. If you want the autonomous to
// continue until interrupted by another command, remove
// these lines or comment it out.
	if(autonomousCommand != NULL)
		autonomousCommand->Cancel();
}

void
Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();

//The Button of the All Mighty Board of Buttons
	ButtonBoard* btnBoard = oi->getBtnBoard();

	if(btnBoard->getScaleTower()) {
		RobotMap::shooterAimingDevice->Get(); // TODO: MOVE till in saftey

		RobotMap::scaleTower->Set(1);

		time_t initTime , currentTime;
		time(&initTime);

		int counter = 0;
		double distanceTravelled = 0 , velocity = 0 , dt;
		while(distanceTravelled < 1.75) { // 1.75 m
			dt = difftime(time(&currentTime) , initTime);
			time(&initTime);
			double acceleration = getAcceleration() * GRAVITY;
			velocity += acceleration * dt; // v = v0 + a * t
			distanceTravelled += velocity * dt + acceleration * dt * dt; // d = d0 + v0*t + a*t^2
			counter += RobotMap::heightCounter->GetTriggerState() ? 1 : 0;
			if(counter >= MAX_REVOLUTIONS)
				break;
		}

		RobotMap::scaleTower->Set(0);
	}

	//Arms Up & Out Button
	if(btnBoard->getScaleTower()) { //If arms Up and Out is True
		RobotMap::scaleTower->Set(1);
	}
	else {
		RobotMap::scaleTower->Set(0);
	}
	DriverStation::ReportError("UltraSonic: " + std::to_string(RobotMap::ultrasonic->GetRangeMM()) + "\n"); //Change for debugging
	DriverStation::ReportError("Potentiometer: " + std::to_string(RobotMap::potentiometer->Get()) + "\n"); //Change for debugging
}

void
Robot::TestPeriodic() {
	lw->Run();
}

START_ROBOT_CLASS(Robot);

