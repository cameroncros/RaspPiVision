/*
 * ImageProcessor.cpp
 *
 *  Created on: Apr 25, 2015
 *      Author: cameron
 */

#include "ImageProcessor.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>

ImageProcessor::ImageProcessor(cv::VideoCapture capture) {
	this->capture = capture;
	black = cv::Vec3b(0,0,0);
}

ImageProcessor::~ImageProcessor() {
	// TODO Auto-generated destructor stub
}

void ImageProcessor::process(int numFrames) {
	initialiseWindow();
	cv::Mat frame, hsvFrame;
	double angle, dist;
	clock_t t = clock();
	for (int z = 0; z < numFrames; z++) {
		capture >> frame;
		if (frame.empty()) {
			break;
		}
		processFrame(frame);
		drawFrame(frame, angle, dist);
		processKeys(frame);
	}
	difftime = clock()-t;
}

void ImageProcessor::printCentre(int line, int x, int y)
{
	//std::cout << line << ") " << x << "," << y << std::endl;

	std::cout << x << "," << y << ",";
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
	char key = 0;
	while (key != ' ') {
		key= (char)cv::waitKey(5); //delay N millis, usually long enough to display and capture input

		switch (key) {
		case 'q':
		case 'Q':
		case 27: //escape key
			exit;
		case 's': //Save an image
			sprintf(filename, "filename%.3d.jpg", n++);
			cv::imwrite(filename, frame);
			std::cout << "Saved " << filename << std::endl;
			break;
		default:
			break;
		}
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

void ImageProcessor::loadBenchmark(std::string benchfile)
{
	std::string line;
	std::ifstream *myfile = new std::ifstream(benchfile);
	if (myfile->is_open())
	{
		while ( std::getline (*myfile,line, ',') )
		{
			try {
			double val = std::stod(line);

			baseline.push_back(val);
			}
			catch (std::exception e) {
				std::cout << "Invalid Argument: " << line << std::endl;
			}

		}
		myfile->close();
	}
}

int ImageProcessor::compareToBaseline()
{
	double error = 0;
	double value;
	if (baseline.size() != calc.size())
	{
		std::cout << "Outputs are different lengths" << std::endl;
	}
	else
	{
		for (int i = 0; i < baseline.size(); i++)
		{
			value = abs(baseline[i]-calc[i]);
			if (value > error)
			{
				error = value;
			}
		}
		std::cout << "Max Error: " << error << std::endl;
	}
	return error;
}

void ImageProcessor::printType()
{
	std::cout << methodType << std::endl;
}

void ImageProcessor::printTime()
{
	std::cout << difftime/(CLOCKS_PER_SEC/1000) << " milliseconds" << std::endl;
}
