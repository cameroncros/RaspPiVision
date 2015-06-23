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
	minTime = INT32_MAX;
	maxTime = INT32_MIN;
}

ImageProcessor::~ImageProcessor() {
	// TODO Auto-generated destructor stub
}

void ImageProcessor::process(int maxFrames) {
	initialiseWindow();
	cv::Mat frame, hsvFrame;
	long difftime;
	for (int z = 0; z < maxFrames; z++) {
		capture >> frame;
		if (frame.empty()) {
			break;
		}
		clock_t t = clock();
		calc[z] = processFrame(frame);
		//printCentre(z, calc[z]);
		difftime = clock()-t;
		totalTime += difftime;
		if (difftime > maxTime) {
			maxTime = difftime;
		}
		if (difftime < minTime) {
			minTime = difftime;
		}

		numFrames++;

		drawFrame(frame, angle(frame, calc[z]), distance(frame, calc[z]));
		processKeys(frame);
	}
}

double ImageProcessor::distance(cv::Mat frame, DoublePair var)
{
	double xcoord = var.getX()-frame.rows/2;
	double ycoord = var.getY()-frame.cols/2;

	return sqrt(xcoord*xcoord+ycoord*ycoord);
}

double ImageProcessor::angle(cv::Mat frame, DoublePair var)
{
	double xcoord = var.getX()-frame.rows/2;
	double ycoord = var.getY()-frame.cols/2;

	return atan2(xcoord, ycoord)*180/M_PI;
}

void ImageProcessor::printCentre(int line, DoublePair val)
{
	//std::cout << line << ") " << x << "," << y << std::endl;

	std::cout << line << "," << val.getX() << "," << val.getY() << std::endl;
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

void ImageProcessor::saveFrame(const cv::Mat& frame) {
	sprintf(filename, "filename%.3d.jpg", n++);
	cv::imwrite(filename, frame);
	std::cout << "Saved " << filename << std::endl;
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
			saveFrame(frame);
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
		while (!myfile->eof() )
		{

			try {
				std::getline (*myfile,line, ',');
				int lineNo = std::stoi(line);
				std::getline (*myfile,line, ',');
				double x = std::stod(line);
				std::getline (*myfile,line);
				double y = std::stod(line);
				DoublePair *vals = new DoublePair(x,y);
				baseline[lineNo] = *vals;
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
		for (auto const &it1 : baseline)
		{

			DoublePair val = calc[it1.first];
			value = it1.second.compare(val);
			if (value > error)
			{
				error = value;
			}
		}
		std::cout << "Max Error: " << error << std::endl;
	}
	return error;
}

void ImageProcessor::printReport()
{
	std::cout << methodType << std::endl;
	std::cout << "Total time taken (ms): " << totalTime/(CLOCKS_PER_SEC/1000) << std::endl;
	std::cout << "Average Frame Time (ms): " << (totalTime/(CLOCKS_PER_SEC/1000))/numFrames << std::endl;
	std::cout << "Minimum Frame Time (ms): " << minTime/(CLOCKS_PER_SEC/1000) << std::endl;
	std::cout << "Maximum Frame Time (ms): " << maxTime/(CLOCKS_PER_SEC/1000) << std::endl;
	compareToBaseline();
	std::cout << std::endl;



}
