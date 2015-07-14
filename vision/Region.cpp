/*
 * DoublePair.cpp
 *
 *  Created on: 3 May 2015
 *      Author: cameron
 */

#include "Region.h"

#include <cmath>
#include <cstddef>


Region::Region() {
	this->x = -1;
	this->y = -1;
}

Region::Region(double x, double y, double size) {
	this->x = x;
	this->y = y;
	this->size = size;
}

Region::~Region() {
}

double Region::getX() const
{
	return x;
}
double Region::getY() const
{
	return y;
}


void Region::setX(double x)
{
	this->x=x;
}
void Region::setY(double y)
{
	this->y=y;
}

double Region::compare(const Region &val) const
{
	if (&val == NULL) {
		return 0;
	}
	double xdiff = x-val.getX();
	double ydiff = y-val.getY();
	return sqrt(xdiff*xdiff + ydiff*ydiff);
}

double Region::getSize() const {
 	return size;
}

void Region::setSize(double size) {
	this->size = size;
}
