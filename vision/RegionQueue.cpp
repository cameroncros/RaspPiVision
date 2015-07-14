/*
 * RegionQueue.cpp
 *
 *  Created on: 15 Jul 2015
 *      Author: cameron
 */

#include "RegionQueue.h"
#include "Region.h"
#include <iostream>


RegionQueue::RegionQueue(int initSize) {
	maxSize = initSize;
	xArray = new double[initSize];
	yArray = new double[initSize];
	sizeArray = new double[initSize];
	start = 0;
	end = 0;
	length = 0;
}

RegionQueue::~RegionQueue() {
	delete[] xArray;
	delete[] yArray;
	delete[] sizeArray;
	// TODO Auto-generated destructor stub
}

void RegionQueue::append(double x, double y, double size) {
	if (length == maxSize) {
		std::cout << "Array is full" << length << "-" << maxSize << std::endl;
		return;
	}
	xArray[end]=x;
	yArray[end]=y;
	sizeArray[end]=size;
	end = (end+1)%maxSize;
	length++;
}

double RegionQueue::getX() {
	return xArray[start];
}

double RegionQueue::getY() {
	return yArray[start];
}

double RegionQueue::getSize() {
	return sizeArray[start];
}

void RegionQueue::pop() {
	if (length == 0) {
		std::cout << "Array is empty" << std::endl;
		return;
	}
	length--;
	start = (start+1)%maxSize;
}

int RegionQueue::size() {
	return length;
}

void RegionQueue::reset() {
	start = 0;
	end = 0;
	length = 0;
}

Region* RegionQueue::findLargest() {
	int found=-1, largest = 0;
	int i = start;
	while (i != end) {
		if (sizeArray[i] > largest) {
			found = i;
			largest = sizeArray[i];
		}
		i=(i+1)%maxSize;
	}
	if (found == -1) {
		return NULL;
	} else {
		return new Region(xArray[found], yArray[found], sizeArray[found]);
	}
}
