#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "cell.h"
#include "board.h"
#include <string>

const int blockSize = 4;

class Block {
    
    Cell ***theBlock;
    char blockType;
    Board *board;
    int color;
    
    public:
    
    Block(Board *b, char blockType);
    ~Block();
    
    void goLeft();
    void goRight();
    void goDown();
    void drop();
    void rotateCW();     //rotate clockwise
    void rotateCCW();    //rotate counterclockwise
    void print(char blockType);  //prints the block as string
    
};

#endif
