/*
 * ShootCommand.h
 *
 *  Created on: Feb 27, 2016
 *      Author: CougarRobotics
 */

#ifndef SRC_COMMANDS_SHOOTRESETCOMMAND_H_
#define SRC_COMMANDS_SHOOTRESETCOMMAND_H_

#include "../Robot.h"

class ShooterResetCommand : public Command {
	private:
		int counts;bool isFinished , isBallShot , dontExecute;
	public:
		ShooterResetCommand();
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
