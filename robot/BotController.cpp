/*
 * BotController.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: cameron
 */

#include "BotController.h"
#include "gertbot/gb_drivers.h"
#include <iostream>
#include <unistd.h>
#include <cmath>

BotController::BotController() {
	open_connection(0);
	stop_all();
	set_mode(0, 0, GB_MODE_BRUSH);
	set_mode(0, 1, GB_MODE_BRUSH);
	set_mode(0, 2, GB_MODE_OFF);
	set_mode(0, 3, GB_MODE_BRUSH);

}

BotController::~BotController() {
	// TODO Auto-generated destructor stub
}

//need some complex math to make the bot move correctly
void BotController::move(double direction, double speed) {
	for (int i = 0; i < 3; i++) {
		double power = motorPower(i, direction);
		pwm_brushed(0, i, 1000, abs(power));
		if (i == 2) i = 3;
		if (power > 0) {
			move_brushed(0, i, GB_MOVE_A);
		} else if (power < 0) {
			move_brushed(0, i, GB_MOVE_B);
		} else {
			move_brushed(0, i, GB_MOVE_STOP);
		}
	}
}

double BotController::motorPower(int motorNum, double direction) {
	//global offset
	direction-=120;
	//different motor offsets
	if (motorNum == 1) {
		direction-=120;
	} else if (motorNum == 2) {
		direction-=240;
	}
	//normalise number to 0-360
	while (direction < 0) {
		direction += 360;
	}
	while (direction >360) {
		direction -= 360;
	}
	//determine motor output from -100 - 100
	if (direction >= 0 && direction < 60) {
		return 100*(direction)/60;
	} else if (direction >= 60 && direction <= 120) {
		return 100;
	} else if (direction > 120 && direction < 240) {
		return -100*(direction-180)/60;
	} else if (direction >= 240 && direction <= 300) {
		return -100;
	} else if (direction > 300 && direction <=360) {
		return -100*(direction-300)/60;
	} else {
		throw new std::exception();
	}
}

void BotController::spin(bool clockwise) {
	int direction;
	if (clockwise) {
		direction = GB_MOVE_A;
	} else {
		direction = GB_MOVE_B;
	}
	for (int i = 0; i < 3; i++) {
		if (i == 2) i = 3;
		move_brushed(0, i, direction);
	}
}

void BotController::sleep(int ms) {
	usleep((time_t)time);
}

void BotController::stop() {
	stop_all();
}
