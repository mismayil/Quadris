#ifndef __DISPLAY_H__
#define __DISPLAY_H__
#include <iostream>

const int rowSize = 18;
const int colSize = 10;

class TextDisplay {
    
    char **theDisplay;
    
    public:
    
    TextDisplay();
    ~TextDisplay();
    char** getDisplay();
    void notify(int r, int c, char blockType);  //changes char at row r, col c
    
    friend std::ostream& operator<<(std::ostream &out, const TextDisplay &d);
};

#endif
