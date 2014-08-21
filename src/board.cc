#include "board.h"
#include <cmath>
#include <sstream>

using namespace std;

int Board::hiScore = 0;
int Board::level = 0;

Board::Board(bool graphicState): gameOver(false), score(0), graphics(graphicState) {
    
    theBoard = new Cell*[rowSize];
    display = new TextDisplay();
    
    if (graphics) {
       xw = new Xwindow();
       cellSize = 25;
    }
    
    for (int i = 0;i < rowSize;i++) {
       theBoard[i] = new Cell[colSize];
    }
    
    for (int i = 0;i < rowSize;i++) {
       for (int j = 0;j < colSize;j++) {
          theBoard[i][j].setCoords(i,j);
          if (graphics) {
            theBoard[i][j].setCoords(j*cellSize, i*cellSize, cellSize, cellSize, xw);
            theBoard[i][j].notify(false);
          }
       }
    }
    
    if (graphics) {
     
      for (int i = 0;i < rowSize;i++) { 
         for (int j = 0;j < colSize;j++) {         //to fix the problem with appearance of rows at first
            xw->fillRectangle(j*cellSize,i*cellSize,cellSize,cellSize);
            xw->fillRectangle(j*cellSize,i*cellSize,cellSize,1,9);
            xw->fillRectangle(j*cellSize,i*cellSize,1,cellSize,9);
         }
      }
		  
		  xw->fillRectangle(colSize*cellSize, 0, 1, rowSize*cellSize);
		  xw->fillRectangle(0, rowSize*cellSize, colSize*cellSize, 1);
		  xw->fillRectangle(10*25, 4*25, 300, 40, 6);
		  xw->drawBigString(12*25, 5*25, "Q U A D R I S", 1);
		  xw->drawString(14*25, 18*25, "Created and designed", 4);
		  xw->drawString(14*25, 18*25+15, "By Mahammad", 4);
		  xw->drawString(14*25, 18*25+30, "Copyrights (c) 2013", 4);
    }
    
}

Board::~Board() {
    
    for (int i = 0;i < rowSize;i++) {
       delete [] theBoard[i];
    }
    
    delete theBoard;
    delete display;
    delete sequence;
    if (graphics) delete xw;
}

Cell** Board::getBoard() {
    return theBoard;
}

TextDisplay* Board::getDisplay() {
    return display;
}

int Board::getScore() {
    return score;
}

int Board::getLevel() {
    return level;
}

int Board::getHiScore() {
    return hiScore;
}

bool Board::getGraphics() {
    return graphics;
}

Xwindow* Board::getXwindow() {
    return xw;
}

char* Board::getSequence() {
    return sequence;
}

bool Board::isGameOver() {
    return gameOver;
}

void Board::setGameOver() {
    gameOver = true;
}

void Board::setLevel(int level) {
    this->level = level;
    
    if ((level == 1) || (level == 2)) {
      sequence = new char[7];
      sequence[0] = 'S';
      sequence[1] = 'T';
      sequence[2] = 'I';
      sequence[3] = 'L';
      sequence[4] = 'J';
      sequence[5] = 'O';
      sequence[6] = 'Z';
    }
    
    if (level == 3) {
      sequence = new char[7];
      sequence[0] = 'S';
      sequence[1] = 'Z';
      sequence[2] = 'I';
      sequence[3] = 'L';
      sequence[4] = 'J';
      sequence[5] = 'O';
      sequence[6] = 'T';
    }
}

void Board::setHiScore(int hscore) {
    hiScore = hscore;
}

void Board::recalculate() {
    
    bool full;
    int numFullLines = 0;
    
    for (int i = rowSize-1;i >= 0;) {
       full = true;
       for (int j = 0;j < colSize;j++) {
          if (!theBoard[i][j].getState()) {
            full = false;
            break;
          }
       }
       
       if (full) {
         
         numFullLines++;
         for (int j = 0;j < colSize;j++) {
            theBoard[i][j].notify(false);
            theBoard[i][j].notifyDisplay(display, ' ');
         }
         
         for (int k = i-1;k >= 0;k--) {
            for (int j = 0;j < colSize;j++) {
               theBoard[k+1][j].notify(theBoard[k][j].getState(),theBoard[k][j].getColor());
               theBoard[k+1][j].notifyDisplay(display, display->getDisplay()[k][j]);
            }
         }
         
         for (int j = 0;j < colSize;j++) {
            theBoard[0][j].notify(false);
            theBoard[0][j].notifyDisplay(display, ' ');
         }
         
       } else i--;
    }
    
    if (numFullLines > 0) {
      score = score + pow(numFullLines+level, 2);
      if (score > hiScore) hiScore = score;
    }
}

void Board::levelUp() {
    if (level+1 <= 3) setLevel(++level);
}

void Board::levelDown() {
    if (level-1 >= 0) setLevel(--level);
}

ostream& operator<<(ostream &out, Board &b) {
    
    out << "Level:    " << b.getLevel() << endl;
    out << "Score:    " << b.getScore() << endl;
    out << "Hi Score: " << b.getHiScore() << endl;
    
    if (b.getGraphics()) {
		  stringstream ss;
		  
		  b.getXwindow()->fillRectangle(10*25, 0, 300, 100, 4);
		  
		  b.getXwindow()->drawBigString(12*25, 25, "Level:", 0);
		  ss << b.getLevel();
		  b.getXwindow()->fillRectangle(16*25, 0, 100, 25, 4);
		  b.getXwindow()->drawBigString(16*25, 1*25, ss.str(), 0);
		  ss.str("");
		  
		  b.getXwindow()->drawBigString(12*25, 2*25, "Score:", 0);
		  ss << b.getScore();
		  b.getXwindow()->fillRectangle(16*25, 1*25, 100, 25, 4);
		  b.getXwindow()->drawBigString(16*25, 2*25, ss.str(), 0);
		  ss.str("");
		  
		  b.getXwindow()->drawBigString(12*25, 3*25, "Hi Score:", 0);
		  ss << b.getHiScore();
		  b.getXwindow()->fillRectangle(16*25, 2*25, 100, 25, 4);
		  b.getXwindow()->drawBigString(16*25, 3*25, ss.str(), 0);
		  
    }
    
    out << *(b.display);
    return out;
}
