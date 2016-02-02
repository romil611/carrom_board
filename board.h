#ifndef _BOARD_H
#define _BOARD_H

#include "constants.h"

class Board {
    public:
        float posX=0,posY=0;
        Striker striker;
        Coin coin[9];
        int coinsPocketed=0;
        int required=0;
        int score=0;
        time_t currentTime;
        time_t previousTime;
        time_t startTime;
        time_t pauseTime;
        bool gameEnded=false;
        bool win=false;
        Board();
        ~Board();

        void init(float,float);
        void update();
        void drawBoard();
        void drawCoins();
        float distence(float,float,float,float);
        void checkIfPocketed();
        void drawBox(float,float);
        void drawBall(float);
        void drawLines(float);
        void drawCircles(float);
        void checkCollision();
        time_t getCTime();
        time_t getSTime();
        time_t getPTime();
        time_t getPrTime();
        bool getGameEnded();
        bool getGameWinned();
        void updateGameEnded(bool,bool);
        //time currentTime();
        void updateCTime(time_t);
        void updateSTime(time_t);
        void updatePTime(time_t);
        void updatePrTime(time_t);
        void updateScore();
        bool vectorsApproachEachOther(float, float, float);
        template <typename X> void checkWallCollision(X &a,int);
        void handleCollision(Coin &a,Coin &b,int);
        template <typename X> void checkIfStopped(X &b);
        void writeOnBoard(float , float ,float, std::string s, float , float , float );
        void drawScoreboard();
        void gameEnd(int);
};

#endif