/*
 * RGBProcessor.cpp
 *
 *  Created on: Apr 25, 2015
 *      Author: cameron
 */

#include "RGBProcessor.h"

#include <iostream>
RGBProcessor::RGBProcessor(cv::VideoCapture capture) : ImageProcessor::ImageProcessor(capture) {
	// TODO Auto-generated constructor stub

}

RGBProcessor::~RGBProcessor() {
	// TODO Auto-generated destructor stub
}

void RGBProcessor::process(int numFrames) {
#ifdef GUI
	int n = 0;
	char filename[200];
	std::string window_name = "video | q or esc to quit";
	std::cout << "press space to save a picture. q or esc to quit" << std::endl;
	cv::namedWindow(window_name, CV_WINDOW_KEEPRATIO); //resizable window;
	cv::setMouseCallback(window_name, onMouse, 0);
#endif
	cv::Mat frame;
	for (int z = 0; z < numFrames; z++) {
		capture >> frame;
		if (frame.empty()) {
			break;
		}

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

bool RGBProcessor::isBlue(cv::Vec3b point) {
	if (point[BLUE] > 1*point[GREEN] &&
			point[BLUE] > 1*point[RED]) {
		return true;
	}
	return false;
}
