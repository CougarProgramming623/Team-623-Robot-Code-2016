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
//#include "Subsystems/ButtonBoard.h"	//Old

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
SubsystemDrive* Robot::subsystemDrive = NULL;
SubsystemInput* Robot::subsystemInput = NULL;
SubsystemBallShooter* Robot::subsystemBallShooter = NULL;
OI* Robot::oi = NULL;
Robot* Robot::robot = NULL;

double Robot::potentiometer_zero = 0;

PositionCommand *Robot::positionCommand = NULL; // Changed posCom -> positionCommand

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION

void
Robot::RobotInit() {
	oi = new OI();
	RobotMap::init();
	robot = this;
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	subsystemDrive = new SubsystemDrive();
	subsystemInput = new SubsystemInput();
	subsystemBallShooter = new SubsystemBallShooter();

	positionCommand = new PositionCommand(COMMAND_SAFETY);

	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	// This MUST be here. If the OI creates Commands (which it very likely
	// will), constructing it during the construction of CommandBase (from
	// which commands extend), subsystems are not guaranteed to be
	// yet. Thus, their requires() statements may grab null pointers. Bad
	// news. Don't move it.
	lw = LiveWindow::GetInstance();

	// instantiate the command used for the autonomous period
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
	autonomousCommand = new AutonomousCommand();

	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
}

void
Robot::AutoAim(double averageDistanceToTowerFt) {
	AimAngle(atan(8.437583333333333 * averageDistanceToTowerFt));
}

void
Robot::AimAngle(double angle) {
	double currentPotentionmeter = Robot::getPoteniometerValue();
	double finalPotentiometer = RobotMap::degreeToPotentiometer(angle); //TODO: Check during testing
	double speed = currentPotentionmeter - finalPotentiometer;

	if(RobotMap::limitSADPosBaseline->Get() && speed < 0) {
		return;
	}

	int sign;
	if(speed < 0) {
		sign = -1; // Up
		speed = sign * cos(RobotMap::potentiometerToRadian(currentPotentionmeter)) + sign;
		if(speed == 0)
			speed = sign * cos(RobotMap::potentiometerToRadian(finalPotentiometer)) + sign;
	}
	else if(speed > 0) {
		sign = 1; // Down
		speed = sign * pow(sin(RobotMap::potentiometerToRadian(currentPotentionmeter)) , 2) + sign;
		if(speed == 0) {
			speed = sign * pow(sin(RobotMap::potentiometerToRadian(finalPotentiometer)) , 2) + sign;
		}
	}

	RobotMap::shooterAimingDevice->Set(speed);
}

//Sets SAD to specified angle
void
Robot::Aim(double angle) {

	while(fabs(RobotMap::potentiometerToDegree(Robot::getPoteniometerValue()) - angle) < 2.5)
		AimAngle(angle);
	RobotMap::shooterAimingDevice->Set(-0.2);
}

double
Robot::getPoteniometerValue() {
	return RobotMap::potentiometer->Get() - potentiometer_zero;
}

//Shoots the ball
void
Robot::shoot() {
	double range;
	while(MAX_SHOOT_DISTANCE > (range = RobotMap::getUlrasonicMeters())) {
		double power = range / MAX_SHOOT_DISTANCE - 1;
		if(power > 1)
			power = 1;
		moveRobotLinear(power / 2 + .5);
	}
	shoot(.5);
}

void
Robot::startSpinners(double power) {
	subsystemBallShooter->spinnerCounterclockwise->Set(power);
	subsystemBallShooter->spinnerClockwise->Set(power);
}

void
Robot::stopSpinners() {
	subsystemBallShooter->spinnerCounterclockwise->StopMotor();
	subsystemBallShooter->spinnerClockwise->StopMotor();
}

void
Robot::shoot(double power) {
	stopDriveMotors();
	startSpinners(power);
	Wait(.5); //TODO: Get time to wait
	subsystemBallShooter->spinnerSpringWinder->Set(Relay::Value::kForward);
	while(RobotMap::limitSpinnerSpringWinder->Get())
		;
	startSpinners(0);
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
	float gyroRotation = RobotMap::gyro->GetAngle();
	while(fmod(3600 + RobotMap::gyro->GetAngle() - gyroRotation - degrees , 360) > 5)
		;
	stopDriveMotors();
}

double Robot::nominalAngle = 0;

//Moves robot forward or backward with a specified power
void
Robot::moveRobotLinear(double power) { // -1 = backward 1 = forwards
//	double currentAngle = 0;
//	int iterations = 10;
//	for(int i = 0; i < iterations; i++)
//		currentAngle += RobotMap::gyro->GetAngle() * M_PI / 180;
//	currentAngle /= iterations;
	double leftPower = power * .86 , rightPower = power;

//	DriverStation::ReportError("Nominal: " + std::to_string(nominalAngle));
//	DriverStation::ReportError("Current: " + std::to_string(currentAngle));

	//TODO: Test this!!!
//	if(nominalAngle < currentAngle)
//		rightPower = power * sin(nominalAngle - currentAngle);
//	else
//		leftPower = power * sin(currentAngle - nominalAngle);

	subsystemDrive->treadLeftFront->Set(-leftPower);
	subsystemDrive->treadLeftBack->Set(-leftPower);
	subsystemDrive->treadRightFront->Set(rightPower);
	subsystemDrive->treadRightBack->Set(rightPower);
}

//Moves robot forward or backward a specified distance
void
Robot::moveRobotLinear(double power , double distance) {
//	nominalAngle = 0;
//	int iterations = 10;
//	for(int i = 0; i < iterations; i++)
//		nominalAngle += RobotMap::gyro->GetAngle() * M_PI / 180;
//	nominalAngle /= iterations;
	static double sPower, sDistance;
	if(distance == 0){
		power = sPower;
		distance = sDistance;
	}
	else
	{
		sPower = power;
		sDistance = distance;
		RobotMap::resetRevCounter();
	}
#ifdef USE_TWO_REV_COUNTERS
								RobotMap::resetRevCounters();
								while(RobotMap::getTotalDistanceTravelled() < distance) {
									RobotMap::updateRevCounters();
#else

	if(RobotMap::getDistanceTravelled() < distance) {
		RobotMap::updateRevCounter();
//		DriverStation::ReportError(std::to_string(RobotMap::getDistanceTravelled()));
#endif
		moveRobotLinear(power);
	}
}

double
Robot::getAcceleration() {
//	subsystemInput->accelerometer->
	return sqrt(pow(subsystemInput->accelerometer->GetX() , 2) + pow(subsystemInput->accelerometer->GetY() , 2));
}
void
Robot::stopDriveMotors() {
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
	//This is where autonomous is called

	moveRobotLinear(1 , 7);	//Set aUto power to 1 from .5
	//stopDriveMotors();
	return;

	if(autonomousCommand != NULL)
		autonomousCommand->Start();

	RobotMap::shooterAimingDevice->Set(-1);

	while(!RobotMap::limitSADPosBaseline->Get()) {
	}

	potentiometer_zero = RobotMap::potentiometer->Get();
	if(RobotMap::autoSelector == -1) {
		DriverStation::ReportError("No Autonomous Selected *whisper* DON'T FAIL *whisper*\n"); //Change for debugging
	}
}

//Autonomous program: Here Autnomous is looped throughout the period of autonomous time
void
Robot::AutonomousPeriodic() { //Start in center Area when closer to low bar	//TODO: TEST autonomous code
	moveRobotLinear(0, 0);
	return; //TODO: DELETE WHEN READY TO TEST AUTONOMOUS

	switch (RobotMap::autoSelector) {
		case 0: // Start at center near low bar
			Aim(10);
			moveRobotLinear(1 , 1.85);
			turnRobot(1 , 120);
			moveRobotLinear(1 , 0000000000); //TODO: Get distance Robot Needs to move to get close enough to shoot
			//Aim(ANGLE_TO_TARGET_FROM_MSD);		//TODO: This line does not work since we dont have the MAX_SHOOT_DISTANCE
			Aim(Robot::getPoteniometerValue()); //TODO: This does not move the SAD and it needs to have a decided angle to shoot in the low/high goals
			shoot();
			break;

		case 1: //Start in Spy Box
			moveRobotLinear(1 , 1.5); //Reminder: moveRobotLinear is in meters
			turnRobot(1 , 8); //Do we really need to turn the robot?
			Aim(ANGLE_TO_TARGET_FROM_MSD);
			shoot(); //TODO: Tell drive team to put robot within 3-5 inches of corner when start in spy box
			break;

		case 2: //Start in center but not near low bar
			moveRobotLinear(1 , 1.1);
			break;
	}
}

void
Robot::TeleopInit() {
// This makes sure that the autonomous stops running when
// teleop starts running. If you want the autonomous to
// continue until interrupted by another command, remove
// these lines or comment it out.

	if(autonomousCommand != NULL)
		autonomousCommand->Cancel();
	RobotMap::ultrasonicPing->SetUpSourceEdge(true , false);
}

/*
 * I added a timer to move the SAD to safety if a red or green btn is pressed
 */

void
Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
	RobotMap::robotDrive41->TankDrive(Robot::oi->getJoystickLeft() , Robot::oi->getJoystickRight());
//	DriverStation::ReportError("Potentiometer: " + std::to_string(RobotMap::potentiometer->Get()) + "\n"); //Change for debugging
	RobotMap::updateRevCounter();
	//DriverStation::ReportError("Distance Traveled: " + std::to_string(RobotMap::getDistanceTravelled()) + "\n");

//#if 0		//TODO: Never Runs I'm keeping it because of reasons
////The Button of the All Mighty Board of Buttons
//	ButtonBoard* btnBoard = oi->getBtnBoard();
//
//	if(btnBoard->getScaleTower()) {
//		RobotMap::shooterAimingDevice->Get();
//
//		RobotMap::scaleTower->Set(1);
//
//		time_t initTime , currentTime;
//		time(&initTime);
//
//		int counter = 0;
//		double distanceTravelled = 0 , velocity = 0 , dt;
//		while(distanceTravelled < 1.75) { // 1.75 m
//			dt = difftime(time(&currentTime) , initTime);
//			time(&initTime);
//			double acceleration = getAcceleration() * GRAVITY;
//			velocity += acceleration * dt;// v = v0 + a * t
//			distanceTravelled += velocity * dt + acceleration * dt * dt;// d = d0 + v0*t + a*t^2
//			counter += RobotMap::heightCounter->GetTriggerState() ? 1 : 0;
//			if(counter >= MAX_REVOLUTIONS)
//			break;
//		}
//
//		RobotMap::scaleTower->Set(0);
//	}
//
//	//Arms Up & Out Button
//	if(btnBoard->getScaleTower()) { //If arms Up and Out is True
//		RobotMap::scaleTower->Set(1);
//	}
//	else {
//		RobotMap::scaleTower->Set(0);
//	}
//#endif

	//	DriverStation::ReportError("Ultrasonic: " + std::to_string(RobotMap::getUlrasonicFeet()) + "\n"); //Change for debugging
}

void
Robot::TestPeriodic() {
	lw->Run();
}

START_ROBOT_CLASS(Robot);

