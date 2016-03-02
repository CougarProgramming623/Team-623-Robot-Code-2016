/*
 * ButtonBoard.h
 *
 *  Created on: Feb 20, 2016
 *      Author: CougarRobotics
 */

#ifndef SRC_SUBSYSTEMS_BUTTONBOARD_H_
#define SRC_SUBSYSTEMS_BUTTONBOARD_H_

#include "Buttons/JoystickButton.h"
#include "Joystick.h"

#define PORT_ARMS_UP_AND_OUT 11
#define PORT_SHOOT 4
#define PORT_BALL_IN 3
#define PORT_BALL_OUT 1
#define PORT_SCALE_TOWER 2
#define PORT_POS_SAFTEY 5
#define PORT_POS_STORE 6
#define PORT_POS_AUTO_AIM 7
#define PORT_POS_PICK_UP 8
#define PORT_PORTCULIS_UP 9
#define PORT_PORTCULIS_DOWN 10
#define PORT_SAD_UP 13 //SAD = Shooter Aiming Device
#define PORT_SAD_DOWN 12

#define POS_NONE 0
#define POS_SAFTEY 1
#define POS_STORE 2
#define POS_AUTO_AIM 3
#define POS_PICK_UP 4

#define SAD_UP 5
#define SAD_DOWN -5
#define SAD_NONE 0

#define BALL_IN 6
#define BALL_OUT -6
#define BALL_NONE 0

#define PORTCULIS_UP 7
#define PORTCULIS_DOWN -7
#define PORTCULIS_NONE 0

class ButtonBoard : public Joystick {
	private:
		JoystickButton *SAD_up; //SAD = Shooter Aiming Device
		JoystickButton *SAD_down;
		JoystickButton *arms_up_and_out;
		JoystickButton *shoot;
		JoystickButton *ball_in;
		JoystickButton *ball_out;
		JoystickButton *scale_tower;
		JoystickButton *pos_saftey;
		JoystickButton *pos_store;
		JoystickButton *pos_auto_aim;
		JoystickButton *pos_pickup;
		JoystickButton *port_up;
		JoystickButton *port_down;
	public:
		ButtonBoard(int port);
		~ButtonBoard();

		int
		getSADPos();
		int
		getPresetPos();
		int
		getPortPos();
		int
		getBallSpinner();
		bool
		getScaleTower();
		bool
		getArmsUpAndOut();
		bool
		getShoot();
};

#endif /* SRC_SUBSYSTEMS_BUTTONBOARD_H_ */
