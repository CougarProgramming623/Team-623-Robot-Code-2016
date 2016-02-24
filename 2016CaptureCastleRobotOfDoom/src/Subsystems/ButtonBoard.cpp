/*
 * ButtonBoard.cpp
 *
 *  Created on: Feb 20, 2016
 *      Author: CougarRobotics
 */
#include "Joystick.h"
#include "Buttons/JoystickButton.h"
#include "ButtonBoard.h"

ButtonBoard::ButtonBoard()
		: Joystick(BUTTON_BOARD_PORT) {
	shoot = new JoystickButton(this , PORT_SHOOT);
	SAD_up = new JoystickButton(this , PORT_SAD_U);
	SAD_down = new JoystickButton(this , PORT_SAD_D);
	pos_obstacle = new JoystickButton(this , PORT_POS_OBT);
	pos_ball_pickup = new JoystickButton(this , PORT_POS_BALL_PKU);
	pos_default = new JoystickButton(this , PORT_POS_DEFAULT);
	pos_shooting = new JoystickButton(this , PORT_POS_SHOOT);
	pos_saftey = new JoystickButton(this , PORT_POS_SFTY);
	robot_lifter_release = new JoystickButton(this , PORT_ROBOT_LIFTER_RELEASE);
	robot_lifter_up = new JoystickButton(this , PORT_ROBOT_LIFTER_U);
	robot_lifter_down = new JoystickButton(this , PORT_ROBOT_LIFTER_D);
}

ButtonBoard::~ButtonBoard() {
	delete shoot;
	delete SAD_up;
	delete SAD_down;
	delete pos_obstacle;
	delete pos_ball_pickup;
	delete pos_default;
	delete pos_shooting;
	delete pos_saftey;
	delete robot_lifter_release;
	delete robot_lifter_up;
	delete robot_lifter_down;
}

bool ButtonBoard::getShoot() {
	return shoot->Get();
}

bool ButtonBoard::getSADUp() {
	return SAD_up->Get();
}

bool ButtonBoard::getSADDown() {
	return SAD_down->Get();
}

int ButtonBoard::getPos() {
	if(pos_saftey->Get()) {
		return POS_NONE;
	}
	else if(pos_default->Get()) {
		return POS_DEFAULT;
	}
	else if(pos_obstacle->Get()) {
		return POS_OBSTACLE;
	}
	else if(pos_ball_pickup->Get()) {
		return POS_BALL_PICKUP;
	}
	else if(pos_shooting->Get()) {
		return POS_SHOOTING;
	}
	else {
		return POS_NONE;
	}

}

int ButtonBoard::getLifterPos() {
	if(robot_lifter_release->Get()) {
		return LIFTER_POS_RELEASE;
	}
	else if(robot_lifter_up->Get()) {
		return LIFTER_POS_UP;
	}
	else if(robot_lifter_down->Get()) {
		return LIFTER_POS_DOWN;
	}
	else {
		return POS_NONE;
	}
}

