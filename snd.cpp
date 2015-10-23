/*
 * snd.c - Search and Destroy - Robot spins around until it finds the shape it wants, then it goes and kills it.
 *
 *  Created on: 17 Jun 2015
 *      Author: cameron
 */

#include "robot/BotController.h"
#include "vision/ImageProcessor.h"
#include "vision/BasicShapeDetection.h"
#include <unistd.h>
#include <iostream>
#include <signal.h>

static volatile int keepRunning = 1; //note for JS, prevents compiler access errors

void intHandler(int dummy) {
    keepRunning = 0;
}

void search(cv::VideoCapture *capture, BotController *bt);
void destroy(cv::VideoCapture *capture, BotController *bt);

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

	BotController *bt = new BotController();
	while (keepRunning) {
		search(&capture, bt);
		destroy(&capture, bt);
	}

	std::cout << "Shutting down" << std::endl;
//	bt->stop();
}

void search(cv::VideoCapture *capture, BotController *bt) {
	cv::Mat frame;
	std::vector<Region *> *regionList;
	//Designed to be modifiable between algs, could nest if statements in case of detection failure of a certain object? -JS
	ImageProcessor *ip = new BasicShapeDetection(*capture);

	(*capture) >> frame;
	while (keepRunning) {
		bt->spin(1);
		bt->sleep(20);
		bt->stop();
		bt->sleep(500);
		(*capture) >> frame;
		ip->cleanRegionList();
		regionList = ip->processFrame(frame);
		if (regionList->size() > 0) {
			for (Region *reg : *regionList) {
				double angle = ip->angle(frame, *reg);
				double dist = ip->distance(frame, *reg);
				ip->drawArrow(frame, angle, dist);
				if (reg->getColor() == BLACK && reg->getShape() == SQUARE) {
					std::cout << "Found the black square" << std::endl;
					return;
				}
			}
		}
		bt->sleep(1);
	}
	bt->stop();
}

void destroy(cv::VideoCapture *capture, BotController *bt) {
	cv::Mat frame;
	std::vector<Region *> *regionList = new std::vector<Region *>();
	ImageProcessor *ip = new BasicShapeDetection(*capture);
	while (keepRunning) {
		(*capture) >> frame;
		ip->cleanRegionList();
		regionList = ip->processFrame(frame);
		if (regionList->size() == 0) {
			break;
		}
		std::sort(regionList->begin(), regionList->end(), compareBySize);
		Region *largestColor, *foundRegion = NULL;
		for (unsigned int i = 0; i < regionList->size(); i++) {
			largestColor = regionList->at(i);
			if (largestColor->getColor() == BLACK && largestColor->getShape() == SQUARE) {
				foundRegion = largestColor;
				break;
			}
		}

		if (foundRegion == NULL) {
			break;
		}

		int halfFrame = frame.cols/2;
		if ((foundRegion->getX()-halfFrame)/halfFrame > 0.2) {
			std::cout << "Object is to the right" << std::endl;
			bt->spin(1);
			bt->sleep(10);
		} else if ((foundRegion->getX()-halfFrame)/halfFrame < -0.2) {
			std::cout << "Object is to the left" << std::endl;
			bt->spin(0);
			bt->sleep(10);
		} else {
			bt->move(0, 1);
			bt->sleep(250);
		}
		bt->stop();
		bt->sleep(500);
	}
}

