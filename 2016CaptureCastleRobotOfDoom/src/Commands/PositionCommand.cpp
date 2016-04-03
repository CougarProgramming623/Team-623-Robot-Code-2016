/*
 * PositionCommand.cpp
 *
 *  Created on: Feb 27, 2016
 *      Author: CougarRobotics
 */

#include "PositionCommand.h"
#include "../Robot.h"

double PositionCommand::totalUltrasonicReadings = 0;
int PositionCommand::ultrasonicReadingsCount = 0;
int PositionCommand::countPressed = 0; // TODO: Part of new code to move robot SAD up to safety after buttons are released

PositionCommand::PositionCommand(int btnNumber) {
	isFinished = false;
	this->btnNumber = btnNumber;
	Requires(RobotMap::positionSubsystem);
}

void
PositionCommand::Initialize() {
	isFinished = false;
	if(btnNumber != COMMAND_AUTO_SAFETY)
		countPressed++;
}

bool
PositionCommand::IsFinished() {
	return isFinished;
}

void
PositionCommand::End() {
	if(btnNumber == COMMAND_PICK_UP)
		Robot::robot->startSpinners(-.5);
	else
		Robot::robot->stopSpinners();

	double angle = RobotMap::potentiometerToRadian(Robot::getPoteniometerValue());
	DriverStation::ReportError("Angle: " + std::to_string(angle * 180 / M_PI));

	if(btnNumber != COMMAND_SAFETY) {

		double latent_power = sin(angle);
		latent_power = -.17;
//		latent_power *= -.05;
//
//		if(Robot::getPoteniometerValue() < RobotMap::degreeToPotentiometer(30)) {
//			DriverStation::ReportError("Hit Threshold: ");
//			latent_power = -.2;
//		}
		DriverStation::ReportError("Latent Power: " + std::to_string(latent_power));

		Robot::subsystemBallShooter->shooterAimingDevice->Set(latent_power);
	}
	else
		Robot::subsystemBallShooter->shooterAimingDevice->StopMotor();
	isFinished = true;
	if(btnNumber != COMMAND_AUTO_SAFETY)
		countPressed--;
}

void
PositionCommand::Interrupted() {
	End();
}

/*
 Potentiometer measurements
 90 degrees - 0.460
 45 degrees - 0.277
 0 degrees - 0.098
 All in (Max) - 0.6 (120 deg)  //Didn't do
 All down (Min) - 0.09 (-3 deg)  //Didn't do (except for -2.5 deg)
 * */

void
PositionCommand::Execute() {
	double position = 0;

	switch (btnNumber) {
		case COMMAND_SAFETY:
			position = RobotMap::degreeToPotentiometer(95);
			break;
		case COMMAND_STORE:
			position = RobotMap::degreeToPotentiometer(45);
			break;
		case COMMAND_AUTO_AIM:
			position = RobotMap::degreeToPotentiometer(70);
			break;
		case COMMAND_PICK_UP:
			position = RobotMap::degreeToPotentiometer(8);
			break;
		case COMMAND_PORTCULIS_UP:
			position = RobotMap::degreeToPotentiometer(65);
			break;
		case COMMAND_PORTCULIS_DOWN:
			position = RobotMap::degreeToPotentiometer(8); //I set this to 0 from -0.05
			break;
		case COMMAND_SAD_UP:
			position = RobotMap::potentiometer->Get() + RobotMap::degreeToPotentiometer(5);
			break;
		case COMMAND_SAD_DOWN:
			position = RobotMap::potentiometer->Get() - RobotMap::degreeToPotentiometer(5);
			if(position < 0)
				position = 0;
			break;
		default:
			position = RobotMap::degreeToPotentiometer(95);
			break;
	} // TODO: Make sure bottom limit switch works, during last test the SAD would not move after reacing the Porticulis down position

	if(btnNumber == COMMAND_PICK_UP)
		Robot::robot->startSpinners(-.5);
	else
		Robot::robot->stopSpinners();

	double currentPosition = Robot::getPoteniometerValue();
	double speed = currentPosition - position;

	if(RobotMap::limitSADPosBaseline->Get() && speed < 0) {
		End();
		return;
	}

	int sign;
	if(speed < 0) {
		sign = -1; // Up
		speed = sign * cos(RobotMap::potentiometerToRadian(currentPosition)) + sign;
		if(speed == 0)
			speed = sign * cos(RobotMap::potentiometerToRadian(position)) + sign;
	}
	else if(speed > 0) {
		sign = 1; // Down
		speed = sign * pow(sin(RobotMap::potentiometerToRadian(currentPosition)) , 2) + sign;
		if(speed == 0) {
			speed = sign * pow(sin(RobotMap::potentiometerToRadian(position)) , 2) + sign;
		}
	}

	if(fabs(position - Robot::getPoteniometerValue()) > .01) {
		Robot::subsystemBallShooter->shooterAimingDevice->Set(.3 * speed); //Comment
	}
	else {
		End();
	}
}

