/*
 * ImageProcessor.h
 *
 *  Created on: Apr 25, 2015
 *      Author: cameron
 */

#ifndef IMAGEPROCESSOR_H_
#define IMAGEPROCESSOR_H_

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#define BLUE 0
#define GREEN 1
#define RED 2

void onMouse(int event, int x, int y, int, void*);

class ImageProcessor {
protected:
	cv::VideoCapture capture;\
	int n = 0;
	char filename[200];
	std::string window_name = "video | q or esc to quit";
public:
	ImageProcessor(cv::VideoCapture capture);
	virtual ~ImageProcessor();
	virtual void process(int numFrames)=0;
	void printCentre(int line, int x, int y);
	void drawArrow(cv::Mat frame, double angle, double dist);
	void drawFrame(cv::Mat frame, double angle, double dist);
	void processKeys(cv::Mat frame);
	void initialiseWindow();
};

#endif /* IMAGEPROCESSOR_H_ */
