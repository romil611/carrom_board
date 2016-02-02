#ifndef _STRIKER_H
#define _STRIKER_H

#include "coin.h"
#include "constants.h"

class Striker :public Coin {
	public:
		float angle;
		float power;
		Striker();
		~Striker();

		void reset();
		void changePower(float);
		void changeAngle(float);
		void setPower(float);
		void setAngle(float);
		void changePosX(float);
		void drawIndicator();
		void release();
		void changePosX2(float x);

};

#endif