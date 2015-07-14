/*
 * HSVRegionProcessor.h
 *
 *  Created on: 8 Jul 2015
 *      Author: cameron
 */

#ifndef HSVREGIONPROCESSOR_H_
#define HSVREGIONPROCESSOR_H_

#include "HSVProcessor.h"

class HSV_Region_Processor: public HSVProcessor {
public:
	HSV_Region_Processor(cv::VideoCapture &capture);
	virtual ~HSV_Region_Processor();

	Region *processFrame(cv::Mat &frame);

private:
	Region *findRegion(cv::Mat &frame, int i, int j);
};

#endif /* HSVREGIONPROCESSOR_H_ */
