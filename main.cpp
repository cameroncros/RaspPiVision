/*
 * RSD_starter_video.cpp
 *
 * This code was developed for students studying RME40003 Robot Systems Design at Swinburne
 * University of Technology in Melbourne, Australia
 *
 * This code is largely based on the 'starter_video.cpp' code created by Ethan Rublee, Nov 23,
 * 2010 for use with OpenCV software. Ethan Rublee's code comes packaged with the OpenCV files
 * and can be found in ..\OpenCV\sources\samples\cpp\
 *
 * This is a simple starter sample  for using opencv, getting a video stream, displaying images,
 * reading and outputting pixel values, and modifying pixel values.
 *
 */

/*
 * CODE MODIFICATIONS AND BUG FIXES
 * 24/07/2014 Code added by Michelle Dunn to read, output and modify pixel values
 * 21/08/2014 Comments added by Michelle Dunn for Swinburne students
 */
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <vector>
#include <stdio.h>

#define BLUE 0
#define GREEN 1
#define RED 2

void onMouse(int event, int x, int y, int, void*);
bool isBlue(cv::Vec3b point);


//hide the local functions in an anon namespace
void help(char** av) {
	std::cout << "\nThis program justs gets you started reading images from video\n"
			"Usage:\n./" << av[0] << " <video device number>\n"
			<< "q,Q,esc -- quit\n"
			<< "space   -- save frame\n\n"
			<< "\tThis is a starter sample, to get you up and going in a copy pasta fashion\n"
			<< "\tThe program captures frames from a camera connected to your computer.\n"
			<< "\tTo find the video device number, try ls /dev/video* \n"
			<< "\tYou may also pass a video file, like my_vide.avi instead of a device number"
			<< std::endl;
}

int process(cv::VideoCapture& capture) {
	int n = 0;
	char filename[200];
	std::string window_name = "video | q or esc to quit";
	std::cout << "press space to save a picture. q or esc to quit" << std::endl;
	cv::namedWindow(window_name, CV_WINDOW_KEEPRATIO); //resizable window;
	cv::setMouseCallback(window_name, onMouse, 0);
	cv::Mat frame;
	for (;;) {
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
					frame.at<cv::Vec3b>(i, j)[RED]=0;
					frame.at<cv::Vec3b>(i, j)[GREEN]=0;
					frame.at<cv::Vec3b>(i, j)[BLUE]=255;
				} else {
					frame.at<cv::Vec3b>(i, j)[RED]=0;
					frame.at<cv::Vec3b>(i, j)[GREEN]=0;
					frame.at<cv::Vec3b>(i, j)[BLUE]=0;
				}

			}
		}
		if (totalBlue > 1) {
			double xcoord = sumX/totalBlue-frame.rows/2;
			double ycoord = sumY/totalBlue-frame.cols/2;

			double dist = sqrt(xcoord*xcoord+ycoord*ycoord);

			std::cout << "Centre of blue is: " << sumX/totalBlue << "," << sumY/totalBlue << std::endl;
			std::cout << "Angle: " << atan2(xcoord, ycoord) << "Distance: " << dist << std::endl;
			std::cout << "Frame size is: " << frame.rows << "," << frame.cols << std::endl;
		} else {
			std::cout << "No blue in image" << std::endl;
		}


		cv::imshow(window_name, frame);
		char key = (char)cv::waitKey(5); //delay N millis, usually long enough to display and capture input
		switch (key) {
		case 'q':
		case 'Q':
		case 27: //escape key
			return 0;
		case ' ': //Save an image
			sprintf(filename, "filename%.3d.jpg", n++);
			cv::imwrite(filename, frame);
			std::cout << "Saved " << filename << std::endl;
			break;
		default:
			break;
		}
	}
	return 0;
}

void onMouse(int event, int x, int y, int, void*)
{
	if (event != CV_EVENT_LBUTTONDOWN)
		return;

	cv::Point pt = cv::Point(x, y);
	std::cout << "x=" << pt.x << "\t y=" << pt.y << std::endl;

}

bool isBlue(cv::Vec3b point) {
	if (point[BLUE] > 1.8*point[GREEN] &&
		point[BLUE] > 1.8*point[RED]) {
		return true;
	}
	return false;
}

int main(int ac, char** av) {

	if (ac != 2) {
		help(av);
		return 1;
	}
	std::string arg = av[1];
	cv::VideoCapture capture(arg); //try to open string, this will attempt to open it as a video file
	if (!capture.isOpened()) //if this fails, try to open as a video camera, through the use of an integer param
		capture.open(atoi(arg.c_str()));
	if (!capture.isOpened()) {
		std::cerr << "Failed to open a video device or video file!\n" << std::endl;
		help(av);
		return 1;
	}
	return process(capture);
}
