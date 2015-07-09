/*
 * RGBProcessor.cpp
 *
 *  Created on: Apr 25, 2015
 *      Author: cameron
 */

#include "RGBProcessor.h"

#include <iostream>
RGBProcessor::RGBProcessor(cv::VideoCapture capture) : ImageProcessor::ImageProcessor(capture) {
	methodType = "RGBBasic";

}

RGBProcessor::~RGBProcessor() {
	// TODO Auto-generated destructor stub
}

Region *RGBProcessor::processFrame(cv::Mat &frame) {
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
	if (foundRegion == NULL) {
		delete(foundRegion);
		foundRegion = NULL;
	}
	if (totalBlue > 1) {
		foundRegion = new Region(sumX/totalBlue, sumY/totalBlue, totalBlue);
	}
	return foundRegion;

}

bool RGBProcessor::isBlue(cv::Vec3b point) {
	if (point[BLUE] > 1*point[GREEN] &&
			point[BLUE] > 1*point[RED]) {
		return true;
	}
	return false;
}
