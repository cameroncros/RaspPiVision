/*
 * DoublePair.h
 *
 *  Created on: 3 May 2015
 *      Author: cameron
 */

#ifndef DOUBLEPAIR_H_
#define DOUBLEPAIR_H_

class DoublePair {
	double x, y;
	double size;
public:
	DoublePair();
	DoublePair(double x, double y, double size);
	virtual ~DoublePair();
	double getX() const;
	double getY() const;
	double getSize() const;
	void setX(double x);
	void setY(double y);
	void setSize(double size);
	bool isNull() const;
	double compare(const DoublePair val) const;
};

#endif /* DOUBLEPAIR_H_ */
