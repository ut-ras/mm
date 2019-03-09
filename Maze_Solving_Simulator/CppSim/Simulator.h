/**
 *  Simulator.h
 *  @Description: This class manages the maxe and mouse state.
 *      It can run plug-in algorithms to traverse the mouse across the maze.
 *  @Authors: Matthew Yu and Ahmad Ahbab
 *  @Org: Micromouse
 */
#ifndef _SIMULATOR_H
#define _SIMULATOR_H

#include "Maze.h"
#include "Mouse.h"

class Simulator{
    private:
        static Maze maze;
        static Mouse mouse;
        generateField();
    public:
        /**
         *  @Description: Simulator constructor sets up the mouse and the field.
         */
        Simulator();

        /**
         *  @Description: printMaze prints the state of the maze and the mouse inside it.
         */
        void printMaze();
};

#endif
