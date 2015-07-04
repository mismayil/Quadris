Quadris
=======

Non-real time version of Tetris.<br>

Run make to build and ./quadris to start the game.<br>

Options:<br>
  -text_______________no graphics, only text display
  -seed n             seed to generate random blocks
  -scriptfile file    file to read order of blocks from (default: sequence.txt)
  -startlevel l       level of the game to start
  
Commands:
  <num>left                move the block to the left <num> times 
  <num>right               move the block to the right <num> times
  <num>down                move the block down <num> times
  <num>drop                drop <num> next blocks
  <num>clockwise           turn the block clockwise <num> times
  <num>counterclockwise    turn the block counterclockwise <num> times
  <num>levelup             increase the level of the game to <num>
  <num>leveldown           decrease the level of the game to <num>
  restart                  restart the game
