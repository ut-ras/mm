/**
 *  Simulator.cpp
 *  @Description: This class manages the maxe and mouse state.
 *      It can run plug-in algorithms to traverse the mouse across the maze.
 *  @Authors: Matthew Yu and Ahmad Ahbab
 *  @Org: Micromouse
 */

Simulator::Simulator(){
    maze = Maze();
    mouse = Mouse();
    algo = Algorithm();
}

Simulator::Simulator(char *argv[]){
    maze = Maze(argv);
    mouse = Mouse();
    algo = Algorithm();
}

void Simulator::printExploredMaze(){

}

void Simulator::printTotalMaze(){

}

void Simulator::run(){

}

void Simulator::run(int n){

}
