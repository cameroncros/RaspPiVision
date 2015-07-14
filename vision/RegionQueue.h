/*
 * RegionQueue.h
 *
 *  Created on: 15 Jul 2015
 *      Author: cameron
 */

#ifndef VISION_RegionQueue_H_
#define VISION_RegionQueue_H_

#include "Region.h"

class RegionQueue {
private:
	double *xArray;
	double *yArray;
	double *sizeArray;
	int maxSize;
	int start, end;
	int length;

public:
	RegionQueue(int initSize);
	virtual ~RegionQueue();

	void reset();

	void append(double x, double y, double size);
	double getX();
	double getY();
	double getSize();
	void pop();
	int size();
	Region *findLargest();
};

#endif /* VISION_RegionQueue_H_ */
