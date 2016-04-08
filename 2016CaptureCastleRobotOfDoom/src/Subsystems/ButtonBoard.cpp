/*
 * ButtonBoard.cpp
 *
 *  Created on: Feb 20, 2016
 *      Author: CougarRobotics
 */

#include "../RobotMap.h"
#include "ButtonBoard.h"

#include "../Commands/ShootCommand.h"
#include "../Commands/PositionCommand.h"
#include "../Commands/BallInOutCommand.h"
#include "../Commands/ArmsUpAndOutCommand.h"
#include "../Commands/ScaleTowerCommand.h"
#include "../Commands/ShooterResetCommand.h"

ButtonBoard::ButtonBoard(int port) :
	Joystick(port) {
	//Initialization
	arms_up_and_out = new JoystickButton(this , PORT_ARMS_UP_AND_OUT);
	shoot = new JoystickButton(this , PORT_SHOOT);
	SAD_up = new JoystickButton(this , PORT_SAD_UP);
	SAD_down = new JoystickButton(this , PORT_SAD_DOWN);
	ball_in = new JoystickButton(this , PORT_BALL_IN);
	ball_out = new JoystickButton(this , PORT_BALL_OUT);
	scale_tower = new JoystickButton(this , PORT_SCALE_TOWER);
	pos_saftey = new JoystickButton(this , PORT_POS_SAFTEY);
	pos_auto_aim = new JoystickButton(this , PORT_POS_AUTO_AIM);
	pos_store = new JoystickButton(this , PORT_POS_STORE);
	pos_pickup = new JoystickButton(this , PORT_POS_PICK_UP);
	port_up = new JoystickButton(this , PORT_PORTCULIS_UP);
	port_down = new JoystickButton(this , PORT_PORTCULIS_DOWN);

	outputs = 0;
	this->SetOutputs(0);

	//Commands

	shoot->WhileHeld(new ShootCommand());

	pos_auto_aim->WhileHeld(new PositionCommand(COMMAND_AUTO_AIM));

	pos_saftey->WhenPressed(new PositionCommand(COMMAND_SAFETY));
	pos_pickup->WhileHeld(new PositionCommand(COMMAND_PICK_UP));
	port_down->WhileHeld(new PositionCommand(COMMAND_PORTCULIS_DOWN));
	port_up->WhenPressed(new PositionCommand(COMMAND_PORTCULIS_UP));
	pos_store->WhileHeld(new PositionCommand(COMMAND_STORE));

	SAD_up->WhileHeld(new PositionCommand(COMMAND_SAD_UP));
	SAD_down->WhileHeld(new PositionCommand(COMMAND_SAD_DOWN));

	ball_in->WhileHeld(new BallInOutCommand(true));
	ball_out->WhileHeld(new BallInOutCommand(false));
	scale_tower->WhileHeld(new ScaleTowerCommand());
	arms_up_and_out->WhileHeld(new ArmsUpAndOutCommand());

	shoot->WhenReleased(new ShooterResetCommand());

	//Set to safety after released
	PositionCommand *commmandSafety = new PositionCommand(COMMAND_SAFETY);
	pos_pickup->WhenReleased(commmandSafety);
	port_down->WhenReleased(commmandSafety);
	//port_up->WhenReleased(commmandSafety);
	pos_store->WhenReleased(commmandSafety);
}

ButtonBoard::~ButtonBoard() {
	delete shoot;
	delete arms_up_and_out;
	delete SAD_up;
	delete SAD_down;
	delete ball_in;
	delete ball_out;
	delete scale_tower;
	delete pos_saftey;
	delete pos_auto_aim;
	delete pos_store;
	delete pos_pickup;
	delete port_up;
	delete port_down;
}

void
ButtonBoard::ResetScoopLEDs(void)
{
	outputs &= ~LEDS_SCOOP;
	this->SetOutputs(outputs);
}

void
ButtonBoard::EnableLEDs(uint32_t mask)
{
	outputs |= mask;
	this->SetOutputs(outputs);
}

void
ButtonBoard::DisableLEDs(uint32_t mask)
{
	outputs &= ~mask;
	this->SetOutputs(outputs);
}
