/*
 * RGBProcessor.h
 *
 *  Created on: Apr 25, 2015
 *      Author: cameron
 */

#ifndef RGBPROCESSOR_H_
#define RGBPROCESSOR_H_

#include "ImageProcessor.h"

class RGBProcessor: public ImageProcessor {
public:
	RGBProcessor(cv::VideoCapture capture);
	virtual ~RGBProcessor();

	DoublePair processFrame(cv::Mat frame);
	bool isBlue(cv::Vec3b point);
};

#endif /* RGBPROCESSOR_H_ */
