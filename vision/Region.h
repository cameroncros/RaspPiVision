/*
 * Region.h
 *
 *  Created on: 3 May 2015
 *      Author: cameron
 */

#ifndef REGION_H_
#define REGION_H_

class Region {
	double x, y;
	double size;
public:
	Region();
	Region(double x, double y, double size);
	virtual ~Region();
	double getX() const;
	double getY() const;
	double getSize() const;
	void setX(double x);
	void setY(double y);
	void setSize(double size);
	bool isNull() const;
	double compare(const Region val) const;
};

#endif /* REGION_H_ */
