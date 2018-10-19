//Tremaux's Algorithm

/**
 *memPrintMaze function taken from the following author and repurposed
 *to display the mouse memory path in the maze. Also cleaner ASCII maze.
 *Author: <brandon.blodget@gmail.com>
 *Copyright 2011 Brandon Blodget.
 *To display this new maze presentation, copy and paste over the same function
 *in maze.js from the inspect->sources window. call mouse.memPrintMaze(); from the console.
 **/
mouse.memPrintMaze = function() {
	var x,y;
	var str="";
	var path;

	// print debugging info
	str = "Flood values:\n";
	for (y=0;y<cHeight;y++) {
		// print north wall
		for (x=0;x<cWidth;x++) {
      let visited = 0;
      if (memMaze[y][x][VISIT])
        visited = 1;
			path = memMaze[y][x][NORTH];
			if (path) {
        if (visited) {
          str += "#- ";
        }else {
          str += "#  ";
        }
			} else {
				str += "###";
			}
		}
		str += "#\n";
		// print west wall
		for (x=0;x<cWidth;x++) {
      let visited = 0;
      if (memMaze[y][x][VISIT])
        visited = 1;
			path = memMaze[y][x][WEST];
			if (path) {
        if (visited) {
          str += " - ";
        }else {
          str += "   ";
        }
			} else {
        if (visited) {
          str += "#- ";
        }else {
          str += "#  ";
        }
			}
		}
		str += "#\n";
	}
	str += "#################################################\n";
	console.log(str);
};

//creates a grid to hold memory
const unvisited = 0, visited =  1, blocked = 2, start = -1, goal = -2;
var cells[cHeight][cWidth];
initializeMouse(){
  for(int i = 0; i < cHeight; i++){
    for(int j = 0; j < cWidth; j++){
      cells[i][j] = 0;
    }
  }
  //set start and goal points
  cells[cHeight][0] = start;
  cells[8][8] = goal;
  cells[8][9] = goal;
  cells[9][8] = goal;
  cells[9][9] = goal;
}

//Clear the driver object.
driver = {};
//Boolean. TRUE = go to the goal. FALSE = go back to start.
driver.goGoal;
//Gets called only when downloaded to the mouse
//Performs initialization
driver.load = function() {
    //default maze
      //mouse.loadMaze("91japa1");
    driver.goGoal = true
    initializeMouse();
}

//Calls on each iteration. Determines the next move.
driver.next = function() {
  //if the goal is reached.
  if (mouse.isGoal() && driver.goGoal) {
    mouse.stop();
    alert("Center Reached! Moves: "+ mouse.moveCount() +
        "\nPress start to go home.");
    driver.goGoal = !driver.goGoal;
  }
  //if the start is reached.
  if (mouse.isHome() && !driver.goGoal) {
      mouse.stop();
      alert("Home Reached! Press start to run again.");
      driver.goGoal = !driver.goGoal;
  }

  //Algorithm Goes HERE
  //NOTE:
  //Move along the corridor until a junction is reached (2 or more paths exist
  //that branch from the cell.)
  //select the path with the smallest manhattan distance to the end point. If
  //there are several, hardcode to go in priority of clockwise direction starting
  //from north, as well as previously visited.
  //if a dead end has been reached, turn around and go back.
  //for every cell moved, mark the current cell as visited1 and visited2.
  //Never go back along a path marked twice.
  //ends when the center is reached.



}
