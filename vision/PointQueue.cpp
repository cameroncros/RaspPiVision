/*
 * PointQueue.cpp
 *
 *  Created on: 15 Jul 2015
 *      Author: cameron
 */

#include "PointQueue.h"

#include <iostream>

PointQueue::PointQueue(int initSize) {
	maxSize = initSize;
	xArray = new int[initSize];
	yArray = new int[initSize];
	start = 0;
	end = 0;
	length = 0;
}

PointQueue::~PointQueue() {
	delete[] xArray;
	delete[] yArray;
	// TODO Auto-generated destructor stub
}

void PointQueue::append(int x, int y) {
	if (length == maxSize) {
		std::cout << "Array is full" << length << "-" << maxSize << std::endl;
		return;
	}
	xArray[end]=x;
	yArray[end]=y;
	end = (end+1)%maxSize;
	length++;
}

int PointQueue::getX() {
	return xArray[start];
}

int PointQueue::getY() {
	return yArray[start];
}

void PointQueue::pop() {
	if (length == 0) {
		std::cout << "Array is empty" << std::endl;
		return;
	}
	length--;
	start = (start+1)%maxSize;
}

int PointQueue::size() {
	return length;
}
