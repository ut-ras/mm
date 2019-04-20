/**
 *  Simulator.cpp
 *  @Description: This class manages the maxe and mouse state.
 *      It can run plug-in algorithms to traverse the mouse across the maze.
 *  @Authors: Matthew Yu and Ahmad Ahbab
 *  @Org: Micromouse
 */
#include "Params.h"
#include "Simulator.h"
using namespace std;

Simulator::Simulator(){
    maze = Maze();
    mouse = Mouse();
    //algo = Algorithm(0, 0, 0);
}

Simulator::Simulator(char *argv[]){
    maze = Maze(argv);
    mouse = Mouse();
    //algo = Algorithm(0, 0, 0);
}

void Simulator::printExploredMaze(){
    // requires Algorithm.getMaze();

    // int** totMaze = Algorithm.getMaze();
    // for(int i = 0; i < MAZE_SIDE_LENGTH; i++){
    //     for(int j = 0; j < MAZE_SIDE_LENGTH; j++){
    //         printf("%i", totMaze[i][j]);
    //     }
    //     printf("\n");
    // }
    //
    // printf("---End Explored Maze---\n\n");
}

void Simulator::printTotalMaze(){
    int** totMaze = maze.getMaze();
    for(int i = 0; i < MAZE_SIDE_LENGTH; i++){
        for(int j = 0; j < MAZE_SIDE_LENGTH; j++){
            printf("%i", totMaze[i][j]);
        }
        printf("\n");
    }

    printf("---End Maze---\n\n");
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

void bool Simulator::iterateStep(){
    // check front, left, and right
    Algorithm.getCheck([mouse.checkLeft(), mouse.checkFront(), mouse.checkRight()]);
    // make a decision
    int* decision = Algorithm.decide();
    // possibly print decision
    switch(decision[0]){
        case 0: // move forwards
            mouse.moveForward(decision[1]);
            break;
        case 1: // move backwards
            mouse.moveBackward(decision[1]);
            break;
        case 2: // rotate
            mouse.rotate(decision[1]);
            break;
        case 3: // finished
            printf("End condition reached for algorithm.");
            return false;
    }
    return true;

}
