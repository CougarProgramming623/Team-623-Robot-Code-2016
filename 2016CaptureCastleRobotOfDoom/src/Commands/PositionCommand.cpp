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
	isFinished = true;
	Robot::subsystemBallShooter->shooterAimingDevice->Set(0);
	if(btnNumber != COMMAND_AUTO_SAFETY)
		countPressed--;
}

void
PositionCommand::Interrupted() {
	End();
}

/*
 Potentiometer measurements
 90 degrees - 0.43
 45 degrees - 0.25
 0 degrees - 0.07
 All in (Max) - 0.52 (112.5 deg)
 All down (Min) - 0.05 (-.05 deg)
 * */

void
PositionCommand::Execute() {
	DriverStation::ReportError("Reporting Limit Switch: " + std::to_string(RobotMap::limitSADPosBaseline->Get())); //TODO: FROM UNTESTED PATCH (line 52 - line 57)
	//time(&lastPositionClickTime);	//TODO: Do we Still Need this?????????????

	double position = 0;

	switch (btnNumber) {
		case COMMAND_SAFETY:
			position = RobotMap::degreeToPotentiometer(90);
			break;
		case COMMAND_STORE:
			position = RobotMap::degreeToPotentiometer(45);
			break;
		case COMMAND_AUTO_AIM:
			position = .298;
			break;
		case COMMAND_PICK_UP:
			position = RobotMap::degreeToPotentiometer(0);
			break;
		case COMMAND_PORTCULIS_UP:
			position = RobotMap::degreeToPotentiometer(70);
			break;
		case COMMAND_PORTCULIS_DOWN:
			position = RobotMap::degreeToPotentiometer(0); //I set this to 0 from -0.05
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
			position = RobotMap::degreeToPotentiometer(90);
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
//			speed = sign * cos(RobotMap::potentiometerToDegree(currentPosition) * M_PI / 180) + sign; //Old
		speed = sign * cos(RobotMap::potentiometerToRadian(currentPosition)) + sign;
		if(speed == 0)
			speed = sign * cos(RobotMap::potentiometerToRadian(position)) + sign;
	}
	else if(speed > 0) { // TODO: Change to sin^2 and cos^2 and check code 				(Not sture if his todo still applies) we need to test the code
		sign = 1; // Down
//			speed = sign * sin(RobotMap::potentiometerToDegree(currentPosition) * M_PI / 180) + sign; //Old
		speed = sign * pow(sin(RobotMap::potentiometerToRadian(currentPosition)) , 2) + sign;
		if(speed == 0) {
//				speed = sign * sin(RobotMap::potentiometerToDegree(position) * M_PI / 180) + sign; //Old
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

