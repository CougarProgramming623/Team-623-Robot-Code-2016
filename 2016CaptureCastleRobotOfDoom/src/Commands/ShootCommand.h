/*
 * ShootCommand.h
 *
 *  Created on: Feb 27, 2016
 *      Author: CougarRobotics
 */

#ifndef SRC_COMMANDS_SHOOTCOMMAND_H_
#define SRC_COMMANDS_SHOOTCOMMAND_H_

#include "../Robot.h"

class ShootCommand : public Command {
	private:
		bool isFinished , isBallShot;
		Robot *robot;
	public:
		ShootCommand(Robot*);
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
