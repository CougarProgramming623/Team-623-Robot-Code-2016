/*
 * ShootCommand.cpp
 *
 *  Created on: Feb 27, 2016
 *      Author: CougarRobotics
 */

#include "ShootCommand.h"
#include "../Robot.h"

ShootCommand::ShootCommand() {
	isFinished = false;
	isBallShot = true;
	counts = 0;
}

void
ShootCommand::Initialize() {
	isBallShot = false;
	isFinished = false;
}

bool
ShootCommand::IsFinished() {
	return isFinished;
}

void
ShootCommand::End() {
	isFinished = true;
	RobotMap::ballShooterSpinnerSpringWinder->Set(Relay::Value::kOff);
	Robot::robot->stopSpinners();
}

void
ShootCommand::Interrupted() {
	End();
}

void
ShootCommand::Execute() {
//	if(!isBallShot) {
//		if(!RobotMap::limitSpinnerSpringWinder->Get()) {		//OLD
	counts++;
		if(!isBallShot && counts * .02 < 6) {
			if(!RobotMap::limitSpinnerSpringWinder->Get()) { // Reset
			RobotMap::ballShooterSpinnerSpringWinder->Set(Relay::Value::kReverse);
			Robot::robot->stopSpinners();
			isBallShot = true;
		}
		else {	//Shoot
			RobotMap::ballShooterSpinnerSpringWinder->Set(Relay::Value::kForward);
			RobotMap::ballShooterSpinnerClockwise->Set(.5);
			RobotMap::ballShooterSpinnerCounterclockwise->Set(.5);
		}
	}
	else if(RobotMap::limitSpinnerSpringWinder->Get()) {		//Stop
		counts = 0;
		RobotMap::ballShooterSpinnerSpringWinder->Set(Relay::Value::kOff);
	}
}

