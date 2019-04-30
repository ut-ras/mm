/**
 *  Simulator.cpp
 *  @Description: This class manages the maxe and mouse state.
 *      It can run plug-in algorithms to traverse the mouse across the maze.
 *  @Authors: Matthew Yu and Ahmad Ahbab
 *  @Org: Micromouse
 */
#include "Simulator.h"

Simulator::Simulator(){
    maze = new Maze();
    mouse = new Mouse(*maze);
    algo = new Algorithm();
}

Simulator::Simulator(string input){
    maze = new Maze(input);
    mouse = new Mouse(0/2, maze->getMazeHeight()/2 - 1, 90.0, *maze);
    algo = new Algorithm();
}

void Simulator::printExploredMaze(){
    algo->printMaze();
}

void Simulator::printTotalMaze(){
    maze->printMaze(mouse->getPositionX(), mouse->getPositionY(), mouse->getHeading());
}

void Simulator::run(){
    while(iterateStep());
    printTotalMaze();
    printExploredMaze();
}

void Simulator::run(int n){
    // kick out if finished early or reaches n steps.
    for(int i = 0; i < n; i++)
        if(iterateStep())
            break;
}

bool Simulator::iterateStep(){
    // check front, left, and right
    bool check[3];  // find way to fix into declaration or directly into .getCheck()
    check[0] = mouse->checkLeft();
    check[1] = mouse->checkFront();
    check[2] = mouse->checkRight();
    algo->getCheck(check);
    // make a decision
    int* decision = algo->decide();
    // possibly print decision
    switch(decision[0]){
        case 0: // move forwards
            mouse->moveForward(decision[1]);
            break;
        case 1: // move backwards
            mouse->moveBackward(decision[1]);
            break;
        case 2: // rotate
            mouse->rotate(decision[1]);
            break;
        case 3: // finished
            printf("End condition reached for algorithm.");
            return false;
    }
    return true;
}

Mouse* Simulator::getMouse(){
    return mouse;
}
Algorithm* Simulator::getAlgorithm(){
    return algo;
}
