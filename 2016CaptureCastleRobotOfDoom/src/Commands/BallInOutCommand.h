/*
 * BallInOut.h
 *
 *  Created on: Feb 27, 2016
 *      Author: CougarRobotics
 */

#ifndef SRC_COMMANDS_BALLINOUTCOMMAND_H_
#define SRC_COMMANDS_BALLINOUTCOMMAND_H_

#include "../Robot.h"

class BallInOutCommand : public Command {
	private:
		bool isFinished , isIn;
		Robot *robot;
	public:
		BallInOutCommand(Robot* , bool);
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

#endif /* SRC_COMMANDS_BALLINOUTCOMMAND_H_ */
