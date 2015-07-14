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
#include "RegionQueue.h"
#include "Region.h"

class HSV_Region_Processor_Min_Alloc: public HSV_Region_Processor {
	PointQueue *pointList;
	RegionQueue *regionList;
public:
	HSV_Region_Processor_Min_Alloc(cv::VideoCapture &capture);
	virtual ~HSV_Region_Processor_Min_Alloc();
	Region *processFrame(cv::Mat &frame);
private:
	void findRegion(cv::Mat &frame, int i, int j, double &regX, double &regY, double &regSize);

};

#endif /* VISION_HSVREGIONPROCESSORMINALLOC_H_ */
