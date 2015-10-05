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
#include "vision/ImageProcessor.h"
#include "vision/RGBProcessor.h"
#include "vision/HSVProcessor.h"
#include "vision/HSVRegionProcessor.h"
#include "vision/HSVRegionProcessorMinAlloc.h"
#include "vision/HoughCircleDetection.h"
#include "vision/BasicShapeDetection.h"

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







int main(int ac, char** av) {

	if (ac != 5) {
		help(av);
		return 1;
	}
	std::string arg = av[1];
	int numFrames = std::stoi(av[3]);
	cv::VideoCapture capture(arg); //try to open string, this will attempt to open it as a video file
	if (!capture.isOpened()) //if this fails, try to open as a video camera, through the use of an integer param
		capture.open(atoi(arg.c_str()));
	if (!capture.isOpened()) {
		std::cerr << "Failed to open a video device or video file!\n" << std::endl;
		help(av);
		return 1;
	}
	ImageProcessor *proc;
	if (std::string(av[2]).compare("RGBBasic") == 0)
	{
		proc = new RGBProcessor(capture);
	}
	else if (std::string(av[2]).compare("HSVBasic") == 0)
	{
		proc = new HSVProcessor(capture);
	}
	else if (std::string(av[2]).compare("HSVRegion") == 0)
	{
		proc = new HSV_Region_Processor(capture);
	}
	else if (std::string(av[2]).compare("HSVRegionMinAlloc") == 0)
	{
		proc = new HSV_Region_Processor_Min_Alloc(capture);
	}
	else if (std::string(av[2]).compare("HoughCircleDetection") == 0)
	{
		proc = new HoughCircleDetection(capture);
	}
	else if (std::string(av[2]).compare("BasicShapeDetection") == 0)
	{
		proc = new BasicShapeDetection(capture);
	}

	proc->process(numFrames);
	proc->loadBenchmark(av[4]);
	proc->printReport(std::string(av[1]));
	delete(proc);
	return 0;
}
