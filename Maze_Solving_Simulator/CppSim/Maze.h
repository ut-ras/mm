/**
 *  Maze.h
 *  @Description: This class manages maze functions.
 *  @Authors: Matthew Yu and Ahmad Ahbab
 *  @Org: Micromouse
 */
#pragma once

// #include "Params.h"
#include <string>
#include <cstring>
#include <fstream>
using namespace std;

class Maze{
    private:
        int** maze;
        int MAZE_HEIGHT;
        int MAZE_WIDTH;

        /**
         * @Description: parse takes in a text file of a maze and sets the maze.
         * @param: string input - name of the maze file to parse.
         */
        void parse(string input);
    public:
        /**
         *  @Description: Maze constructor creates a default, empty maze.
         */
        Maze();

        /**
         *  @Description: Maze constructor creates a preset maze from the file name input.
	     *  @param: string input - String obj of file name to load from
         */
        Maze(string input);

    	/**
    	 *  @Description: numPaths gives the number of open paths at position (x, y).
    	 *  @param: int x - x position (scaled x2)
    	 *  @param: int y - y position (scaled x2)
    	 *  @return: int number of paths open
    	 */
    	int numPaths(int x, int y);

        /**
         * @Description: query calls the Maze and checks if this particular position is open or not.
         * @param: int x - x position to check (scaled x2)
         * @param: int y - y position to check (scaled x2)
         * @return: bool true if no wall, false if wall exists
         */
        bool query(int x, int y);

        /**
         * @Description: printMaze - safe encapsulated method to display total maze.
         * used by Simulator to read-access maze data.
         * @param: int x - x position of Mouse
         * @param: int y - y position of Mouse
         * @param: double heading - heading of Mouse
         */
        void printMaze(int x, int y, double heading);

        /**
         * @Description: getMazeWidth - get width of maze.
         * @Note: used by Mouse class for initialization.
         * @return int MAZE_WIDTH
         */
        int getMazeWidth();
        /**
         * @Description: getMazeHeight - get height of maze.
         * @Note: used by Mouse class for initialization.
         * @return int MAZE_HEIGHT
         */
        int getMazeHeight();
};
