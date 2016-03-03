/*
 * ShootCommand.h
 *
 *  Created on: Feb 27, 2016
 *      Author: CougarRobotics
 */

#ifndef SRC_COMMANDS_POSITIONCOMMAND_H_
#define SRC_COMMANDS_POSITIONCOMMAND_H_

#include "../Robot.h"

#define COMMAND_SAFETY 0
#define COMMAND_STORE 1
#define COMMAND_AUTO_AIM 2
#define COMMAND_PICK_UP 3
#define COMMAND_PORTCULIS_UP 4
#define COMMAND_PORTCULIS_DOWN 5
#define COMMAND_SAD_UP 6
#define COMMAND_SAD_DOWN 7

#define MIN_THRESHOLD .5

class PositionCommand : public Command {
	private:
		bool isFinished;
		int btnNumber;
		Robot *robot;
	public:
		static double totalUltrasonicReadings;
		static int ultrasonicReadingsCount;
		PositionCommand(Robot*, int);
		virtual void
		Initialize();
		virtual void
		Execute();
		virtual bool
		IsFinished();
		virtual void
		End();
		virtual void
		Interrupted();
};

#endif /* SRC_COMMANDS_SHOOTCOMMAND_H_ */
