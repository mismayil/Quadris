#ifndef __BOARD_H__
#define __BOARD_H__

#include <iostream>
#include "cell.h"
#include "display.h"

class Board {
     
    Cell **theBoard;
    TextDisplay *display; 
    static int level;     //current level of the game
    static int hiScore;   //current hi Score of the game
    int score;            //current score of the game
    bool gameOver;        //to determine whether game is over or not
    Xwindow *xw;          
    int cellSize;         //size of a cell on window
    bool graphics;        //to determine whether graphics is on or off
    char *sequence;       //to generate random sequence of blocks
    
    public:
    
    Board(bool graphicState = true);
    ~Board();
    
    Cell** getBoard();
    TextDisplay* getDisplay();
    int getScore();
    int getHiScore();
    int getLevel();
    bool getGraphics();
    Xwindow* getXwindow();
    char* getSequence();
    bool isGameOver();
    void setGameOver();
    void setHiScore(int hscore);
    void recalculate();
    void setLevel(int level);
    void levelUp();
    void levelDown();
    
    friend std::ostream& operator<<(std::ostream &out, Board &b);
    
};
    
#endif
