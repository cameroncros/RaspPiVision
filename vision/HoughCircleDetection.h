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

	void processFrame(cv::Mat &frame, std::vector<Region *> &regionList);
};

#endif /* VISION_HOUGHCIRCLEDETECTION_H_ */
