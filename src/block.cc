#include "block.h"
#include <sstream>

using namespace std;

Block::Block(Board *b, char blockType): blockType(blockType), board(b) {
    
    theBlock = new Cell**[blockSize];
    
    for (int i = 0;i < blockSize;i++) {
      theBlock[i] = new Cell*[blockSize];
    }
    
    for (int i = 0;i < blockSize;i++) {
      for(int j = 0;j < blockSize;j++) {
         theBlock[i][j] = 0;
      }
    }

    
    switch (blockType) {
    
      case 'I': 
        
        color = 8;
        
        for (int i = 0;i < blockSize;i++) {
           theBlock[3][i] = &(board->getBoard()[3][i]);
        }
        
        break;

      case 'J':
        
        color = 2;
        
        theBlock[2][0] = &(board->getBoard()[3][0]);
        theBlock[3][0] = &(board->getBoard()[4][0]);
        theBlock[3][1] = &(board->getBoard()[4][1]);
        theBlock[3][2] = &(board->getBoard()[4][2]);
        
        break;

      case 'L':
        
        color = 3;
        
        theBlock[2][2] = &(board->getBoard()[3][2]);
        
        for (int i = 0;i < blockSize-1;i++) {
           theBlock[3][i] = &(board->getBoard()[4][i]);
        }
        
        break;

      case 'O':
        
        color = 4;
        
        theBlock[2][0] = &(board->getBoard()[3][0]);
        theBlock[2][1] = &(board->getBoard()[3][1]);
        theBlock[3][0] = &(board->getBoard()[4][0]);
        theBlock[3][1] = &(board->getBoard()[4][1]);
        
        break;
        
      case 'S':
      
        color = 5;
        
        theBlock[2][1] = &(board->getBoard()[3][1]);
        theBlock[2][2] = &(board->getBoard()[3][2]);
        theBlock[3][0] = &(board->getBoard()[4][0]);
        theBlock[3][1] = &(board->getBoard()[4][1]);        
        
        break;
        
      case 'Z':
        
        color = 6;
        
        theBlock[2][0] = &(board->getBoard()[3][0]);
        theBlock[2][1] = &(board->getBoard()[3][1]);
        theBlock[3][1] = &(board->getBoard()[4][1]);
        theBlock[3][2] = &(board->getBoard()[4][2]);        
        
        break;
        
      case 'T':
        
        color = 7;
        
        for (int i = 0;i < blockSize-1;i++) {
           theBlock[2][i] = &(board->getBoard()[3][i]);
        }
        
        theBlock[3][1] = &(board->getBoard()[4][1]);
        
        break;
      
    }
    
    for (int i = 0;i < blockSize;i++) {
       for (int j = 0;j < blockSize;j++) {
          if (theBlock[i][j] != 0) {
            if (theBlock[i][j]->getState()) {
              board->setGameOver();
              break;
            }
          }
       }
    } 
    
    if (!(board->isGameOver())) {
       for (int i = 0;i < blockSize;i++) {
          for (int j = 0;j < blockSize;j++) {
             if (theBlock[i][j] != 0) {
               theBlock[i][j]->notify(true,color);
               theBlock[i][j]->notifyDisplay(board->getDisplay(), blockType);
             }
          }
       }
    }
    this->goRight();  //to fix the problem of appearance of the block in the beginning
    this->goLeft();
   
}

void Block::goLeft() {
    
    bool possible = true;
    int row, col;
    
    for (int i = 0;i < blockSize;i++) {
       for (int j = 0;j < blockSize;j++) {
          if ((theBlock[i][j] != 0) && ((j == 0) || (theBlock[i][j-1] == 0))) {
            row = theBlock[i][j]->getRow();
            col = theBlock[i][j]->getCol();
       
            if (col-1 < 0) {
              possible = false;
              break;
            } else {
                if (board->getBoard()[row][col-1].getState()) {
                  possible = false;
                  break;
                }
              }
          }
       }
    }
    
    
    if (possible) {
     
      for (int i = 0;i < blockSize;i++) {
         for (int j = 0;j < blockSize;j++) {
            if (theBlock[i][j] != 0) {
              theBlock[i][j]->notify(false);
              theBlock[i][j]->notifyDisplay(board->getDisplay(), ' ');
              row = theBlock[i][j]->getRow();
              col = theBlock[i][j]->getCol();
              theBlock[i][j] = &(board->getBoard()[row][col-1]);
            }
         }
      }
      
      for (int i = 0;i < blockSize;i++) {
         for (int j = 0;j < blockSize;j++) {
            if (theBlock[i][j] != 0) {
              theBlock[i][j]->notify(true,color);
              theBlock[i][j]->notifyDisplay(board->getDisplay(), blockType);
            }
         }
      }
    }
}

void Block::goRight() {
    
    bool possible = true;
    int row, col;
    
    for (int i = 0;i < blockSize;i++) {
       for (int j = 0;j < blockSize;j++) {
          if ((theBlock[i][j] != 0) && ((j == blockSize-1) || (theBlock[i][j+1] == 0))) {
            row = theBlock[i][j]->getRow();
            col = theBlock[i][j]->getCol();
       
            if (col+1 >= colSize) {
              possible = false;
              break;
            } else {
                if (board->getBoard()[row][col+1].getState()) {
                  possible = false;
                  break;
                }
              }
          }
       }
    }
    
    
    if (possible) {
     
      for (int i = 0;i < blockSize;i++) {
         for (int j = 0;j < blockSize;j++) {
            if (theBlock[i][j] != 0) {
              theBlock[i][j]->notify(false);
              theBlock[i][j]->notifyDisplay(board->getDisplay(), ' ');
              row = theBlock[i][j]->getRow();
              col = theBlock[i][j]->getCol();
              theBlock[i][j] = &(board->getBoard()[row][col+1]);
            }
         }
      }
      
      for (int i = 0;i < blockSize;i++) {
         for (int j = 0;j < blockSize;j++) {
            if (theBlock[i][j] != 0) {
              theBlock[i][j]->notify(true,color);
              theBlock[i][j]->notifyDisplay(board->getDisplay(), blockType);
            }
         }
      }
    }
}

void Block::goDown() {
    
    bool possible = true;
    int row, col;
    
    for (int i = 0;i < blockSize;i++) {
       for (int j = 0;j < blockSize;j++) {
          if ((theBlock[i][j] != 0) && ((i == blockSize-1) || (theBlock[i+1][j] == 0))) {
            row = theBlock[i][j]->getRow();
            col = theBlock[i][j]->getCol();
       
            if (row+1 >= rowSize) {
              possible = false;
              break;
            } else {
                if (board->getBoard()[row+1][col].getState()) {
                  possible = false;
                  break;
                }
              }
          }
       }
    }
    
    
    if (possible) {
     
      for (int i = 0;i < blockSize;i++) {
         for (int j = 0;j < blockSize;j++) {
            if (theBlock[i][j] != 0) {
              theBlock[i][j]->notify(false);
              theBlock[i][j]->notifyDisplay(board->getDisplay(), ' ');
              row = theBlock[i][j]->getRow();
              col = theBlock[i][j]->getCol();
              theBlock[i][j] = &(board->getBoard()[row+1][col]);
            }
         }
      }
      
      for (int i = 0;i < blockSize;i++) {
         for (int j = 0;j < blockSize;j++) {
            if (theBlock[i][j] != 0) {
              theBlock[i][j]->notify(true,color);
              theBlock[i][j]->notifyDisplay(board->getDisplay(), blockType);
            }
         }
      }
    }
}

void Block::drop() {
    
    int row, dropSteps;
    for (int i = blockSize-1;i >= 0;i--) {
       for (int j = blockSize-1;j >= 0;j--) {
          if (theBlock[i][j] != 0) {
             row = theBlock[i][j]->getRow();
             dropSteps = rowSize - row;
          }
       }
    }
    
    for (int i = 0;i < dropSteps;i++) {
       this->goDown();
    } 
}

void Block::rotateCW() {
    
    if (blockType != 'O') {
    
		  int rowDif, colDif;
		  
		  for (int i = 0;i < blockSize;i++) {
		     for (int j = 0;j < blockSize;j++) {
		        if (theBlock[i][j] != 0) {
		          rowDif = theBlock[i][j]->getRow() - i;
		          colDif = theBlock[i][j]->getCol() - j;
		          break;
		        }
		     }
		  }
		  
		  Cell*** temp = new Cell**[blockSize];
				
			for (int i = 0;i < blockSize;i++) {
				 temp[i] = new Cell*[blockSize];
			}
				
			for (int i = 0;i < blockSize;i++) {
				 for (int j = 0;j < blockSize;j++) {
				    temp[i][j] = 0;
				 }
			}
				
			if (blockType == 'I') {
				
				if (theBlock[blockSize-1][blockSize-1] != 0) {
				   
				  for (int i = 0;i < blockSize;i++) {
				     temp[i][0] = theBlock[3][i];
				  }
				     
				} else if (theBlock[0][0] != 0) {
				             
				     for (int i = 0;i < blockSize;i++) {
				        temp[3][i] = theBlock[i][0];
				     }
				} 
				   
			} else {
				   
				   if ((theBlock[1][0] == 0) && (theBlock[1][1] == 0)) {  
				     for (int i = 2;i < blockSize;i++) {
				        for (int j = 0;j < blockSize-1;j++) {
				           temp[j+1][3-i] = theBlock[i][j]; 
				        }
				     }
				   } else {
				   	 for (int i = 1;i < blockSize;i++) {
				        for (int j = 0;j < blockSize-2;j++) {
				           temp[j+2][3-i] = theBlock[i][j];
				        }
				     }
				   }
			}
				  
			bool possible = true;
				  
			for (int i = 0;i < blockSize;i++) {
		     for (int j = 0;j < blockSize;j++) { 
		        if (temp[i][j] != 0) {
		          if ((rowDif+i >= rowSize) || (colDif+j >= colSize)) {
		            possible = false;
		            break;
		          }
		          if (board->getBoard()[rowDif+i][colDif+j].getState()) {
		            possible = false;
		            for (int k = 0;k < blockSize;k++) {
		               for (int l = 0;l < blockSize;l++) {
		                  if (temp[k][l] == &(board->getBoard()[rowDif+i][colDif+j])) {
		                    possible = true;
		                    break;
		                  }
		               }
		            }
		          }
		        }
		        if (!possible) break;
		     }
		     if (!possible) break;
		  }

		  if (possible) {
		  
				for (int i = 0;i < blockSize;i++) {
				   for (int j = 0;j < blockSize;j++) {
				      if (theBlock[i][j] != 0) {
						    theBlock[i][j]->notify(false);
						    theBlock[i][j]->notifyDisplay(board->getDisplay(), ' ');
						  }
					 }
				}
				           
				for (int i = 0;i < blockSize;i++) {
					 for (int j = 0;j < blockSize;j++) {
						  theBlock[i][j] = temp[i][j];
					 }
				}
				
				for (int i = 0;i < blockSize;i++) {
					 for (int j = 0;j < blockSize;j++) {
						  if (theBlock[i][j] != 0) {
						    theBlock[i][j] = &(board->getBoard()[rowDif+i][colDif+j]);
						    theBlock[i][j]->notify(true,color);
						    theBlock[i][j]->notifyDisplay(board->getDisplay(), blockType);
						  }
					 }
				}
				    	      
		  }
		         
    }
    
}

void Block::rotateCCW() {
    
    if (blockType != 'O') {
    
		  int rowDif, colDif;
		  
		  for (int i = 0;i < blockSize;i++) {
		     for (int j = 0;j < blockSize;j++) {
		        if (theBlock[i][j] != 0) {
		          rowDif = theBlock[i][j]->getRow() - i;
		          colDif = theBlock[i][j]->getCol() - j;
		          break;
		        }
		     }
		  }
		  
		  Cell*** temp = new Cell**[blockSize];
				
			for (int i = 0;i < blockSize;i++) {
				 temp[i] = new Cell*[blockSize];
			}
				
			for (int i = 0;i < blockSize;i++) {
				 for (int j = 0;j < blockSize;j++) {
				    temp[i][j] = 0;
				 }
			}
				
			if (blockType == 'I') {
				
				if (theBlock[blockSize-1][blockSize-1] != 0) {
				   
				  for (int i = 0;i < blockSize;i++) {
				     temp[i][0] = theBlock[3][i];
				  }
				     
				} else if (theBlock[0][0] != 0) {
				             
				     for (int i = 0;i < blockSize;i++) {
				        temp[3][i] = theBlock[i][0];
				     }
				} 
				   
			} else {
				   
				   if ((theBlock[1][0] == 0) && (theBlock[1][1] == 0)) { 
				     for (int i = 2;i < blockSize;i++) {
				        for (int j = 0;j < blockSize-1;j++) {
				           temp[3-j][i-2] = theBlock[i][j]; 
				        }
				     }
				   } else {
				        for (int i = 1;i < blockSize;i++) {
				           for (int j = 0;j < blockSize-2;j++) {
				              temp[3-j][i-1] = theBlock[i][j];
				           }
				        }
				   }
			}
				  
			bool possible = true;
				  
			for (int i = 0;i < blockSize;i++) {
		     for (int j = 0;j < blockSize;j++) { 
		        if (temp[i][j] != 0) {
		        	if ((rowDif+i >= rowSize) || (colDif+j >= colSize)) {
		            possible = false;
		            break;
		          }
		          if (board->getBoard()[rowDif+i][colDif+j].getState()) {
		            possible = false;
		            for (int k = 0;k < blockSize;k++) {
		               for (int l = 0;l < blockSize;l++) {
		                  if (temp[k][l] == &(board->getBoard()[rowDif+i][colDif+j])) {
		                    possible = true;
		                    break;
		                  }
		               }
		            }
		          }
		        }
		        if (!possible) break;
		     }
		     if (!possible) break;
		  }

		  if (possible) {
		  
				for (int i = 0;i < blockSize;i++) {
				   for (int j = 0;j < blockSize;j++) {
				      if (theBlock[i][j] != 0) {
						    theBlock[i][j]->notify(false);
						    theBlock[i][j]->notifyDisplay(board->getDisplay(), ' ');
						  }
					 }
				}
				           
				for (int i = 0;i < blockSize;i++) {
					 for (int j = 0;j < blockSize;j++) {
						  theBlock[i][j] = temp[i][j];
					 }
				}
				
				for (int i = 0;i < blockSize;i++) {
					 for (int j = 0;j < blockSize;j++) {
						  if (theBlock[i][j] != 0) {
						    theBlock[i][j] = &(board->getBoard()[rowDif+i][colDif+j]);
						    theBlock[i][j]->notify(true,color);
						    theBlock[i][j]->notifyDisplay(board->getDisplay(), blockType);
						  }
					 }
				}
		  }
		         
    }
    
}
    

void Block::print(char blockType) {
    
    stringstream ss;
    
    switch (blockType) {
      
      case 'I':
        cout << "IIII";
        
        if (board->getGraphics()) {
          for (int i = 0;i < blockSize;i++) {
             board->getXwindow()->fillRectangle(12*25+i*25, 8*25, 25, 25, 0);
             board->getXwindow()->fillRectangle(12*25+i*25, 8*25+25, 25, 25, 0);
          }
          
          for (int i = 0;i < blockSize;i++) {
             board->getXwindow()->fillRectangle(12*25+i*25, 8*25, 25, 25, 8);
          }
        }
        break;
      case 'J':
        cout << "J" << endl << "JJJ";
        
        if (board->getGraphics()) {
          for (int i = 0;i < blockSize;i++) {
             board->getXwindow()->fillRectangle(12*25+i*25, 8*25, 25, 25, 0);
             board->getXwindow()->fillRectangle(12*25+i*25, 8*25+25, 25, 25, 0);
          }
          
          board->getXwindow()->fillRectangle(12*25, 8*25, 25, 25, 2);
          
          for (int i = 0;i < blockSize-1;i++) {
             board->getXwindow()->fillRectangle(12*25+i*25, 8*25+25, 25, 25, 2);
          }
        }
        break;
      case 'L':
        cout << "  L" << endl << "LLL";
 
        if (board->getGraphics()) {
          for (int i = 0;i < blockSize;i++) {
             board->getXwindow()->fillRectangle(12*25+i*25, 8*25, 25, 25, 0);
             board->getXwindow()->fillRectangle(12*25+i*25, 8*25+25, 25, 25, 0);
          }
          
          board->getXwindow()->fillRectangle(12*25+2*25, 8*25, 25, 25, 3);
          
          for (int i = 0;i < blockSize-1;i++) {
             board->getXwindow()->fillRectangle(12*25+i*25, 8*25+25, 25, 25, 3);
          }
        }
        break;
      case 'O':
        cout << "OO" << endl << "OO";
      
        if (board->getGraphics()) {
          for (int i = 0;i < blockSize;i++) {
             board->getXwindow()->fillRectangle(12*25+i*25, 8*25, 25, 25, 0);
             board->getXwindow()->fillRectangle(12*25+i*25, 8*25+25, 25, 25, 0);
          }
        
          board->getXwindow()->fillRectangle(12*25, 8*25, 25, 25, 4);
          board->getXwindow()->fillRectangle(12*25+1*25, 8*25, 25, 25, 4);
          board->getXwindow()->fillRectangle(12*25, 8*25+25, 25, 25, 4);
          board->getXwindow()->fillRectangle(12*25+1*25, 8*25+25, 25, 25, 4);
        }
        break;
      case 'S':
        cout << " SS" << endl << "SS";
        
        if (board->getGraphics()) {
          for (int i = 0;i < blockSize;i++) {
             board->getXwindow()->fillRectangle(12*25+i*25, 8*25, 25, 25, 0);
             board->getXwindow()->fillRectangle(12*25+i*25, 8*25+25, 25, 25, 0);
          }
        
          board->getXwindow()->fillRectangle(12*25+1*25, 8*25, 25, 25, 5);
          board->getXwindow()->fillRectangle(12*25+2*25, 8*25, 25, 25, 5);
          board->getXwindow()->fillRectangle(12*25, 8*25+25, 25, 25, 5);
          board->getXwindow()->fillRectangle(12*25+1*25, 8*25+25, 25, 25, 5);
        }
        break;
      case 'Z':
        cout << "ZZ" << endl << " ZZ";
        
        if (board->getGraphics()) {
          for (int i = 0;i < blockSize;i++) {
             board->getXwindow()->fillRectangle(12*25+i*25, 8*25, 25, 25, 0);
             board->getXwindow()->fillRectangle(12*25+i*25, 8*25+25, 25, 25, 0);
          }
        
          board->getXwindow()->fillRectangle(12*25, 8*25, 25, 25, 6);
          board->getXwindow()->fillRectangle(12*25+1*25, 8*25, 25, 25, 6);
          board->getXwindow()->fillRectangle(12*25+1*25, 8*25+25, 25, 25, 6);
          board->getXwindow()->fillRectangle(12*25+2*25, 8*25+25, 25, 25, 6);
        }
        break;
      case 'T':
        cout << "TTT" << endl << " T ";
        
        if (board->getGraphics()) {
          for (int i = 0;i < blockSize;i++) {
             board->getXwindow()->fillRectangle(12*25+i*25, 8*25, 25, 25, 0);
             board->getXwindow()->fillRectangle(12*25+i*25, 8*25+25, 25, 25, 0);
          }
        
          for (int i = 0;i < blockSize-1;i++) {
             board->getXwindow()->fillRectangle(12*25+i*25, 8*25, 25, 25, 7);
          }
        
           board->getXwindow()->fillRectangle(12*25+1*25, 8*25+25, 25, 25, 7);
        }
        break;
    }
}
   
Block::~Block() {}
        
        
        
        
                        
        
        
        
        
        
        
        
        
        
        
