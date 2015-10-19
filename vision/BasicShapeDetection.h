/*
 * BasicShapeDetection.h
 *
 *  Created on: 12 Sep 2015
 *      Author: cameron
 */

#ifndef VISION_BASICSHAPEDETECTION_H_
#define VISION_BASICSHAPEDETECTION_H_

#include "ImageProcessor.h"
#include <vector>

class BasicShapeDetection: public ImageProcessor {
	std::vector<std::vector<cv::Point> > squares;
public:
	BasicShapeDetection(cv::VideoCapture &capture);
	virtual ~BasicShapeDetection();

	std::vector<Region *>* processFrame(cv::Mat &frame);
	double anglePoint( cv::Point pt1, cv::Point pt2, cv::Point pt0 );
	Color getColor(cv::Mat &frame, int x, int y, int size);

	float maximum( float a, float b, float c );
	float minimum( float a, float b, float c );
	void RGBtoHSV( float r, float g, float b, float *h, float *s, float *v );
};

#endif /* VISION_BASICSHAPEDETECTION_H_ */
