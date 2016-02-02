#ifndef _COIN_H
#define _COIN_H
#include "constants.h"

class Coin {
	public:
		float posX,posY;
		float velX,velY;
		float radius;
		int color;
		float mass;
		bool isMoving;
		bool wasMoving;

		Coin();
		~Coin();

		void init(float,float,float,float,float,float,int);
		float getPosX();
		float getPosY();
		float getVelX();
		float getVelY();
		float getMass();
		float getColor();
		float getRadius();
		bool getWasMoving();
		void updateVelX(float);
		void updateVelY(float);
		void updatePosX(float);
		void updatePosY(float);
		
		void drawCoin();
		bool moving();
		void stopMoving();
		void startMoving();
		void wMoving();
		void wNotMoving();

};

#endif