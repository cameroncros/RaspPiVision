/*
 * HSVProcessor.cpp
 *
 *  Created on: Apr 25, 2015
 *      Author: cameron
 */

#include "HSVProcessor.h"
#include <iostream>

HSVProcessor::HSVProcessor(cv::VideoCapture capture) : ImageProcessor::ImageProcessor(capture) {
	// TODO Auto-generated constructor stub

}

HSVProcessor::~HSVProcessor() {
	// TODO Auto-generated destructor stub
}

void HSVProcessor::process(int numFrames) {
	initialiseWindow();
	cv::Mat frame, hsvFrame;
	double angle, dist;
	for (int z = 0; z < numFrames; z++) {
		capture >> frame;
		if (frame.empty()) {
			break;
		}
		cv::cvtColor(frame, hsvFrame, cv::COLOR_BGR2HSV_FULL);
		long sumX = 0, sumY = 0, totalBlue = 0;
		for (int i = 0; i<hsvFrame.rows; i++)
		{
			for (int j = 0; j<hsvFrame.cols; j++)
			{
				if (isBlue(hsvFrame.at<cv::Vec3b>(i, j))) {
					sumX += i;
					sumY += j;
					totalBlue++;
				}

			}
		}
		if (totalBlue > 1) {
			double xcoord = sumX/totalBlue-hsvFrame.rows/2;
			double ycoord = sumY/totalBlue-hsvFrame.cols/2;

			dist = sqrt(xcoord*xcoord+ycoord*ycoord);
			angle = atan2(xcoord, ycoord);
			printCentre(z, sumX/totalBlue, sumY/totalBlue);


			//std::cout << "Angle: " << angle << "Distance: " << dist << std::endl;
		} else {
			std::cout << "No blue in image" << std::endl;
		}
		drawFrame(frame, angle, dist);
		processKeys(frame);
	}
}

bool HSVProcessor::isBlue(cv::Vec3b point)
{
	if (point[0] < 250 && point[0] > 210) {
		return true;
	}
	return false;
}
