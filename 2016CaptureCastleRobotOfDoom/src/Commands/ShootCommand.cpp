/*
 * ShootCommand.cpp
 *
 *  Created on: Feb 27, 2016
 *      Author: CougarRobotics
 */

#include "ShootCommand.h"
#include "PositionCommand.h"

ShootCommand::ShootCommand(Robot *robot) {
	isFinished = false;
	isBallShot = true;
	this->robot = robot;
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
//	DriverStation::ReportError("SHOOT BALL SHOT=" + std::to_string(isBallShot));
//	DriverStation::ReportError("SHOOT LSSW=" + std::to_string(RobotMap::limitSpinnerSpringWinder->Get()) + "\n");
	if(!isBallShot) {
		if(!RobotMap::limitSpinnerSpringWinder->Get()) {
			RobotMap::ballShooterSpinnerSpringWinder->Set(Relay::Value::kReverse);
			Robot::robot->stopSpinners();
			isBallShot = true;
		}
		else {
			RobotMap::ballShooterSpinnerSpringWinder->Set(Relay::Value::kForward);
			RobotMap::ballShooterSpinnerClockwise->Set(.5);
			RobotMap::ballShooterSpinnerCounterclockwise->Set(.5);
		}
	}
	else if(RobotMap::limitSpinnerSpringWinder->Get()) {
		RobotMap::ballShooterSpinnerSpringWinder->Set(Relay::Value::kOff);
	}
//	else {
//		RobotMap::ballShooterSpinnerSpringWinder->Set(Relay::Value::kForward);
//	}
}

