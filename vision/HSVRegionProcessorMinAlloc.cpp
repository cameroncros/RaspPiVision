/*
 * HSVRegionProcessorMinAlloc.cpp
 *
 *  Created on: 15 Jul 2015
 *      Author: cameron
 */

#include "HSVRegionProcessorMinAlloc.h"

HSV_Region_Processor_Min_Alloc::HSV_Region_Processor_Min_Alloc(cv::VideoCapture &capture) : HSV_Region_Processor::HSV_Region_Processor(capture) {
	methodType = "HSVRegionMinAlloc";
	pointList = new PointQueue(10000);
	regionList = new RegionQueue(10000);
}

HSV_Region_Processor_Min_Alloc::~HSV_Region_Processor_Min_Alloc() {
	delete(pointList);
	delete(regionList);
}

Region *HSV_Region_Processor_Min_Alloc::processFrame(cv::Mat &frame)
{
	cv::Mat hsvFrame;
	cv::cvtColor(frame, hsvFrame, cv::COLOR_BGR2HSV);
	double regX=0, regY=0, regSize=0;
	regionList->reset();
	for (int i = 0; i<hsvFrame.rows; i++)
	{
		for (int j = 0; j<hsvFrame.cols; j++)
		{

			if (isBlue(hsvFrame.at<cv::Vec3b>(i, j))) {
				findRegion(hsvFrame, i, j, regX, regY, regSize);
				if (regSize != -1) {
					regionList->append(regX, regY, regSize);
				}
			}

		}
	}
	frame = hsvFrame;
	return regionList->findLargest();
}

void HSV_Region_Processor_Min_Alloc::findRegion(cv::Mat &frame, int i, int j, double &regX, double &regY, double &regSize) {
	pointList->append(i,j);
	long sumX = 0, sumY = 0;
	regSize = 0;

	while(pointList->size() != 0) {
		int tempX = pointList->getX();
		int tempY = pointList->getY();
		cv::Vec3b &point = frame.at<cv::Vec3b>(tempX, tempY);
		if (isBlue(point)) {
			sumX += tempX;
			sumY += tempY;
			regSize++;
			point=black;
			if (tempX != frame.rows-1) {pointList->append(tempX+1, tempY);};
			if (tempX != 0           ) {pointList->append(tempX-1, tempY);};
			if (tempY != frame.cols-1) {pointList->append(tempX, tempY+1);};
			if (tempY != 0           ) {pointList->append(tempX, tempY-1);};
		}
		pointList->pop();
	}
	if (regSize > 1) {
		regX = sumX/regSize;
		regY = sumY/regSize;
	} else {
		regX = -1;
		regY = -1;
		regSize = -1;
	}
}
