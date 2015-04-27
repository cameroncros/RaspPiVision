/*
 * ImageProcessor.cpp
 *
 *  Created on: Apr 25, 2015
 *      Author: cameron
 */

#include "ImageProcessor.h"
#include <iostream>
#include <stdio.h>

#define GUI

ImageProcessor::ImageProcessor(cv::VideoCapture capture) {
	this->capture = capture;
}

ImageProcessor::~ImageProcessor() {
	// TODO Auto-generated destructor stub
}

void ImageProcessor::printCentre(int line, int x, int y)
{
	std::cout << line << ") " << x << "," << y << std::endl;
}

void ImageProcessor::drawArrow(cv::Mat frame, double angle,
		double dist) {
	cv::Point start, finish;
	start.x = frame.cols/2;
	start.y = frame.rows/2;

	finish.x = frame.cols/2+dist*cos(angle);
	finish.y = frame.rows/2+dist*sin(angle);

	cv::line(frame, start, finish, cv::Scalar(128,128,128), 10);
}

void ImageProcessor::drawFrame(cv::Mat frame, double angle, double dist)
{
#ifdef GUI
		drawArrow(frame, angle, dist);
		cv::imshow(window_name, frame);
#endif
}


void ImageProcessor::processKeys(cv::Mat frame)
{
#ifdef GUI
		char key = (char)cv::waitKey(5); //delay N millis, usually long enough to display and capture input
		switch (key) {
		case 'q':
		case 'Q':
		case 27: //escape key
			return;
		case ' ': //Save an image
			sprintf(filename, "filename%.3d.jpg", n++);
			cv::imwrite(filename, frame);
			std::cout << "Saved " << filename << std::endl;
			break;
		default:
			break;
		}
#endif
}

void ImageProcessor::initialiseWindow()
{
#ifdef GUI
	std::cout << "press space to save a picture. q or esc to quit" << std::endl;
	cv::namedWindow(window_name, CV_WINDOW_KEEPRATIO); //resizable window;
	cv::setMouseCallback(window_name, onMouse, 0);
#endif
}


void onMouse(int event, int x, int y, int, void*)
{
	if (event != CV_EVENT_LBUTTONDOWN)
		return;

	cv::Point pt = cv::Point(x, y);
	std::cout << "x=" << pt.x << "\t y=" << pt.y << std::endl;

}

