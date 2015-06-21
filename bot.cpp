/*
 * bot.c
 *
 *  Created on: 17 Jun 2015
 *      Author: cameron
 */

#include "robot/BotController.h"
#include "vision/ImageProcessor.h"
#include "vision/HSVProcessor.h"
#include <unistd.h>
#include <iostream>


int main(int argc, char **argv)
{
	if (argc != 2) {
		exit(1);
	}

	cv::VideoCapture capture(argv[1]);

	ImageProcessor *ip = new HSVProcessor(capture);
	BotController *bt = new BotController();
	DoublePair dp;
	cv::Mat frame;
	while (true) {
		capture >> frame;
		dp = ip->processFrame(frame);
		if (dp.getX() != -1 && dp.getY() != -1) {
			double angle = ip->angle(frame, dp);
			double distance = ip->distance(frame, dp);
			std::cout << angle << " - " << distance << std::endl;
			bt->move(angle, distance);
		} else {
			std::cout << "No object found, sitting still" << std::endl;
		}
	}
}
