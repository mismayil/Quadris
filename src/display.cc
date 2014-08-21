#include <iostream>
#include "display.h"

using namespace std;

TextDisplay::TextDisplay() {
    
    theDisplay = new char*[rowSize];
    
    for (int i = 0;i < rowSize;i++) {
       theDisplay[i] = new char[colSize];
    }
    
    for (int i = 0;i < rowSize;i++) {
       for (int j = 0;j < colSize;j++) {
          theDisplay[i][j] = ' ';
       }
    }
}

TextDisplay::~TextDisplay() {
    
    for (int i = 0;i < rowSize;i++) {
       delete [] theDisplay[i];
    }
    
    delete theDisplay;
}

void TextDisplay::notify(int r, int c, char blockType) {
    
    theDisplay[r][c] = blockType;
}

char** TextDisplay::getDisplay() {
    return theDisplay;
}

ostream& operator<<(ostream &out, const TextDisplay &d) {
    
    for (int i = 0;i < colSize;i++) {
       out << "_";
    }
    
    out << endl;
    
    for (int i = 0;i < rowSize;i++) {
       for (int j = 0;j < colSize;j++) {
          out << d.theDisplay[i][j];
       }
       out << endl;
    }
    
    for (int i = 0;i < colSize;i++) {
       out << "_";
    }
    
    return out;
}
