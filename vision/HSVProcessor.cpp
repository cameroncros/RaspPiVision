/*
 * HSVProcessor.cpp
 *
 *  Created on: Apr 25, 2015
 *      Author: cameron
 */

#include "HSVProcessor.h"
#include <iostream>

HSVProcessor::HSVProcessor(cv::VideoCapture &capture) : ImageProcessor::ImageProcessor(capture) {
	// TODO Auto-generated constructor stub
	methodType = "HSVBasic";

}

HSVProcessor::~HSVProcessor() {
	// TODO Auto-generated destructor stub
}

Region *HSVProcessor::processFrame(cv::Mat &frame)
{
	cv::Mat hsvFrame;
	cv::cvtColor(frame, hsvFrame, cv::COLOR_BGR2HSV);
			long sumX = 0, sumY = 0, totalBlue = 0;
			for (int i = 0; i<hsvFrame.rows; i++)
			{
				for (int j = 0; j<hsvFrame.cols; j++)
				{

					if (isBlue(hsvFrame.at<cv::Vec3b>(i, j))) {
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
			frame = hsvFrame;
			return foundRegion;
}

bool HSVProcessor::isBlue(cv::Vec3b point)
{
	if (point[1] > 70 && point[0] < 140 && point[0] > 100) {
		return true;
	}
	return false;
}
