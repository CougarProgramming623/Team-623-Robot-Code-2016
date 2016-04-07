/*
 * ShooterResetCommand.cpp
 *
 *  Created on: Feb 27, 2016
 *      Author: CougarRobotics
 */

#include "ShooterResetCommand.h"
#include "PositionCommand.h"

ShooterResetCommand::ShooterResetCommand() {
	isFinished = false;
	isBallShot = true;
	dontExecute = false;
	counts = 0;
}

void
ShooterResetCommand::Initialize() {
	isBallShot = false;
	isFinished = false;
	dontExecute = false;
	if(RobotMap::limitSpinnerSpringWinder->Get()) {
		dontExecute = true;
		End();
	}
}

bool
ShooterResetCommand::IsFinished() {
	return isFinished;
}

void
ShooterResetCommand::End() {
	isFinished = true;
	RobotMap::ballShooterSpinnerSpringWinder->Set(Relay::Value::kOff);
	Robot::robot->stopSpinners();
	Robot::positionCommand->Initialize();
	while(!dontExecute && !Robot::positionCommand->IsFinished())
		Robot::positionCommand->Execute();
}

void
ShooterResetCommand::Interrupted() {
	End();
}

void
ShooterResetCommand::Execute() {
	if (!isFinished) {
		counts++;
		if(!isBallShot && counts * .02 < 6) {
			if(!RobotMap::limitSpinnerSpringWinder->Get()) { // Reset
				RobotMap::ballShooterSpinnerSpringWinder->Set(Relay::Value::kReverse);
				Robot::robot->stopSpinners();
				isBallShot = true;
			}
			else { // Stop!!!!!
				End();
				return;
			}
		}
		else if(RobotMap::limitSpinnerSpringWinder->Get()) { //Stop
			counts = 0;
			End();
			return;
		}
	}
}

