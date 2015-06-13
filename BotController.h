/*
 * BotController.h
 *
 *  Created on: 13 Jun 2015
 *      Author: cameron
 */

#ifndef BOTCONTROLLER_H_
#define BOTCONTROLLER_H_

class BotController {
public:
	BotController();
	virtual ~BotController();

	void move(double direction, double speed);
	double motorPower(int motorId, double direction);
	void spin(double angle);

};

#endif /* BOTCONTROLLER_H_ */
