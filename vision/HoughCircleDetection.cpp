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
	cv::Mat newFrame;
	cvtColor(frame, newFrame, CV_BGR2GRAY);
	GaussianBlur(newFrame, newFrame, cv::Size(9, 9), 2, 2);
	cv::vector<cv::Vec3f> circles;
	HoughCircles(newFrame, circles, CV_HOUGH_GRADIENT, 1, frame.rows/8, 40, 40, 0, 0 );

	for (unsigned int i = 0; i < circles.size(); i++) {
		Color col = getColor(frame, circles[i][0], circles[i][1], circles[i][2]);
		regionList->push_back(new Region(circles[i][0], circles[i][1], circles[i][2], col));
	}
	return regionList;
}

//get average pixel colors in a square that is half the size;
Color HoughCircleDetection::getColor(cv::Mat frame, int x, int y, int size) {
	long r = 0, b = 0, g = 0, total=0;
	int squareWidth = size/2;
	for (int i = x-(squareWidth/2); i < x+(squareWidth/2); i++) {
		for (int j = y-(squareWidth/2); j < y+(squareWidth/2); j++) {
			total++;
			cv::Vec3b val = frame.at<cv::Vec3b>(i, j);
			r += val[RED];
			b += val[BLUE];
			g += val[GREEN];
		}
	}
	r /= total;
	b /= total;
	g /= total;

	cv::Vec3b averageVal;
	averageVal[RED]=r;
	averageVal[BLUE]=b;
	averageVal[GREEN]=g;

	cvtColor(averageVal, averageVal, CV_BGR2HSV);
	if (averageVal[1] < 70) {
		return WHITE;
	}
	if (averageVal[2] < 70) {
		return BLACK;
	}

	if (averageVal[0] < 140 && averageVal[0] > 100) {
		return BLUE;
	}

	return UNKNOWN;
}
