/*
 * ButtonBoard.h
 *
 *  Created on: Feb 20, 2016
 *      Author: CougarRobotics
 */

#ifndef SRC_SUBSYSTEMS_BUTTONBOARD_H_
#define SRC_SUBSYSTEMS_BUTTONBOARD_H_

#include "Buttons/JoystickButton.h"
#include <Joystick.h>

#define BUTTON_BOARD_PORT 1

#define PORT_SHOOT 0
#define PORT_PICKUP_U 0
#define PORT_PICKUP_D 0
#define PORT_POS_OBT 0
#define PORT_POS_BALL_PKU 0
#define PORT_POS_DEFAULT 0
#define PORT_POS_SHT 0
#define PORT_POS_SFTY 0
#define PORT_RL_R 0
#define PORT_RL_U 0
#define PORT_RL_D 0

#define POS_NONE 0
#define POS_OBSTACLE 1
#define POS_BALL_PICKUP 2
#define POS_DEFAULT 3
#define POS_SHOOTING 4
#define POS_SAFTEY 5

#define LIFTER_POS_NONE 0
#define LIFTER_POS_RELEASE 1
#define LIFTER_POS_UP 2
#define LIFTER_POS_DOWN 3

class ButtonBoard : Joystick {
	private:
		JoystickButton *shoot;
		JoystickButton *pickup_up;
		JoystickButton *pickup_down;
		JoystickButton *pos_obstacle;
		JoystickButton *pos_ball_pickup;
		JoystickButton *pos_default;
		JoystickButton *pos_shooting;
		JoystickButton *pos_saftey;
		JoystickButton *robot_lifter_release;
		JoystickButton *robot_lifter_up;
		JoystickButton *robot_lifter_down;
	public:
		ButtonBoard();
		~ButtonBoard();
		bool getShoot();
		bool getPickupUp();
		bool getPickupDown();
		int getPos();
		int getLifterPos();
};

#endif /* SRC_SUBSYSTEMS_BUTTONBOARD_H_ */
