#include "cell.h"

using namespace std;

Cell::Cell(): isOccupied(false), height(0), width(0), colour(0), xw(0) {}

Cell::~Cell() {}

void Cell::setCoords(int r, int c) {
   row = r;
   col = c;
}

void Cell::setCoords(int x, int y, int width, int height, Xwindow *xw) {
   this->x = x;
   this->y = y;
   this->width = width;
   this->height = height;
   this->xw = xw;
}

void Cell::draw(int color) {
   if (xw != 0) {
     xw->fillRectangle(x,y,width,height,color);
     xw->fillRectangle(x,y,width,1,9);
     xw->fillRectangle(x,y,1,height,9);
   }
}

int Cell::getRow() {
   return row;
}

int Cell::getCol() {
   return col;
}

bool Cell::getState() {
   return isOccupied;
}

int Cell::getColor() {
   return colour;
}

void Cell::notify(bool occupied, int color) {
   isOccupied = occupied;
   this->colour = color;
   draw(color);
}

void Cell::notifyDisplay(TextDisplay *d, char blockType) {
   d->notify(row,col,blockType);
}
