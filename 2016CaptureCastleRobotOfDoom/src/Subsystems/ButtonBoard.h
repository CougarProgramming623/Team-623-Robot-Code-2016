/*
 * ButtonBoard.h
 *
 *  Created on: Feb 20, 2016
 *      Author: CougarRobotics
 */

#ifndef SRC_SUBSYSTEMS_BUTTONBOARD_H_
#define SRC_SUBSYSTEMS_BUTTONBOARD_H_

#include "Joystick.h"
#include "Buttons/JoystickButton.h"

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

#define LED_PORTCULIS_DOWN (1 << 0)
#define LED_PORTCULIS_UP (1 << 1)
#define LED_POS_PICK_UP (1 << 2)
#define LED_POS_AUTO_AIM (1 << 3)
#define LED_SHOT_COMPLETE (1 << 4)
#define LED_POS_SAFETY (1 << 5)

#define LEDS_SCOOP (LED_PORTCULIS_DOWN | LED_PORTCULIS_UP | LED_POS_PICK_UP | \
						  LED_POS_AUTO_AIM | LED_POS_SAFETY)

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
		uint32_t outputs;
	public:
		ButtonBoard(int port);
		~ButtonBoard();
		void ResetScoopLEDs(void);
		void EnableLEDs(uint32_t mask);
		void DisableLEDs(uint32_t mask);
};

#endif /* SRC_SUBSYSTEMS_BUTTONBOARD_H_ */
