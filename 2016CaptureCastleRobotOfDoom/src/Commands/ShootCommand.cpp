/*
 * ShootCommand.cpp
 *
 *  Created on: Feb 27, 2016
 *      Author: CougarRobotics
 */

#include "ShootCommand.h"

ShootCommand::ShootCommand(Robot *robot) {
	isFinished = false;
	this->robot = robot;
}

void
ShootCommand::Initialize() {
}

bool
ShootCommand::IsFinished() {
	return isFinished;
}

void
ShootCommand::End() {
	isFinished = true;
}

void
ShootCommand::Interrupted() {
}

void
ShootCommand::Execute() {
	robot->shoot();
}

