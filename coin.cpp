#ifndef _COIN_CPP
#define _COIN_CPP

#include "coin.h"
#include "constants.h"

Coin::Coin() {
	this->posX=0;
	this->posY=0;
	this->velX=0;
	this->velY=0;
	this->radius=0;
	this->mass=0;
	this->color=0;
	this->isMoving=false;
	this->wasMoving=false;
}
Coin::~Coin() {
}

void Coin::init(float posX,float posY,float velX,float velY,float radius,float mass,int color){
	this->posX=posX;
	this->posY=posY;
	this->velX=velX;
	this->velY=velY;
	this->radius=radius;
	this->mass=mass;
	this->color=color;
}

void Coin::drawCoin() {
	    glPushMatrix();
		glTranslatef(this->posX,this->posY,0.0f);	   
        glBegin(GL_TRIANGLE_FAN);
        for(int i=0 ; i<360 ; i++) {
            glVertex2f(this->radius * cos(DEG2RAD(i)), this->radius * sin(DEG2RAD(i)));
       }
       glEnd();
       glPopMatrix();
}

float Coin::getPosX(){
	return this->posX;
}

float Coin::getPosY(){
	return this->posY;
}

float Coin::getVelX(){
	return this->velX;
}

float Coin::getVelY(){
	return this->velY;
}

float Coin::getMass(){
	return this->mass;
}

float Coin::getColor(){
	return this->color;
}
bool Coin::getWasMoving(){
	return this->wasMoving;
}

float Coin::getRadius(){
	return this->radius;
}
void Coin::updatePosX(float X){
	this->posX=X;
}

void Coin::updatePosY(float Y){
	this->posY=Y;
}

void Coin::updateVelX(float X){
	this->velX=X;
}

void Coin::updateVelY(float Y){
	this->velY=Y;
}

bool Coin::moving(){
	return this->isMoving;
}

void Coin::startMoving(){
	this->isMoving=true;
}

void Coin::stopMoving(){
	this->isMoving=false;
}

void Coin::wMoving(){
	this->wasMoving=true;
}

void Coin::wNotMoving(){
	this->wasMoving=false;
}
#endif