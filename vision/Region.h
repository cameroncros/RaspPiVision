/*
 * Region.h
 *
 *  Created on: 3 May 2015
 *      Author: cameron
 */

#ifndef REGION_H_
#define REGION_H_

#include "ImageProcessor.h"

typedef enum {
	BLUE=0,
	GREEN=1,
	RED=2,
	BLACK=3,
	WHITE=4,
	UNKNOWN
} Color;

typedef enum {
	SQUARE,
	CIRCLE,
	TRIANGLE,
	BLOB
} Shape;

class Region {

public:
	Region();
	Region(double x, double y, double size, Color color, Shape shape);
	virtual ~Region();
	double getX() const;
	double getY() const;
	double getSize() const;
	Color getColor() const;
	Shape getShape() const;
	void setX(double x);
	void setY(double y);
	void setSize(double size);
	void setColor(Color color);
	void setShape(Shape shape);
	double compare(const Region &val) const;


private:
	double x, y;
	double size;
	Color color;
	Shape shape;
};

#endif /* REGION_H_ */
