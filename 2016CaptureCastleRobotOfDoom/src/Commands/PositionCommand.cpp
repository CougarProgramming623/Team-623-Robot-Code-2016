/*
 * PositionCommand.cpp
 *
 *  Created on: Feb 27, 2016
 *      Author: CougarRobotics
 */

#include "PositionCommand.h"

double PositionCommand::totalUltrasonicReadings = 0;
int PositionCommand::ultrasonicReadingsCount = 0;

PositionCommand::PositionCommand(Robot *robot , int btnNumber) {
	isFinished = false;
	this->robot = robot;
	this->btnNumber = btnNumber;
}

void
PositionCommand::Initialize() {
	isFinished = false;
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
	double position = 0;
	switch (btnNumber) {
		case COMMAND_SAFETY:
			position = RobotMap::degreeToPotentiometer(112.5);
			break;
		case COMMAND_STORE:
			position = RobotMap::degreeToPotentiometer(45);
			break;
		case COMMAND_AUTO_AIM:
			if(ultrasonicReadingsCount < 5) {
				totalUltrasonicReadings += RobotMap::getUlrasonicFeet();
				ultrasonicReadingsCount++;
			}
			else {
				Robot::AutoAim(totalUltrasonicReadings / ultrasonicReadingsCount);
				totalUltrasonicReadings = 0;
				ultrasonicReadingsCount = 0;
			}
			return;
		case COMMAND_PICK_UP:
			position = RobotMap::degreeToPotentiometer(0);
			break;
		case COMMAND_PORTCULIS_UP:
			position = RobotMap::degreeToPotentiometer(70);
			break;
		case COMMAND_PORTCULIS_DOWN:
			position = RobotMap::degreeToPotentiometer(-.05);
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
	} // TODO: Scale the speed based on position up is faster and down is slower. The Check for limit switch
	double currentPosition = Robot::getPoteniometerValue();
	double speed = currentPosition - position;

	int sign;
	if(speed < 0) {
		sign = -1; // Up
		speed = sign * cos(RobotMap::potentiometerToDegree(currentPosition) * M_PI / 180) + sign;
		if(speed == 0)
			speed = sign * cos(RobotMap::potentiometerToDegree(position) * M_PI / 180) + sign;
	}
	else if(speed > 0) {
		sign = 1; // Down
		speed = sign * sin(RobotMap::potentiometerToDegree(currentPosition) * M_PI / 180) + sign;
		if(speed == 0)
			speed = sign * sin(RobotMap::potentiometerToDegree(position) * M_PI / 180) + sign;
	}

	DriverStation::ReportError("POSITION CURRENT=" + std::to_string(currentPosition));
	DriverStation::ReportError("POSITION END=" + std::to_string(position));
	DriverStation::ReportError("POSITION SPEED=" + std::to_string(speed) + "\n");
	DriverStation::ReportError("FABS=" + std::to_string(fabs(position - Robot::getPoteniometerValue())) + "\n");

	if(fabs(position - Robot::getPoteniometerValue()) > .005)
		Robot::subsystemBallShooter->shooterAimingDevice->Set(.3 * speed); //Comment
	else
		Robot::subsystemBallShooter->shooterAimingDevice->Set(0);
}

