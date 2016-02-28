// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#ifndef ROBOTMAP_H
#define ROBOTMAP_H

#include "WPILib.h"
#include "AnalogGyro.h"
#include <Relay.h>
#include "Robot.h"

#define FRONT_RIGHT 7
#define FRONT_LEFT 5
#define BACK_RIGHT 6
#define BACK_LEFT 8

#define SPINNER_CW 2
#define SPINNER_CCW 3
#define SPINNER_SPRING_WINDER 1

#define PORT_SAD 4
#define SCALE_TOWER 1
#define ARMS_UP_AND_OUT 0
#define POSITION 4

//Sensors
#define PORT_POTENTIOMETER 1
#define PORT_ULTRASONIC_PING 6
#define PORT_ULTRASONIC_ECHO 7
#define PORT_GYRO 0

//Limit Switches
#define L_SPINNER_SPRING_WINDER 2
#define L_SAD_POS_UPPERBOUND 4
#define L_SAD_POS_BASELINE 3

//Height Counter (pulses)
#define HEIGHT_COUNTER 5

/**
 *The RobotMap is a mapping from the ports sensors and actuators are wired into
 *to a variable name. This provides flexibility changing wiring, makes checking
 *the wiring easier and significantly reduces the number of magic numbers
 *floating around.
 */
class RobotMap {
	private:
		RobotMap();
	public:
		static RobotMap *robotMap;
		// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
		static SpeedController *robotDriveTreadRightFront;
		static SpeedController *robotDriveTreadRightBack;
		static SpeedController *robotDriveTreadLeftFront;
		static SpeedController *robotDriveTreadLeftBack;

		static SpeedController *ballShooterSpinnerClockwise;
		static SpeedController *ballShooterSpinnerCounterclockwise;
		static SpeedController *shooterAimingDevice; // SAD = Shooter Aiming Device

		static Relay *ballShooterSpinnerSpringWinder;
		static Relay *armsUpAndOut;

		static SpeedController *scaleTower;
		static SpeedController *position;

		static RobotDrive *robotDrive41;

		static AnalogPotentiometer *potentiometer;
		static BuiltInAccelerometer *accelerometer;
		static Ultrasonic *ultrasonic;

		static DigitalInput *limitSpinnerSpringWinder;
		static DigitalInput *limitSADPosBaseline;
		static AnalogTrigger *heightCounter;

		AnalogGyro *gyro;
		// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

		static void
		init();
		static double degreeToPotentiometer(double);
		static double potentiometerToDegree(double);
};
#endif
