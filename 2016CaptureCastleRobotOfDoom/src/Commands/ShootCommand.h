/*
 * ShootCommand.h
 *
 *  Created on: Feb 27, 2016
 *      Author: CougarRobotics
 */

#ifndef SRC_COMMANDS_SHOOTCOMMAND_H_
#define SRC_COMMANDS_SHOOTCOMMAND_H_

#include "Commands/Command.h"

class ShootCommand : public Command {
	private:
		int counts;
		bool isFinished , isBallShot;
	public:
		ShootCommand();
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
