/*
 * selector.c - Object shape selector - Provides somewhat arbitrary stub/skeleton for selecting a shape that the robot will chase
 *
 *  Created on: 02 Oct 2015
 *      Author: jonathan
 */

#include "robot/BotController.h"
#include "vision/ImageProcessor.h"
#include "vision/HoughCircleDetection.h"
#include <unistd.h>
#include <iostream>
#include <signal.h>
#include <cstddef> // size_t is a typedef on an unsigned int

static volatile int keepRunning = 1; //note for JS, prevents compiler access errors

void intHandler(int dummy) {
    keepRunning = 0;
}

int choice = 0; //Circle by default

void select(cv::VideoCapture *capture, BotController *bt, int choice);

int main()
{
	const char* shapes[] = { "Circle", "Square", "Triangle" } ;
	std::cout << "Choose shape: (1)Circle, (2)Square, (3)Triangle" ;
	std::size_t Number ;
	std::cin >> Number ;
	Number-1;
	if ( (Number > 2) || (Number < 0) ){
	  	std::cerr << "Not a choice! Defaulting to circe." << std::endl;
	}
	else
	{
		std::cout << "Chosen: \"" << shapes[Number] << "\"" << std::endl;
		choice = Number;
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
		search(&capture, bt, choice);
	}

	std::cout << "Shutting down" << std::endl;
	bt->stop();

	return 0 ;
}

void search(cv::VideoCapture *capture, BotController *bt, int selection) {
	cv::Mat frame;
	std::vector<Region *> *regionList;
	if (selection == 0){
		std::cout << "Searching for circle" << std::endl;
		ImageProcessor *ip = new HoughCircleDetection(*capture);
	}
	else if (selection == 1){
		std::cout << "Searching for square" << std::endl;
		//alternate algorithm
	}
	else if (selection == 2){
		std::cout << "Searching for triangle" << std::endl;
		//nothing here yet
	}
	else {
		ImageProcessor *ip = null;
		//error
	}
}

