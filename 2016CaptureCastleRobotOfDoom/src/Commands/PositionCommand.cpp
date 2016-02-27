/*
 * PositionCommand.cpp
 *
 *  Created on: Feb 27, 2016
 *      Author: CougarRobotics
 */

#include "PositionCommand.h"

PositionCommand::PositionCommand(Robot *robot, int btnNumber) {
	isFinished = false;
	this->robot = robot;
	this->btnNumber = btnNumber;
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

void
PositionCommand::Execute() {
	double position = 0; //TODO: Do position stuff
	switch(btnNumber){
	case COMMAND_SAFETY:
		break;
	case COMMAND_STORE:
		break;
	case COMMAND_AUTO_AIM:
		break;
	case COMMAND_PICK_UP:
		break;
	case COMMAND_PORTCULIS_UP:
		break;
	case COMMAND_PORTCULIS_DOWN:
		break;
	}
	double currentPosition =  RobotMap::potentiometer->Get();
	double speed = position - currentPosition;
	if(speed > 1)
		speed = 1;
	else if(speed > 0 && speed < MIN_THRESHOLD)
		speed = MIN_THRESHOLD;
	if(speed < 1)
		speed = -1;
	else if(speed < 0 && speed > -MIN_THRESHOLD)
			speed = -MIN_THRESHOLD;
	Robot::subsystemBallShooter->shooterAimingDevice->Set(speed); //Comment
	while(fabs(position - RobotMap::potentiometer->Get() > .05))
		;
	Robot::subsystemBallShooter->shooterAimingDevice->Set(0);
}

