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
	this->size = -1;
	this->color = UNKNOWN;
	this->shape = BLOB;
}

Region::Region(double x, double y, double size, Color color, Shape shape) {
	this->x = x;
	this->y = y;
	this->size = size;
	this->color = color;
	this->shape = shape;
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

Shape Region::getShape() const {
	return shape;
}

void Region::setShape(Shape shape) {
	this->shape = shape;
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

void Region::setColor(Color color) {
	this->color = color;
}



Color Region::getColor() const {
	return color;
}
