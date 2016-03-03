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
	isFinished = false;
}

bool
BallInOutCommand::IsFinished() {
	return isFinished;
}

void
BallInOutCommand::End() {
	isFinished = true;
	Robot::robot->stopSpinners();
}

void
BallInOutCommand::Interrupted() {
	End();
}

void
BallInOutCommand::Execute() {
	if(isIn) {
		Robot::robot->startSpinners(.5);
	}
	else {
		Robot::robot->startSpinners(-.25);
	}
}

