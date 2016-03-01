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
	isBallShot = false;
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
	if(!isBallShot && !RobotMap::ballShooterSpinnerSpringWinder->Get()) {
		//Stop Spinners and Kicker
		RobotMap::ballShooterSpinnerClockwise->Set(0);
		RobotMap::ballShooterSpinnerCounterclockwise->Set(0);
		RobotMap::ballShooterSpinnerSpringWinder->Set(Relay::Value::kOff);
	}
	else if(isBallShot) {
		RobotMap::ballShooterSpinnerSpringWinder->Set(Relay::Value::kReverse);
	}
	else {
		//Aim
		if(ultrasonicReadingsCount < 5) {
			totalUltrasonicReadings += RobotMap::getUlrasonicFeet();
			ultrasonicReadingsCount++;
		}
		else {
			Robot::AutoAim(totalUltrasonicReadings / ultrasonicReadingsCount);
			RobotMap::ballShooterSpinnerSpringWinder->Set(Relay::Value::kForward);
			RobotMap::ballShooterSpinnerClockwise->Set(.5);
			RobotMap::ballShooterSpinnerCounterclockwise->Set(.5);
			totalUltrasonicReadings = 0;
			ultrasonicReadingsCount = 0;
		}
	}
}
