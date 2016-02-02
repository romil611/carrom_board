#ifndef _Board_CPP
#define _Board_CPP

#include "board.h"
#include "constants.h"
#include "coin.h"
#include "striker.h"

Board::Board(){
	this->posX=0;
	this->posY=0;
	this->score=30;
	this->coinsPocketed=0;
	this->required=0;
}

Board::~Board(){
}

void Board::init(float posX,float posY) {
	this->posX=posX;
	this->posY=posY;
	this->score=30;
	this->striker = Striker();
	this->coinsPocketed=0;
	this->required=0;
	this->win=false;
	this->gameEnded=false;
	for(int i = 0;i< COIN_NO; i++) {
		this->coin[i] = Coin();
	}
	this->coin[0].init(0.0f,0.0f,0.0f,0.0f,COIN_RAD,COIN_MASS,0);
	int j=1;
	for(int i=22;i<385;i+=(360/(COIN_NO-1))){
		this->coin[j].init(START_RAD*cos(DEG2RAD(i)), START_RAD* sin(DEG2RAD(i)),0.0f,0.0f,COIN_RAD,COIN_MASS,j%2+1);
		j++;
	}
	time_t t;
	t=time(NULL);
	this->currentTime=t;
	this->startTime=t;
	this->pauseTime=t;
	this->previousTime=t;
}

void Board::drawBoard(){
	glColor3f(GREY);
	this->drawBox(BOX_LEN2,BOX_LEN2);              //outer line of board
	glColor3f(CREAM);					  //inner line of board
	this->drawBox(BOX_LEN,BOX_LEN);				  
	glColor3f(BROWN);
	this->drawLines(BOX_LEN);			  //inner lines
	this->drawCircles(CENTER_RAD);		  //design central circle
	float x=BOX_LEN/2 - 0.588f;
	float y=BOX_LEN/2 - 0.588f;
	for(int i =0;i<4;i++){
		glPushMatrix();
		if(i%2==1)
			x=-1*x;
		y=-y;
		glTranslatef(x,y, 0.0f);
		this->drawCircles(BALL_RAD);	  //end line circle
		glPopMatrix();
	}
	glColor3f(BROWN);
	x=BOX_LEN/2 - 0.16f;
	y=BOX_LEN/2 - 0.16f;
	for(int i =0;i<4;i++){
		glPushMatrix();
		if(i%2==1)
			x=-1*x;
		y=-1*y;
		glTranslatef(x,y, 0.0f);
		glColor3f(CREAM2);
		this->drawBall(POCKET_RAD);   //pockets
		glPopMatrix();
	}

	glColor3f(STRIKER_COLOR);
	this->striker.drawCoin();       //striker
	this->striker.drawIndicator();

	glColor3f(RED);
	this->coin[0].drawCoin();       //central red coin
	this->drawCoins();				//rest of the coins
	this->drawScoreboard();	
	if(getGameEnded()){
		glColor3f(BLACK);
		this->drawBox(BOX_LEN3+0.3f,BOX_LEN3-0.3f);
		if(this->win)
			this->writeOnBoard(-BOX_LEN3/2+0.0001f,0.0f,0.0f,"Game Over : You Win :)",1.0f,1.0f,1.0f);
		else if(!this->win)
			this->writeOnBoard(-BOX_LEN3/2+0.0001f,0.0f,0.0f,"Game Over : You Lose :(",1.0f,1.0f,1.0f); 
		this->writeOnBoard(-BOX_LEN3/3,-0.22f,0.0f,"Play Again? \n y / n",1.0f,1.0f,1.0f);	
	}
}

void Board::drawCoins(){
	int j=1;
	for(int i=22;i<385;i+=(360/(COIN_NO-1))){
		glPushMatrix();
		if(j%2==0)
			glColor3f(COIN_COLOR1);
		if(j%2==1)
			glColor3f(COIN_COLOR2);
		this->coin[j].drawCoin();
		j++;
		glPopMatrix();
	}
}

void Board::drawBox(float len,float len2) {

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
	glVertex2f(-len / 2, -len2 / 2);
	glVertex2f(len / 2, -len2 / 2);
	glVertex2f(len / 2, len2 / 2);
	glVertex2f(-len / 2, len2 / 2);
	glEnd();
        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Board::drawLines(float len) {

	glBegin(GL_LINES);
	glVertex2f(-len / 2+OFFSET, -len / 2+(OFFSET-0.1f));
	glVertex2f(len / 2-OFFSET, -len / 2+(OFFSET-0.1f));
	glVertex2f(len / 2-OFFSET, len / 2-(OFFSET-0.1f));
	glVertex2f(-len / 2+OFFSET, len / 2-(OFFSET-0.1f));
	glVertex2f(-len / 2+(OFFSET-0.1f), -len / 2+OFFSET);
	glVertex2f(-len / 2+(OFFSET-0.1f), len / 2-OFFSET);
	glVertex2f(len / 2-(OFFSET-0.1f), len / 2-OFFSET);
	glVertex2f(len / 2-(OFFSET-0.1f), -len / 2+OFFSET);
/*	glVertex2f(-len / 2+0.65f, -len / 2+0.65f);
	glVertex2f(len / 2-0.65f, -len / 2+0.65f);
	glVertex2f(len / 2-0.65f, len / 2-0.65f);
	glVertex2f(-len / 2+0.65f, len / 2-0.65f);
	glVertex2f(-len / 2+0.65f, -len / 2+0.65f);
	glVertex2f(-len / 2+0.65f, len / 2-0.65f);
	glVertex2f(len / 2-0.65f, len / 2-0.65f);
	glVertex2f(len / 2-0.65f, -len / 2+0.65f);
*/	glVertex2f(-len / 2+0.4f, -len / 2+0.4f);
	glVertex2f(-len / 2+1.2f, -len / 2+1.2f);
	glVertex2f(len / 2-0.4f, len / 2-0.4f);
	glVertex2f(len / 2-1.2f, len / 2-1.2f);
	glVertex2f(-len / 2+0.4f, len / 2-0.4f);
	glVertex2f(-len / 2+1.2f, len / 2-1.2f);
	glVertex2f(len / 2-1.2f, -len / 2+1.2f);
	glVertex2f(len / 2-0.4f, -len / 2+0.4f);
	glVertex2f(2*BOX_LEN2/3-0.3f, -0.3f);
	glVertex2f(2*BOX_LEN2/3+2*COIN_RAD*2+0.9f, -0.3f);
	

	glEnd();
        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Board::drawCircles(float r) {
	static const double inc = PI / 48;
	static const double max = 2 * PI;
	glBegin(GL_LINE_LOOP);
	for(double d = 0; d < max; d += inc) {
		glVertex2f(cos(d) * r , sin(d) * r );
	}
	glEnd();
}

void Board::drawBall(float rad) {

	glBegin(GL_TRIANGLE_FAN);
	for(int i=0 ; i<360 ; i++) 
		glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
	glEnd();
}

template <typename X> void Board::checkWallCollision(X &coin,int a){
float restitution ;
if(a==1)
	restitution = RESTITUTION3;
else 
	restitution = RESTITUTION4;
if(coin.getPosX() + coin.getRadius() > BOX_LEN/2) 
	coin.updateVelX(-1*fabs(coin.getVelX())*restitution);	

if(coin.getPosX() - coin.getRadius() < -1*BOX_LEN/2) 
	coin.updateVelX(fabs(coin.getVelX())*restitution);

if(coin.getPosY() + coin.getRadius() > BOX_LEN/2) 
	coin.updateVelY(-1*fabs(coin.getVelY())*restitution);

if(coin.getPosY() - coin.getRadius() < -1*BOX_LEN/2)    
	coin.updateVelY(fabs(coin.getVelY())*restitution);
}
void Board::checkCollision(){
	float sx,sy,rs,theta;
	
	sx=this->striker.getPosX();
	sy=this->striker.getPosY();
	rs=this->striker.getRadius();

	for(int i=0;i<COIN_NO;i++) {
		float ax,bx;
		float ay,by;
		float ra,rb;
		float u,v;

		ax=this->coin[i].getPosX();
		ay=this->coin[i].getPosY();
		ra=this->coin[i].getRadius();

		if(sx == ax)
			theta = PI/2;
		else
			theta =atan((sy-ay) /(sx-ax ));
		
		u=this->striker.getVelX()*cos(theta)+this->striker.getVelY()*sin(theta);
		v=this->coin[i].getVelX()*cos(theta)+this->coin[i].getVelY()*sin(theta);
		float dis1=sqrt(pow(sx-ax,2)+pow(sy-ay,2));

		if(dis1<=rs+ra && vectorsApproachEachOther(sx-ax,sy-ay,u-v)) {
			//PlaySound("./sound1.mp3", NULL, SND_FILENAME);
			this->handleCollision(this->coin[i],this->striker,1);
		}

		for(int j=0;j<COIN_NO;j++) {
			if(i==j)
				continue;
			bx=this->coin[j].getPosX();
			by=this->coin[j].getPosY();
			rb=this->coin[j].getRadius();

			if(bx == ax)
				theta = PI/2;
			else
				theta =atan((ay-by) /(ax-bx));
			
			u=this->coin[j].getVelX()*cos(theta)+this->coin[j].getVelY()*sin(theta);
			dis1=sqrt(pow(ax-bx,2)+pow(ay-by,2));
			if(dis1<=ra+rb && vectorsApproachEachOther(ax-bx,ay-by,v-u)){
				//PlaySound("./sound2.mp3", NULL, SND_ASYNC|SND_FILENAME);
				this->handleCollision(this->coin[i],this->coin[j],2);
			}
		}
	}
}

void Board::handleCollision(Coin &coin1,Coin &coin2,int a){
	float theta;
	float u,v;
	float up,vp;
	float u2,v2;
	float m1,m2;
	float RESTITUTION;
	if(a==1)
		RESTITUTION=RESTITUTION1;
	else
		RESTITUTION=RESTITUTION2;

	//system("canberra-gtk-play -f ./sound3.wav");
	theta = atan( (coin2.getPosY()- coin1.getPosY()) / (coin2.getPosX()-coin1.getPosX()) );

	u=coin1.getVelX()*cos(theta)+coin1.getVelY()*sin(theta);
	v=coin2.getVelX()*cos(theta)+coin2.getVelY()*sin(theta);

	up=-1*coin1.getVelX()*sin(theta)+coin1.getVelY()*cos(theta);
	vp=-1*coin2.getVelX()*sin(theta)+coin2.getVelY()*cos(theta);

	m1=coin1.getMass();
	m2=coin2.getMass();

	u2=((m1-(RESTITUTION*m2))*u + (RESTITUTION+1)*m2*v)/(m1+m2);
	v2=((m2-(RESTITUTION*m1))*v + (RESTITUTION+1)*m1*u)/(m1+m2);

	coin1.updateVelX(u2*cos(theta)-up*sin(theta));
	coin1.updateVelY(u2*sin(theta)+up*cos(theta));
	coin2.updateVelX(v2*cos(theta)-vp*sin(theta));
	coin2.updateVelY(v2*sin(theta)+vp*cos(theta));
}

template <typename X> void Board::checkIfStopped(X &coin){
if(pow(fabs(coin.getVelX()),2) +pow(fabs(coin.getVelY()),2)<= THRESHOLD) {
	coin.updateVelX(0);
	coin.updateVelY(0);
	if(coin.moving()) 
		coin.wMoving();
	else 
		coin.wNotMoving();
	coin.stopMoving();
}
else 
	coin.startMoving();
}

bool Board::vectorsApproachEachOther(float bx, float by, float v) {
	if(bx == 0 and by == 0 ) 
		return true;
	else if(bx >= 0 and by >= 0) 
		return v < 0;
	else if (bx <= 0 and by >= 0) 
		return v > 0;
	else if(bx <= 0 and by <= 0) 
		return v > 0;
	else if (bx >= 0 and by <= 0)
		return v < 0;
	return true;
}

void Board::update(){
	float x=this->striker.getVelX();
	float y=this->striker.getVelY();
	float theta=atan2(y,x);
	float u=(sqrt(x*x + y*y))*FRICTION/REPEAT;
	float x2=u*cos(theta);
	float y2=u*sin(theta);
	this->striker.updateVelX(x2);
	this->striker.updateVelY(y2);

	this->striker.updatePosX( this->striker.getPosX() + (this->striker.getVelX()/REPEAT) );
	this->striker.updatePosY( this->striker.getPosY() + (this->striker.getVelY()/REPEAT) );
	
	for(int i=0;i<COIN_NO;i++){
		x=this->coin[i].getVelX();
		y=this->coin[i].getVelY();
		theta=atan2(y,x);
		u=(sqrt(x*x + y*y))*FRICTION/REPEAT;
		x2=u*cos(theta);
		y2=u*sin(theta);
		this->coin[i].updateVelX( x2 );
		this->coin[i].updateVelY( y2 );

		this->coin[i].updatePosX( this->coin[i].getPosX() + (this->coin[i].getVelX()/REPEAT) );
		this->coin[i].updatePosY( this->coin[i].getPosY() + (this->coin[i].getVelY()/REPEAT) );
	}

}

float Board::distence(float a,float b,float c,float d){
	return sqrt(pow(a-b,2)+pow(c-d,2));
}

void Board::checkIfPocketed(){
	float x=BOX_LEN/2 - 0.16f;
	float y=BOX_LEN/2 - 0.16f;
	for(int j=0;j<4;j++){
		if(j%2==1)
			x*=-1;
		y*=-1;
		float x1,y1;
		x1=this->striker.getPosX();
		y1=this->striker.getPosY();
		if(distence(x1,x,y1,y)<POCKET_RAD){
			this->striker.reset();
			this->score+=-5;
		}
		for(int i=0;i<COIN_NO;i++){
			x1=this->coin[i].getPosX();
			y1=this->coin[i].getPosY();
			if(distence(x1,x,y1,y)<POCKET_RAD){
				if(this->coin[i].getColor()==1){
					this->coin[i].updatePosX(2*BOX_LEN2/3+0.1f);
					this->score+=10;
					this->required++;
				}
				else if(this->coin[i].getColor()==0){
					this->coin[i].updatePosX(2*BOX_LEN2/3+2*COIN_RAD+0.3f);
					this->score+=50;
					this->required++;
				}
				else if(this->coin[i].getColor()==2){
					this->coin[i].updatePosX(2*BOX_LEN2/3+2*COIN_RAD*2+0.5f);
					this->score+=-5;
				}
				this->coin[i].updatePosY(coinsPocketed*COIN_RAD*2);
				this->coin[i].updateVelX(0);
				this->coin[i].updateVelY(0);
				this->coinsPocketed++;
				//printf("required %d coinsPocketed %d\n",required,coinsPocketed);
				if(required>=(int)COIN_NO/2+1){
					updateGameEnded(true,true);
					this->striker.updateVelX(0);
					this->striker.updateVelY(0);
				}
			}
		}
	}
}

void Board::updateScore(){	
	if(this->score>0 && this->required<(int)COIN_NO/2+1){
		float var;
		//if(this->striker.moving() || this->striker.getWasMoving())
		//	var= (this->getCTime())-(this->getPTime() - this->getSTime()) - (this->getPrTime());
		//else
			var=(this->getCTime()) - (this->getPrTime());
		if( var >1.0f){
			this->score+=-1;
			updatePrTime(this->currentTime);
		}
	}
	else if(this->score<=0){
		updateGameEnded(true,false);
		this->striker.updateVelX(0);
		this->striker.updateVelY(0);
		for(int i=0;i<COIN_NO;i++){
			this->coin[i].updateVelX(0);
			this->coin[i].updateVelY(0);
		}

	}
}

void Board::writeOnBoard(float x, float y, float z,std::string s, float r, float g, float b) {
	int len, i;
	glPushMatrix();
	glColor3f(r,g,b);
	glRasterPos3f(x,y,z);
	len = s.size();
	const char *ss = s.c_str();
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(SCOREBOARD_FONT, ss[i]);
	}
	glPopMatrix();
}

void Board::drawScoreboard() {
	std::string st = std::to_string(this->score);
	st = "Score : " + st;
	this->writeOnBoard(SCOREBOARD_POSITION, st,TEXTCOLOR);
}



bool Board::getGameEnded(){
	return this->gameEnded;
}

bool Board::getGameWinned(){
	return this->win;
}

void Board::updateGameEnded(bool status,bool status2){
	this->gameEnded=status;
	this->win=status2;
}

time_t Board::getCTime(){
	time_t t;
	time(&t);
	this->updateCTime(t);
	return this->currentTime;
}

time_t Board::getSTime(){
	return this->startTime;
}

time_t Board::getPTime(){
	if(this->striker.moving()){
		time_t t;
		time(&t);
		updatePTime(t);
		return this->pauseTime;
	}
	else
		return this->pauseTime;
}

time_t Board::getPrTime(){
	return this->previousTime;
}

void Board::updateCTime(time_t t){
	this->currentTime=t;
}

void Board::updateSTime(time_t t){
	this->startTime=t;
}

void Board::updatePTime(time_t t){
	this->pauseTime=t;
}

void Board::updatePrTime(time_t t){
	this->previousTime=t;
}


#endif