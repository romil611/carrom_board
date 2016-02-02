#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include <stdio.h>
#include <ctime>
#include <string.h>

#define BALL_RAD 0.08f
#define COIN_RAD 0.1f
#define START_RAD COIN_NO*COIN_RAD/PI//0.295f
#define STRIKER_RAD 0.15f
#define POCKET_RAD 0.16f
#define CENTER_RAD 0.4f
#define BOX_LEN 4.0f
#define BOX_LEN2 4.4f 
#define BOX_LEN3 2.6f
#define OFFSET 0.6f
#define STRIKER_VEL 0.08f
#define POWER_MAX 1.5f
#define ANGLE_MAX 175
#define ANGLE_MIN 5
#define INITIAL_ANGLE 90
#define INITIAL_POWER 0.6f
#define THRESHOLD  0.000004f
#define FRICTION 0.996f
#define GAP1 0.5f
#define GAP2 GAP1+2*COIN_RAD+0.1f
#define GAP3 GAP2+2*COIN_RAD+0.1f
#define RESTITUTION1 0.970f
#define RESTITUTION2 0.90f
#define RESTITUTION3 0.94f
#define RESTITUTION4 0.99f
#define FRAMEDEVISION 1000.0f
#define REPEAT 1.0f
#define COIN_NO 9.0f
#define BROWN 0.733f,0.04f,0.0f
#define RED 1.0f,0.0f,0.0f
#define GREY 0.12f,0.12f,0.12f
#define CREAM 1.0f, 1.0f, 0.666f
#define CREAM2 0.80f, 0.80f, 0.566f
#define DARK_CREAM 0.811f, 0.811f, 0.5411f
#define BLUE 0.0f, 0.8f, 1.0f
#define STRIKER_COLOR 0.710f, 0.710f, 0.710f
#define COIN_COLOR1 0.4f, 0.35f, 0.83f
#define COIN_COLOR2 0.30f, 0.30f, 0.30f
#define TEXTCOLOR 0.54f,0.840f,0.260f
#define BLACK 0.0f,0.0f,0.0f
#define SCOREBOARD_FONT GLUT_BITMAP_TIMES_ROMAN_24
#define SCOREBOARD_POSITION 2.9f ,-0.8f ,0.0f
#define PI 3.141592653589
#define	ANGLE_FACTOR 3
#define POWER_FACTOR 0.1f
#define POSITION_FACTOR 0.1f
#define COIN_MASS 1.0f
#define STRIKER_MASS 2.0f
#define DEG2RAD(deg) (deg * PI / 180)
//0 means red , 1 means white ,2 means black, 3 means striker