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

std::vector<Region *>*  HoughCircleDetection::processFrame(cv::Mat& frame) {
	//code taken from http://docs.opencv.org/doc/tutorials/imgproc/imgtrans/hough_circle/hough_circle.html
	cvtColor(frame, frame, CV_BGR2GRAY);
	GaussianBlur(frame, frame, cv::Size(9, 9), 2, 2);
	cv::vector<cv::Vec3f> circles;
	HoughCircles(frame, circles, CV_HOUGH_GRADIENT, 1, frame.rows/8, 200, 100, 0, 0 );

	for (unsigned int i = 0; i < circles.size(); i++) {
		regionList->push_back(new Region(circles[i][0], circles[i][1], circles[i][2]));
	}
	return regionList;
}
