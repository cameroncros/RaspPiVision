/*
 * PointQueue.h
 *
 *  Created on: 15 Jul 2015
 *      Author: cameron
 */

#ifndef VISION_POINTQUEUE_H_
#define VISION_POINTQUEUE_H_

class PointQueue {
private:
	int *xArray;
	int *yArray;
	int maxSize;
	int start, end;
	int length;

public:
	PointQueue(int initSize);
	virtual ~PointQueue();

	void append(int x, int y);
	int getX();
	int getY();
	void pop();
	int size();
};

#endif /* VISION_POINTQUEUE_H_ */
