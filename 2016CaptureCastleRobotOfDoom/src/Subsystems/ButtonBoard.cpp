/*
 * ButtonBoard.cpp
 *
 *  Created on: Feb 20, 2016
 *      Author: CougarRobotics
 */
#include "Joystick.h"
#include "Buttons/JoystickButton.h"
#include "ButtonBoard.h"
#include "../Commands/ShootCommand.h"
#include "../Commands/PositionCommand.h"
#include "../Commands/BallInOutCommand.h"

ButtonBoard::ButtonBoard() :
	Joystick(BUTTON_BOARD_PORT) {
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

	shoot->WhileHeld(new ShootCommand(Robot::robot));

	pos_saftey->WhileHeld(new PositionCommand(Robot::robot , COMMAND_SAFETY));
	pos_auto_aim->WhileHeld(new PositionCommand(Robot::robot , COMMAND_AUTO_AIM));
	pos_pickup->WhileHeld(new PositionCommand(Robot::robot , COMMAND_PICK_UP));
	port_down->WhileHeld(new PositionCommand(Robot::robot , COMMAND_PORTCULIS_DOWN));
	port_up->WhileHeld(new PositionCommand(Robot::robot , COMMAND_PORTCULIS_UP));
	pos_store->WhileHeld(new PositionCommand(Robot::robot , COMMAND_STORE));

	ball_in->WhileHeld(new BallInOutCommand(Robot::robot , true));
	ball_out->WhileHeld(new BallInOutCommand(Robot::robot , false));
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

int
ButtonBoard::getSADPos() {
	if(SAD_up->Get())
		return SAD_UP; // 1
	else if(SAD_down->Get())
		return SAD_DOWN; // -1
	else
		return SAD_NONE; // 0
}

int
ButtonBoard::getPresetPos() {
	if(pos_saftey->Get())
		return POS_SAFTEY;
	else if(pos_store->Get())
		return POS_STORE;
	else if(pos_auto_aim->Get())
		return POS_AUTO_AIM;
	else if(pos_pickup->Get())
		return POS_PICK_UP;
	else
		return POS_NONE;
}

int
ButtonBoard::getPortPos() {
	if(port_up->Get())
		return PORTCULIS_UP; // 1
	else if(port_down->Get())
		return PORTCULIS_DOWN; // -1
	else
		return PORTCULIS_NONE; // 0
}

int
ButtonBoard::getBallSpinner() {
	if(ball_in->Get())
		return BALL_IN; // 1
	else if(ball_out->Get())
		return BALL_OUT; // -1
	else
		return BALL_NONE; // 0
}

bool
ButtonBoard::getScaleTower() {
	return scale_tower->Get();
}

bool
ButtonBoard::getShoot() {
	return shoot->Get();
}

bool
ButtonBoard::getArmsUpAndOut() {
	return arms_up_and_out->Get();
}
