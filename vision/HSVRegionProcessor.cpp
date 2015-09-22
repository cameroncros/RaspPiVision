/*
 * HSVRegionProcessor.cpp
 *
 *  Created on: 8 Jul 2015
 *      Author: cameron
 */

#include "HSVRegionProcessor.h"
#include <queue>

HSV_Region_Processor::HSV_Region_Processor(cv::VideoCapture &capture) : HSVProcessor::HSVProcessor(capture) {
	// TODO Auto-generated constructor stub
	methodType = "HSVRegion";
}

HSV_Region_Processor::~HSV_Region_Processor() {
	// TODO Auto-generated destructor stub
}

void HSV_Region_Processor::processFrame(cv::Mat &frame, std::vector<Region *> &regionList)
{
	cv::Mat hsvFrame;
	cv::cvtColor(frame, hsvFrame, cv::COLOR_BGR2HSV);

	for (int i = 0; i<hsvFrame.rows; i++)
	{
		for (int j = 0; j<hsvFrame.cols; j++)
		{

			if (isBlue(hsvFrame.at<cv::Vec3b>(i, j))) {
				Region *region = findRegion(hsvFrame, i, j);
				if (region != NULL) {
					regionList.push_back(region);
				}
			}

		}
	}
}

Region *HSV_Region_Processor::findRegion(cv::Mat &frame, int i, int j) {
	std::queue<cv::Point *> *pointList = new std::queue<cv::Point *>();
	cv::Point *start = new cv::Point(j,i);
	pointList->push(start);
	long sumX = 0, sumY = 0, totalBlue = 0;

	while(pointList->size() != 0) {
		cv::Point *temp = pointList->front();
		cv::Vec3b &point = frame.at<cv::Vec3b>(*temp);
		if (isBlue(point)) {
			sumX += temp->x;
			sumY += temp->y;
			totalBlue++;
			point=black;
			if (temp->x != frame.cols-1) {pointList->push(new cv::Point(temp->x+1, temp->y));};
			if (temp->x != 0           ) {pointList->push(new cv::Point(temp->x-1, temp->y));};
			if (temp->y != frame.rows-1) {pointList->push(new cv::Point(temp->x, temp->y+1));};
			if (temp->y != 0           ) {pointList->push(new cv::Point(temp->x, temp->y-1));};
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
