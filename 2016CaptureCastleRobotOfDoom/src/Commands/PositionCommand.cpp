/*
 * PositionCommand.cpp
 *
 *  Created on: Feb 27, 2016
 *      Author: CougarRobotics
 */

#include "PositionCommand.h"

PositionCommand::PositionCommand(Robot *robot , int btnNumber) {
	isFinished = false;
	this->robot = robot;
	this->btnNumber = btnNumber;
	time(&lastTime);
	time(&currentTime);
	secondsSinceLastPressed = 0;
}

void
PositionCommand::Initialize() {
}

bool
PositionCommand::IsFinished() {
	return isFinished;
}

void
PositionCommand::End() {
	isFinished = true;
	Robot::subsystemBallShooter->shooterAimingDevice->Set(0);
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
	/*if(btnNumber != COMMAND_SAFETY) {
	 time(&currentTime);
	 double dt = difftime(currentTime , lastTime);
	 time(&lastTime);
	 if(dt < .1) {
	 secondsSinceLastPressed += dt;
	 }
	 else {
	 secondsSinceLastPressed = 0;
	 }
	 if(secondsSinceLastPressed < .25) {
	 return;
	 }
	 }*/
	double position = 0;
	switch (btnNumber) {
		case COMMAND_SAFETY:
			position = RobotMap::degreeToPotentiometer(112.5);
			break;
		case COMMAND_STORE:
			position = RobotMap::degreeToPotentiometer(45);
			break;
		case COMMAND_AUTO_AIM:
			Robot::AutoAim(RobotMap::getUlrasonicFeet());
			break;
		case COMMAND_PICK_UP:
			position = RobotMap::degreeToPotentiometer(0);
			break;
		case COMMAND_PORTCULIS_UP:
			position = RobotMap::degreeToPotentiometer(70);
			break;
		case COMMAND_PORTCULIS_DOWN:
			position = RobotMap::degreeToPotentiometer(-.05);
			break;
		default:
			position = RobotMap::degreeToPotentiometer(90);
			break;
	}
	double currentPosition = RobotMap::potentiometer->Get();
	double speed = position - currentPosition;
	if(speed > 1)
		speed = 1;
	else if(speed > 0 && speed < MIN_THRESHOLD)
		speed = MIN_THRESHOLD;
	if(speed < 1)
		speed = -1;
	else if(speed < 0 && speed > -MIN_THRESHOLD)
		speed = -MIN_THRESHOLD;
	if(fabs(position - RobotMap::potentiometer->Get() > .005))
		Robot::subsystemBallShooter->shooterAimingDevice->Set(.3 * speed); //Comment
	else
		Robot::subsystemBallShooter->shooterAimingDevice->Set(0);
}

