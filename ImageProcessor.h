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
	cv::VideoCapture capture;
public:
	ImageProcessor(cv::VideoCapture capture);
	virtual ~ImageProcessor();
	virtual void process(int numFrames)=0;
};

#endif /* IMAGEPROCESSOR_H_ */
