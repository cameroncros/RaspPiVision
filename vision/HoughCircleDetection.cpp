/*
 * HoughCircleDetection.cpp
 *
 *  Created on: 7 Sep 2015
 *      Author: cameron
 */

#include "HoughCircleDetection.h"

HoughCircleDetection::HoughCircleDetection(cv::VideoCapture &capture) : ImageProcessor::ImageProcessor(capture) {
	// TODO Auto-generated constructor stub
	methodType = "HoughCircleDetection";

}

HoughCircleDetection::~HoughCircleDetection() {
	// TODO Auto-generated destructor stub
}

Region* HoughCircleDetection::processFrame(cv::Mat& frame) {
	//code taken from
	cvtColor(frame, frame, CV_BGR2GRAY);
	GaussianBlur(frame, frame, cv::Size(9, 9), 2, 2);
	cv::vector<cv::Vec3f> circles;
	HoughCircles(frame, circles, CV_HOUGH_GRADIENT, 1, frame.rows/8, 200, 100, 0, 0 );

	int maxRadius = 0;
	int x, y;

	for (int i = 0; i < circles.size(); i++) {
		int radius = circles[i][2];
		if (radius > maxRadius) {
			maxRadius = radius;
			x=circles[i][0];
			y=circles[i][1];
		}
	}
	return new Region(x,y,maxRadius);
}
