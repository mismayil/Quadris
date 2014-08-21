#ifndef __CELL_H__
#define __CELL_H__

#include "display.h"
#include "window-v2.h"

class Cell {
    
    bool isOccupied;  //the state of cell
    int row, col;     //the coordinates of cell
    int x, y, width, height;  //the parameters of cell on window
    Xwindow *xw;
    int colour;
    
    void draw(int color);
    
    public:
    
    Cell();
    ~Cell();
    void setCoords(int r, int c);   //set coordinates
    void setCoords(int x, int y, int width, int height, Xwindow *xw);  //set coordinates for the window
    int getRow();                   
    int getCol();
    bool getState();
    int getColor();
    void notify(bool occupied, int color=1);    //sets state of cell to the value of occupied
    void notifyDisplay(TextDisplay *d, char blockType);   //notifies display
    
    
};

#endif
