/*
 * HSVRegionProcessor.cpp
 *
 *  Created on: 8 Jul 2015
 *      Author: cameron
 */

#include "HSVRegionProcessor.h"
#include <queue>

HSV_Region_Processor::HSV_Region_Processor(cv::VideoCapture capture) : ImageProcessor::ImageProcessor(capture) {
	// TODO Auto-generated constructor stub
	methodType = "HSVRegion";
}

HSV_Region_Processor::~HSV_Region_Processor() {
	// TODO Auto-generated destructor stub
}

Region *HSV_Region_Processor::processFrame(cv::Mat &frame)
{
	cv::Mat hsvFrame;
	cv::cvtColor(frame, hsvFrame, cv::COLOR_BGR2HSV_FULL);

	std::vector<Region *> *regionList = new std::vector<Region *>();

	for (int i = 0; i<hsvFrame.rows; i++)
	{
		for (int j = 0; j<hsvFrame.cols; j++)
		{

			if (isBlue(hsvFrame.at<cv::Vec3b>(i, j))) {
				Region *region = findRegion(hsvFrame, i, j);
				if (region != NULL) {
					regionList->push_back(region);
				}
			}

		}
	}
	double largeSize = 0;
	for (Region *reg : *regionList) {
		if (reg->getSize() > largeSize ) {
			if (foundRegion != NULL) {
				delete(foundRegion);
				foundRegion = NULL;
			}
			largeSize = reg->getSize();
			foundRegion = reg;
		} else {
			delete(reg);
		}
	}
	delete(regionList);
	return foundRegion;
}

bool HSV_Region_Processor::isBlue(cv::Vec3b point)
{
	if (point[0] < 140 && point[0] > 100) {
		return true;
	}
	return false;
}

Region *HSV_Region_Processor::findRegion(cv::Mat &frame, int i, int j) {
	std::queue<cv::Point *> *pointList = new std::queue<cv::Point *>();
	cv::Point *start = new cv::Point(j,i);
	pointList->push(start);
	long sumX = 0, sumY = 0, totalBlue = 0;

	while(pointList->size() != 0) {
		cv::Point *temp = pointList->front();
		if (isBlue(frame.at<cv::Vec3b>(*temp))) {
			sumX += i;
			sumY += j;
			totalBlue++;
			frame.at<cv::Vec3b>(*temp)=black;
			pointList->push(new cv::Point(temp->x+1, temp->y));
			pointList->push(new cv::Point(temp->x-1, temp->y));
			pointList->push(new cv::Point(temp->x, temp->y+1));
			pointList->push(new cv::Point(temp->x, temp->y-1));
		}
		delete(temp);
		pointList->pop();
	}
	delete(pointList);
	if (totalBlue > 1) {
		return new Region(sumX/totalBlue, sumY/totalBlue, totalBlue);
	} else {
		return NULL;
	}
}
