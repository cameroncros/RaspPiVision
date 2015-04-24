/*
 * HSVProcessor.cpp
 *
 *  Created on: Apr 25, 2015
 *      Author: cameron
 */

#include "HSVProcessor.h"
#include <iostream>

HSVProcessor::HSVProcessor(cv::VideoCapture capture) : ImageProcessor::ImageProcessor(capture) {
	// TODO Auto-generated constructor stub

}

HSVProcessor::~HSVProcessor() {
	// TODO Auto-generated destructor stub
}

void HSVProcessor::process(int numFrames) {
#ifdef GUI
	char filename[200];
	std::string window_name = "video | q or esc to quit";
	std::cout << "press space to save a picture. q or esc to quit" << std::endl;
	cv::namedWindow(window_name, CV_WINDOW_KEEPRATIO); //resizable window;
	cv::setMouseCallback(window_name, onMouse, 0);
#endif
	cv::Mat frame, hsvFrame;
	for (int z = 0; z < numFrames; z++) {
		capture >> frame;
		if (frame.empty()) {
			break;
		}
		cv::cvtColor(frame, frame, cv::COLOR_BGR2HSV_FULL);
		long sumX = 0, sumY = 0, totalBlue = 0;
		for (int i = 0; i<frame.rows; i++)
		{
			for (int j = 0; j<frame.cols; j++)
			{
				if (isBlue(frame.at<cv::Vec3b>(i, j))) {
					sumX += i;
					sumY += j;
					totalBlue++;
#ifdef GUI
					frame.at<cv::Vec3b>(i, j)[RED]=0;
					frame.at<cv::Vec3b>(i, j)[GREEN]=0;
					frame.at<cv::Vec3b>(i, j)[BLUE]=255;
				} else {
					frame.at<cv::Vec3b>(i, j)[RED]=0;
					frame.at<cv::Vec3b>(i, j)[GREEN]=0;
					frame.at<cv::Vec3b>(i, j)[BLUE]=0;
#endif
				}

			}
		}
		if (totalBlue > 1) {
			double xcoord = sumX/totalBlue-frame.rows/2;
			double ycoord = sumY/totalBlue-frame.cols/2;

			//double dist = sqrt(xcoord*xcoord+ycoord*ycoord);

			std::cout << z << ")\tCentre of blue is: " << sumX/totalBlue << "," << sumY/totalBlue << std::endl;
			//std::cout << "Angle: " << atan2(xcoord, ycoord) << "Distance: " << dist << std::endl;
		} else {
			std::cout << "No blue in image" << std::endl;
		}

#ifdef GUI
		cv::imshow(window_name, frame);

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
	std::cout << "Frame size is: " << frame.rows << "," << frame.cols << std::endl;
}

bool HSVProcessor::isBlue(cv::Vec3b point)
{
	if (point[0] < 250 && point[0] > 210) {
		return true;
	}
	return false;
}
