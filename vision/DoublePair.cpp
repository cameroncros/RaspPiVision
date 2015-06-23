/*
 * DoublePair.cpp
 *
 *  Created on: 3 May 2015
 *      Author: cameron
 */

#include "DoublePair.h"
#include <math.h>

DoublePair::DoublePair() {
	this->x = -1;
	this->y = -1;
}

DoublePair::DoublePair(double x, double y, double size) {
	this->x = x;
	this->y = y;
	this->size = size;
}

DoublePair::~DoublePair() {
}

double DoublePair::getX() const
{
	return x;
}
double DoublePair::getY() const
{
	return y;
}


void DoublePair::setX(double x)
{
	this->x=x;
}
void DoublePair::setY(double y)
{
	this->y=y;
}

bool DoublePair::isNull() const
{
	if (x == -1 && y == -1) {
		return true;
	}
	return false;
}

double DoublePair::compare(const DoublePair val) const
{
	if (this->isNull() && val.isNull()) {
		return 0;
	}
	double xdiff = x-val.getX();
	double ydiff = y-val.getY();
	return sqrt(xdiff*xdiff + ydiff*ydiff);
}

double DoublePair::getSize() const {
	return size;
}

void DoublePair::setSize(double size) {
	this->size = size;
}
