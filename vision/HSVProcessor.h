/*
 * HSVProcessor.h
 *
 *  Created on: Apr 25, 2015
 *      Author: cameron
 */

#ifndef HSVPROCESSOR_H_
#define HSVPROCESSOR_H_

#include "ImageProcessor.h"

class HSVProcessor: public ImageProcessor {
public:
	HSVProcessor(cv::VideoCapture capture);
	virtual ~HSVProcessor();

	Region processFrame(cv::Mat frame);
	bool isBlue(cv::Vec3b point);
};

#endif /* HSVPROCESSOR_H_ */
