/*
 * HoughCircleDetection.h
 *
 *  Created on: 7 Sep 2015
 *      Author: cameron
 */

#ifndef VISION_HOUGHCIRCLEDETECTION_H_
#define VISION_HOUGHCIRCLEDETECTION_H_

#include "ImageProcessor.h"

class HoughCircleDetection: public ImageProcessor {
public:
	HoughCircleDetection(cv::VideoCapture &capture);
	virtual ~HoughCircleDetection();

	std::vector<Region *>*  processFrame(cv::Mat &frame);
	Color getColor(cv::Mat frame, int x, int y, int size);

	int maximum( int a, int b, int c );
	int minimum( int a, int b, int c );
	void RGBtoHSV( float r, float g, float b, float *h, float *s, float *v );
};

#endif /* VISION_HOUGHCIRCLEDETECTION_H_ */
