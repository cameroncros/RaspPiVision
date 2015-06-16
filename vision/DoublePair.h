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
public:
	DoublePair();
	DoublePair(double x, double y);
	virtual ~DoublePair();
	double getX() const;
	double getY() const;
	void setX(double x);
	void setY(double y);
	bool isNull() const;
	double compare(const DoublePair val) const;
};

#endif /* DOUBLEPAIR_H_ */
