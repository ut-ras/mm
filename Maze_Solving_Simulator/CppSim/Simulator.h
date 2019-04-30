/**
 *  Simulator.h
 *  @Description: This class manages the maze and mouse state.
 *      It can run plug-in algorithms to traverse the mouse across the maze.
 *  @Authors: Matthew Yu and Ahmad Ahbab
 *  @Org: Micromouse
 */
#pragma once

#include "Params.h"
#include "Maze.h"
#include "Mouse.h"
#include "Algorithm.h"
#include <string>
using namespace std;

class Simulator{
    private:
        Maze* maze;
        Mouse* mouse;
        Algorithm* algo;

        /**
         * @Description: iterateStep moves one timestep in the algorithm and field.
         * @return: boolean false if algorithm is done, true if can continue.
         */
        bool iterateStep();
    public:
        /**
         *  @Description: Simulator constructor sets up a default Maze, Mouse, and
         *      generic Algorithm.
         */
        Simulator();

        /**
         *  @Description: Simulator constructor sets up a default Mouse and Algorithm
         *      and a generated Maze given file name and/or path.
         *  @param string input command line arg containing file name converted into String obj.
         */
        Simulator(string input);

        /**
         *  @Description: printExploredMaze accesses the Algorithm API (if it exists)
         *      and prints out the algorithm's representation of the maze and the
         *      paths explored/seen by the algorithm's mouse.
         */
        void printExploredMaze();

        /**
         *  @Description: printTotalMaze accesses the Maze and Mouse API and prints
         *      out the complete maze with the mouse position and orientation.
         *      DOES NOT show paths taken or previous move history.
         */
        void printTotalMaze();

        /**
         *  Decision flow for simulation:
         *  Current mouse position, relative wall data is gathered and sent to the algorithm.
         *  The algorithm runs, makes a decision, and sends it back to the simulator.
         *  The simulator processes that decision (i.e. move mouse forward one step)
         *  and the iteration ends.
         */

        /**
         *  @Description: run simulates the simulator in an loop until an objective
         *  is complete (i.e. the center is reached, etc).
         */
        void run();

        /**
         *  @Description: run simulates the simulator in a loop for n loops or until
         *      an objective is complete, whichever comes first.
         *  @param int n number of loops.
         */
        void run(int n);
};
