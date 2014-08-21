#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include "board.h"
#include "block.h"

using namespace std;

string getCommand(string command) {           //transcribes command into the right command
    
    string left = "left";
    string right = "right";
    string down = "down";
    string drop = "drop";
    string clock = "clockwise";
    string cclock = "counterclockwise";
    string levelu = "levelup";
    string leveld = "leveldown";
    string restart = "restart";
    
    if (command.length() != 1) {
		  if ((command[0] == 'l') && (left.find(command) != string::npos) && (levelu.find(command) == string::npos) && 
		     (leveld.find(command) == string::npos)) 
		  return left;
		  if ((command[0] == 'r') && (right.find(command) != string::npos) && (restart.find(command) == string::npos)) return right;
		  if ((command[0] == 'd') && (down.find(command) != string::npos) && (drop.find(command) == string::npos)) return down;
		  if ((command[0] == 'd') && (drop.find(command) != string::npos) && (down.find(command) == string::npos)) return drop;
		  if ((command[0] == 'c') && (clock.find(command) != string::npos)) return clock;
		  if ((command[0] == 'c') && (cclock.find(command) != string::npos)) return cclock;
		  if ((command[0] == 'l') && (command[1] == 'e') && (levelu.find(command) != string::npos) && (left.find(command) == string::npos) && 
		     (leveld.find(command) == string::npos)) 
		  return levelu;
		  if ((command[0] == 'l') && (command[1] == 'e') && (leveld.find(command) != string::npos) && (levelu.find(command) == string::npos) &&
		     (left.find(command) == string::npos))
		  return leveld;
		  if ((command[0] == 'r') && (command[1] == 'e') && (restart.find(command) != string::npos) && (right.find(command) == string::npos))
		  return restart;  
		  else return "";
    } else return "";
}
    

int main(int argc, char* argv[]) {
    
    Board *qBoard;
    string arg1;
    string arg2;
    int seed = 1;
    int level = 0;
    string scriptfile = "sequence.txt";
    bool graphics = true;  //to determine whether graphics is on or off
    int randNum;
    bool hold = false;      //to hold next block from coming
    bool generate = false;  //to generate next blocks within drop command
    
    for (int i = 1;i < argc;i++) {
       arg1 = argv[i];
       
       if (arg1 == "-text") {
          graphics = false;
       }
       
       if (arg1 == "-seed") {
          arg2 = argv[i+1];
          stringstream ss(arg2);
          ss >> seed;
       }
       
       if (arg1 == "-scriptfile") {
          arg2 = argv[i+1];
          scriptfile = arg2;
       }
       
       if (arg1 == "-startlevel") {
          arg2 = argv[i+1];
          stringstream ss(arg2);
          ss >> level;
          
       }
    }
    
    if (!graphics) qBoard = new Board(false);
    else qBoard = new Board;
    
    if (level <= 3) qBoard->setLevel(level);
    else qBoard->setLevel(3);
    
    ifstream ifs(scriptfile.c_str());
    if (ifs.fail()) ifs.open("sequence.txt"); 
    
    char blockType; 
    string command;
    int mult;        //multiplier
    
    switch (qBoard->getLevel()) {
      case 0: 
        ifs >> blockType;
        ifs.ignore();
        break;
      case 1:
        srand(seed);
        randNum = rand() % 12;
        if (randNum == 6) blockType = qBoard->getSequence()[randNum];
        else blockType = qBoard->getSequence()[randNum % 6];
        break;
      case 2:
        srand(seed);
        randNum = rand() % 7;
        blockType = qBoard->getSequence()[randNum % 7];
        break;
      case 3:
        srand(seed);
        randNum = rand() % 9;
        blockType = qBoard->getSequence()[randNum % 7];
        break;
    }
    
    Block *block = new Block(qBoard, blockType);
    
    while (1) {
      
      cout << *qBoard << endl;
      
      if (qBoard->isGameOver()) {
        int hscore = qBoard->getHiScore();
        delete qBoard;
        hold = false;
        generate = false;
        
        if (!graphics) qBoard = new Board(false);
        else qBoard = new Board;
    
        qBoard->setLevel(0);
        qBoard->setHiScore(hscore);
        ifs.close();
        ifs.open(scriptfile.c_str());
				ifs >> blockType;
				ifs.ignore();
        block = new Block(qBoard, blockType);
        cout << *qBoard << endl;
      }
      
      if (!hold) {
		    
		    switch (qBoard->getLevel()) {
		      case 0:
		        ifs >> blockType;
		    
						if (ifs.fail()) {
						  ifs.close();
						  ifs.open(scriptfile.c_str());
						  ifs >> blockType;
						}
						
						ifs.ignore();
						break;
					case 1:
		        randNum = rand() % 12;
		        if (randNum == 6) blockType = qBoard->getSequence()[randNum];
		        else blockType = qBoard->getSequence()[randNum % 6];
		        break;
		      case 2:
		        randNum = rand() % 7;
		        blockType = qBoard->getSequence()[randNum % 7];
		        break;
		      case 3:
		        randNum = rand() % 9;
            blockType = qBoard->getSequence()[randNum % 7];
            break;
		    }
		    
      }
      
      cout << "Next:" << endl;
      
      if (graphics) qBoard->getXwindow()->drawBigString(12*25, 7*25, "Next: ", 2);
      block->print(blockType);
      cout << endl;
      
      cin >> mult;
      
      if (cin.fail()) {
        cin.clear();
        cin >> command;
        mult = 1;
      } else cin >> command;
      
      if (getCommand(command) == "left")  {
        hold = true;
        while (mult != 0) {
            block->goLeft();
            mult--;
        }
      }
      
      if (getCommand(command) == "right") {
        hold = true;
        while (mult != 0) {
            block->goRight();
            mult--;
        }
      }
      
      if (getCommand(command) == "down") {
        hold = true;
        while (mult != 0) {
            block->goDown();
            mult--;
        }
      }
         
      if (getCommand(command) == "clockwise")  {
        hold = true;
        while (mult != 0) {
            block->rotateCW();
            mult--;
        }
      }
        
      if (getCommand(command) == "counterclockwise")  {
        hold = true;
        while (mult != 0) {
            block->rotateCCW();
            mult--;
        }
      }
        
      if (getCommand(command) == "drop") {
         
         if (mult != 0) hold = false;
         else hold = true;
         
         if (mult > 1) generate = true;
         
         while (mult != 0) {
            
            block->drop();
            qBoard->recalculate();
            block = new Block(qBoard, blockType);
            if (qBoard->isGameOver()) break;
            
            if (generate) {
              
              if (mult != 1) {
		            
		            switch (qBoard->getLevel()) {
									case 0:
										ifs >> blockType;
						
										if (ifs.fail()) {
											ifs.close();
											ifs.open(scriptfile.c_str());
											ifs >> blockType;
										}
										
										ifs.ignore();
										break;
									case 1:
										randNum = rand() % 12;
										if (randNum == 6) blockType = qBoard->getSequence()[randNum];
										else blockType = qBoard->getSequence()[randNum % 6];
										break;
									case 2:
										randNum = rand() % 7;
										blockType = qBoard->getSequence()[randNum % 7];
										break;
									case 3:
										randNum = rand() % 9;
		                blockType = qBoard->getSequence()[randNum % 7];
		                break;
								}
								
							}
							
					  }
					  mult--;
					  
         }
         
         generate = false;
      }
      
      if (getCommand(command) == "levelup") {
        qBoard->levelUp();
        hold = true;
      }
      if (getCommand(command) == "leveldown") {
        qBoard->levelDown();
        hold = true;
      }
      
      if (getCommand(command) == "restart") {
        int hscore = qBoard->getHiScore();
        delete qBoard;
        hold = false;
        generate = false;
        
        if (!graphics) qBoard = new Board(false);
        else qBoard = new Board;
    
        qBoard->setLevel(0);
        qBoard->setHiScore(hscore);
        ifs.close();
        ifs.open(scriptfile.c_str());
				ifs >> blockType;
				ifs.ignore();
        block = new Block(qBoard, blockType);
      }
      
      if (getCommand(command) == "") hold = true;
    }
    
    delete qBoard;
    return 0;

}
