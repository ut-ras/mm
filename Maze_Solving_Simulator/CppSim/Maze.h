/**
 *  Maze.h
 *  @Description: This class manages maze functions.
 *  @Authors: Matthew Yu and Ahmad Ahbab
 *  @Org: Micromouse
 */
#ifndef _MAZE_H
#define _MAZE_H

#include "Params.h"
#include <string.h>
class Maze{
    private:
        static int[MAZE_SIDE_LENGTH][MAZE_SIDE_LENGTH] maze;

        /**
         * @Description: parse takes in a text file of a maze and sets the maze.
         * @param: string filename - name of the maze file to parse.
         */
        void parse(string filename);
    public:
        /**
         *  @Description: Maze constructor creates a default, empty maze.
         */
        Maze();

        /**
         *  @Description: Maze constructor creates a preset maze from the file name input.
	     *  @param: char *argv[] address of name of maze to load
         */
        Maze(char *argv[]);

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
};
#endif
