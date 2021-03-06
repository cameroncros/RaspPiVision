/*
 * bot.c
 *
 *  Created on: 17 Jun 2015
 *      Author: cameron
 */

#include "robot/BotController.h"
#include "vision/ImageProcessor.h"
#include "vision/HSVRegionProcessorMinAlloc.h"
#include <unistd.h>
#include <iostream>
#include <signal.h>

static volatile int keepRunning = 1;

void intHandler(int dummy) {
    keepRunning = 0;
}

int main(int argc, char **argv)
{
	if (argc != 2) {
		exit(1);
	}
	signal(SIGINT, intHandler);

	std::string arg = argv[1];
 	cv::VideoCapture capture(arg); //try to open string, this will attempt
        if (!capture.isOpened()) //if this fails, try to open as a video camera
                capture.open(atoi(arg.c_str()));
        if (!capture.isOpened()) {
                std::cerr << "Failed to open a video device or video file!\n" << std::endl;
                return 1;
        }

	ImageProcessor *ip = new HSV_Region_Processor_Min_Alloc(capture);
	BotController *bt = new BotController();
	Region *dp;
	cv::Mat frame;
	ip->initialiseWindow();
	std::vector<Region *> *regionList;
	while (keepRunning) {
		capture >> frame;
		ip->cleanRegionList();
		regionList = ip->processFrame(frame);
		std::sort(regionList->begin(), regionList->end(), compareBySize);
		dp = (*regionList)[0];
		if (dp != NULL && dp->getSize() > 100) {
			double angle = ip->angle(frame, *dp);
			double distance = ip->distance(frame, *dp);
			std::cout << angle << " - " << distance << std::endl;
			bt->move(angle, distance);
			ip->drawArrow(frame, angle, distance);

			//ip->saveFrame(frame);
		} else {
			std::cout << "No object found, sitting still" << std::endl;
			bt->stop();
		}
		ip->drawFrame(frame);
		cv::waitKey(5);
//		ip->processKeys(frame);
	}
	std::cout << "Shutting down" << std::endl;
	bt->stop();
}
