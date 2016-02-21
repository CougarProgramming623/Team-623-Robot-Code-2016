/*
 * ButtonBoard.cpp
 *
 *  Created on: Feb 20, 2016
 *      Author: CougarRobotics
 */
#include "ButtonBoard.h"
#include "Buttons/JoystickButton.h"

ButtonBoard::ButtonBoard()
		: Joystick(BUTTON_BOARD_PORT) {
	shoot = new JoystickButton(this , PORT_SHOOT);
	pickup_up = new JoystickButton(this , PORT_PICKUP_U);
	pickup_down = new JoystickButton(this , PORT_PICKUP_D);
	pos_obstacle = new JoystickButton(this , PORT_POS_OBT);
	pos_ball_pickup = new JoystickButton(this , PORT_POS_BALL_PKU);
	pos_default = new JoystickButton(this , PORT_POS_DEFAULT);
	pos_shooting = new JoystickButton(this , PORT_POS_SHT);
	pos_saftey = new JoystickButton(this , PORT_POS_SFTY);
	robot_lifter_release = new JoystickButton(this , PORT_RL_R);
	robot_lifter_up = new JoystickButton(this , PORT_RL_U);
	robot_lifter_down = new JoystickButton(this , PORT_RL_D);
}

bool ButtonBoard::getShoot() {
	return shoot->Get();
}

bool ButtonBoard::getPickupUp() {
	return pickup_up->Get();
}

bool ButtonBoard::getPickupDown() {
	return pickup_down->Get();
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

