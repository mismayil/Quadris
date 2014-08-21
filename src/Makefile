quadris: cell.o board.o block.o display.o window-v2.o quadris.o
	g++ cell.o board.o block.o display.o quadris.o window-v2.o -o quadris -lX11
	
quadris.o: quadris.cc board.cc block.cc cell.cc display.cc window-v2.cc board.h block.h cell.h display.h window-v2.h
	g++ -c quadris.cc
	
board.o: board.cc display.cc cell.cc board.h display.h cell.h
	g++ -c board.cc
	
block.o: block.cc cell.cc board.cc block.h cell.h block.h
	g++ -c block.cc
	
display.o: display.cc display.h
	g++ -c display.cc
	
cell.o: cell.cc display.cc window-v2.cc cell.h display.h window-v2.h
	g++ -c cell.cc
	
window-v2.o: window-v2.cc window-v2.h
	g++ -c window-v2.cc
