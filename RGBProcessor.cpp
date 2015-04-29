/*
 * RGBProcessor.cpp
 *
 *  Created on: Apr 25, 2015
 *      Author: cameron
 */

#include "RGBProcessor.h"

#include <iostream>
RGBProcessor::RGBProcessor(cv::VideoCapture capture) : ImageProcessor::ImageProcessor(capture) {
	// TODO Auto-generated constructor stub

}

RGBProcessor::~RGBProcessor() {
	// TODO Auto-generated destructor stub
}

void RGBProcessor::process(int numFrames) {
	initialiseWindow();
	cv::Mat frame;
	double angle, dist;
	cv::Vec3b black(0,0,0);
	for (int z = 0; z < numFrames; z++) {
		capture >> frame;
		if (frame.empty()) {
			break;
		}

		long sumX = 0, sumY = 0, totalBlue = 0;
		for (int i = 0; i<frame.rows; i++)
		{
			for (int j = 0; j<frame.cols; j++)
			{
				if (isBlue(frame.at<cv::Vec3b>(i, j))) {
					sumX += i;
					sumY += j;
					totalBlue++;
				} else {
					frame.at<cv::Vec3b>(i, j)=black;
				}

			}
		}
		if (totalBlue > 1) {
			double xcoord = sumX/totalBlue-frame.rows/2;
			double ycoord = sumY/totalBlue-frame.cols/2;

			dist = sqrt(xcoord*xcoord+ycoord*ycoord);
			angle = atan2(xcoord, ycoord);
			calc.push_back(sumX/totalBlue);
			calc.push_back(sumY/totalBlue);
			printCentre(z, sumX/totalBlue, sumY/totalBlue);
		} else {
			//std::cout << "No blue in image" << std::endl;
		}

		drawFrame(frame, angle, dist);
		processKeys(frame);
	}
}

bool RGBProcessor::isBlue(cv::Vec3b point) {
	if (point[BLUE] > 1*point[GREEN] &&
			point[BLUE] > 1*point[RED]) {
		return true;
	}
	return false;
}
