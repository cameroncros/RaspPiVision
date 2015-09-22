/*
 * HSVRegionProcessorMinAlloc.h
 *
 *  Created on: 15 Jul 2015
 *      Author: cameron
 */

#ifndef VISION_HSVREGIONPROCESSORMINALLOC_H_
#define VISION_HSVREGIONPROCESSORMINALLOC_H_

#include "HSVRegionProcessor.h"

#include "PointQueue.h"
#include "Region.h"

class HSV_Region_Processor_Min_Alloc: public HSV_Region_Processor {
	PointQueue *pointList;
public:
	HSV_Region_Processor_Min_Alloc(cv::VideoCapture &capture);
	virtual ~HSV_Region_Processor_Min_Alloc();
	void processFrame(cv::Mat &frame, std::vector<Region *> &regionList);
private:
	void findRegion(cv::Mat &frame, int i, int j, double &regX, double &regY, double &regSize);

};

#endif /* VISION_HSVREGIONPROCESSORMINALLOC_H_ */
