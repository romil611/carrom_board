#include "constants.h"
#include "coin.cpp"
#include "striker.cpp"
#include "board.cpp"

void drawScene();
void update(int value);
void initRendering();
void handleResize(int w, int h);
void handleKeypress1(unsigned char key, int x, int y);
void handleKeypress2(int key, int x, int y);
void handleMouseclick(int button, int state, int x, int y);
void dragHandler(int x, int y) ;

Board board;
int a=1;
bool moveStriker=false;
bool releaseStriker=true;
int main(int argc, char **argv) {

    // Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	int w = glutGet(GLUT_SCREEN_WIDTH);
	int h = glutGet(GLUT_SCREEN_HEIGHT);
	float windowWidth = w * 9 / 11;
	float windowHeight = h * 9 / 11;

	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition((w - windowWidth) / 2, (h - windowHeight) / 2);

    glutCreateWindow("Carrom Board");  // Setup the window
    initRendering(); 

    // Register callbacks
    glutDisplayFunc(drawScene);
    glutIdleFunc(drawScene);
    glutKeyboardFunc(handleKeypress1);
    glutSpecialFunc(handleKeypress2);
    glutMouseFunc(handleMouseclick);
    glutMotionFunc(dragHandler);
    glutReshapeFunc(handleResize);
    glutTimerFunc(10, update, 0);
    board = Board();
    board.init(0.0f,0.0f); 
    glutMainLoop();
    return 0;
}

void drawScene() {          // Function to draw objects on the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -8.0f);
	board.drawBoard();
	if(a==1){
		board.score=30;
		board.coinsPocketed=0; 
		board.required=0; 
		time_t t;
		t=time(NULL);
		board.currentTime=t;
		board.startTime=t;
		board.pauseTime=t;
		board.previousTime=t;   
		board.win=false;
		board.gameEnded=false;   
		a=0;
	}
	glPopMatrix();
	glutSwapBuffers();
}

// Function to handle all calculations in the scene
// updated evry 10 milliseconds
void update(int value) {	
	board.checkWallCollision(board.striker,1);
	for(int i=0;i<COIN_NO;i++){
		board.checkWallCollision(board.coin[i],2);
	}
	board.checkCollision();
	board.update();
	board.updateScore();
	board.checkIfPocketed();
	board.checkIfStopped(board.striker);
	for(int i=0;i<COIN_NO;i++)
		board.checkIfStopped(board.coin[i]);
	if(board.striker.wasMoving){
		board.striker.reset();
	}
	glutTimerFunc(10, update, 0);
}

// Initializing some openGL 3D rendering options
void fastForward(){
	for(int j=0;j<FRAMEDEVISION;j++){	
		board.checkWallCollision(board.striker,1);
		for(int i=0;i<COIN_NO;i++){
			board.checkWallCollision(board.coin[i],2);
		}
		board.checkCollision();
		board.update();
		board.updateScore();
		board.checkIfPocketed();
		board.checkIfStopped(board.striker);
		for(int i=0;i<COIN_NO;i++)
			board.checkIfStopped(board.coin[i]);
		if(board.striker.wasMoving){
			time_t t;
			time(&t);
			board.updateSTime(t);
			board.striker.reset();
		}
	}
}

void initRendering() {

    glEnable(GL_DEPTH_TEST);        // Enable objects to be drawn ahead/behind one another
    glEnable(GL_COLOR_MATERIAL);    // Enable coloring
    glClearColor(0.40f, 0.40f, 0.40f, 1.0f);   // Setting a background color
    glEnable(GL_LINE_SMOOTH);
}

// Function called when the window is resized
void handleResize(int w, int h) {

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)w / (float)h, 0.1f, 200.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void handleKeypress1(unsigned char key, int x, int y) {
	if(!board.getGameEnded()){
		if(!board.striker.moving()){
			if(key == 'a' || key == 'A')
				board.striker.changeAngle(ANGLE_FACTOR);
			if(key == 'c' || key =='C')
				board.striker.changeAngle(-1*ANGLE_FACTOR);
			if(key == ' '){           
				board.striker.startMoving();
				time_t t;
				t=time(NULL);
				board.updateSTime(t);
				board.striker.release();
			}
		}
		if (key == 'r' || key == 'R'){
			fastForward();
			board.striker.reset();
		}
	}
	else{
		if(key == 'n' || key== 'N')
			exit(0);
		if(key=='y' || key=='Y'|| key == 13){
			board.init(0.0f,0.0f);
			a=1;
		}
	}
	if (key == 27)
        exit(0);     // escape key is pressed
}

void handleKeypress2(int key, int x, int y) {
	if(!board.getGameEnded()){
		if(!board.striker.moving()){
			if (key == GLUT_KEY_LEFT)
				board.striker.changePosX(-1*POSITION_FACTOR);
			if (key == GLUT_KEY_RIGHT)
				board.striker.changePosX(POSITION_FACTOR);
			if (key == GLUT_KEY_UP)
				board.striker.changePower(POWER_FACTOR);
			if (key == GLUT_KEY_DOWN)
				board.striker.changePower(-1*POWER_FACTOR);
		}
	}
}

void handleMouseclick(int button, int state, int x, int y) {
	if(!board.getGameEnded()){
		if(!board.striker.moving()){
			x-=560;
			y-=315;
			float fac_x;
			float x1;
			fac_x = (BOX_LEN/2)/190;
			x1 = x*fac_x;
			if(button == GLUT_RIGHT_BUTTON && state==GLUT_DOWN){
				moveStriker=true;
			}
			if(button==GLUT_RIGHT_BUTTON && state==GLUT_UP){
				moveStriker=false;
			}
			if(button==GLUT_RIGHT_BUTTON){
				board.striker.changePosX2(x1);
			}

			if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
				releaseStriker=true;
			}
			if(button==GLUT_LEFT_BUTTON && state==GLUT_UP){
				releaseStriker=false;
				board.striker.startMoving();
				time_t t;
				t=time(NULL);
				board.updateSTime(t);
				board.striker.release();

			}
		}
	}
}
void dragHandler(int x, int y) {
	if(!board.getGameEnded()){
		if(!board.striker.moving()){
			x-=560;
			y-=315;
			float fac_x,fac_y;
			float x1,y1;
			float xs,ys;

			fac_x = (BOX_LEN/2)/190;
			fac_y = (BOX_LEN/2)/190;
			x1 = x*fac_x;
			y1 = -1*y*fac_y;
			xs=board.striker.getPosX();
			ys=board.striker.getPosY();
			if(moveStriker) {
				board.striker.changePosX2(x1);	
				moveStriker=true;
			}
			if(releaseStriker){
				float theta;
				float theta2;
				theta = atan2((y1-ys),(x1-xs));
				theta2= theta*180/PI;
				board.striker.setPower(2*fabs(sqrt(pow(xs-x1,2)+pow(ys-y1,2)))/BOX_LEN);
				board.striker.setAngle(theta2);
			}
			glutPostRedisplay();
		}
	}
}
