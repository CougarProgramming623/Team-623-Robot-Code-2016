/*
 * BallInOutCommand.cpp
 *
 *  Created on: Feb 27, 2016
 *      Author: CougarRobotics
 */

#include "BallInOutCommand.h"

BallInOutCommand::BallInOutCommand(Robot *robot , bool isIn) {
	isFinished = false;
	this->robot = robot;
	this->isIn = isIn;
}

void
BallInOutCommand::Initialize() {
}

bool
BallInOutCommand::IsFinished() {
	return isFinished;
}

void
BallInOutCommand::End() {
	isFinished = true;
	RobotMap::ballShooterSpinnerClockwise->Set(0);
	RobotMap::ballShooterSpinnerCounterclockwise->Set(0);
	if(!RobotMap::limitSpinnerSpringWinder->Get()) {
		Robot::subsystemBallShooter->spinnerSpringWinder->Set(Relay::Value::kReverse);
		while(!RobotMap::limitSpinnerSpringWinder->Get())
			;
		Wait(.5);
		Robot::subsystemBallShooter->spinnerSpringWinder->Set(Relay::Value::kOff);
	}
}

void
BallInOutCommand::Interrupted() {
	End();
}

void
BallInOutCommand::Execute() {
	if(isIn) {
		Robot::robot->shoot(.5);
	}
	else {
		Robot::robot->shoot(.25);
	}
}

