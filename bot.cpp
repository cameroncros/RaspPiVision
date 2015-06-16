/*
 * bot.c
 *
 *  Created on: 17 Jun 2015
 *      Author: cameron
 */

#include "robot/BotController.h"
#include <unistd.h>
#include <iostream>


int main(int argc, char **argv)
{
	BotController *bt = new BotController();

	usleep(1000);
	bt->move(0, 100);
	usleep(5000);
	bt->move(180, 100);
	usleep(5000);
	bt->stop();
	for (int i = 0; i < 14; i++) {
		bt->move(i*3, 100);
		usleep(50);
		std::cout << (i*30) << "\t| " << bt->motorPower(0, i*30) << "\t| " << bt->motorPower(1, i*30) << "\t| " << bt->motorPower(2, i*30) << "\t|\t" << std::endl;
	}
	bt->stop();
}
