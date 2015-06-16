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
		bt->move(ip->angle(frame, dp), ip->distance(frame, dp));
	}
}
