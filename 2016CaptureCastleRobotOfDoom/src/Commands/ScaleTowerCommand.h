/*
 * ScaleTower.h
 *
 *  Created on: Feb 28, 2016
 *      Author: CougarRobotics
 */

#ifndef SRC_COMMANDS_SCALETOWERCOMMAND_H_
#define SRC_COMMANDS_SCALETOWERCOMMAND_H_

#include "Commands/Subsystem.h"
#include "../Robot.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class ScaleTowerCommand : public Command {
	private:
		time_t lastTime = 0 , currentTime = 0;
		int halfrevs = 0, iterations = 0;
		bool lastRevState = false;
		double distanceTravelled = 0 , velocity = 0 , dt = 0;
	public:
		ScaleTowerCommand();
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

#endif /* SRC_COMMANDS_SCALETOWERCOMMAND_H_ */
