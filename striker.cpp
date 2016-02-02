#ifndef _STRIKER_CPP
#define _STRIKER_CPP

#include "striker.h"
#include "constants.h"

Striker::Striker() {
	this->angle = INITIAL_ANGLE;
	this->power = INITIAL_POWER;
	this->init(0.0f,-BOX_LEN/2+STRIKER_RAD+0.5f,0.0f,0.0f,STRIKER_RAD,STRIKER_MASS,3);
}

Striker::~Striker() {
}

void Striker::drawIndicator(){
	if(!this->isMoving){
		float power = this->power;
		int angle = this->angle;
		glPushMatrix();
		glColor3f(0.60f,0.60f,0.60f);
		glTranslatef(this->posX, this->posY, 0.0f);
		glBegin(GL_LINES);
		glVertex2f(0.0f, 0.0f);
		glVertex2f(power*cos(DEG2RAD(angle)),power*sin(DEG2RAD(angle)));
		glEnd();
		glPopMatrix();
	}
}

void Striker::changePosX(float x){
	if(this->posX+x<=BOX_LEN/2-OFFSET && this->posX+x>=-BOX_LEN/2+OFFSET )
		this->posX+=x;
}
void Striker::changePosX2(float x){
	if(x<=BOX_LEN/2-OFFSET && x>=-BOX_LEN/2+OFFSET )
		this->posX=x;
}

void Striker::reset(){
	this->posX=0;
	this->posY=-BOX_LEN/2+STRIKER_RAD+0.5f;
	this->velX=0;
	this->velY=0;
	this->power=0.6f;
	this->angle=90;
	this->isMoving=false;
}

void Striker::changePower(float power){
	if(this->power+power<=POWER_MAX && this->power + power > STRIKER_RAD)
		this->power+=power;
}

void Striker::changeAngle(float angle){
	if(this->angle+angle <= ANGLE_MAX && this->angle + angle >= ANGLE_MIN)
		this->angle+=angle;
}

void Striker::release(){
	if(this->moving()){
		this->velX=STRIKER_VEL*cos(DEG2RAD(this->angle))*this->power;
		this->velY=STRIKER_VEL*sin(DEG2RAD(this->angle))*this->power;
	}
}

void Striker::setPower(float power){
	if(power<=POWER_MAX &&  power > STRIKER_RAD){
		this->power=power;
	}
	else if(power>POWER_MAX){
		this->power=POWER_MAX;
	}
	else if(power<STRIKER_RAD){
		this->power=INITIAL_POWER;
	}
}
void Striker::setAngle(float angle){
	if(angle <= ANGLE_MAX &&  angle >= ANGLE_MIN){
		this->angle=angle;
	}
	else if(angle > ANGLE_MAX)
		this->angle=ANGLE_MAX;
	else if(angle < ANGLE_MIN)
		this->angle=ANGLE_MIN;
}


#endif