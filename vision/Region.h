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

class Region {

public:
	Region();
	Region(double x, double y, double size, Color color);
	virtual ~Region();
	double getX() const;
	double getY() const;
	double getSize() const;
	Color getColor() const;
	void setX(double x);
	void setY(double y);
	void setSize(double size);
	void setColor(Color color);
	double compare(const Region &val) const;


private:
	double x, y;
	double size;
	Color color;
};

#endif /* REGION_H_ */
