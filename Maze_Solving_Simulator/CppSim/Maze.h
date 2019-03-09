/**
 *  Maze.h
 *  @Description: This class manages maze functions.
 *  @Authors: Matthew Yu and Ahmad Ahbab
 *  @Org: Micromouse
 */
#ifndef _MAZE_H
#define _MAZE_H
#define MAZE_SIDE 16

class Maze{
    private:
        static int[16][16] maze;
        static int[16] top = {14,13,12,11,10,9,8,7,7,8,9,10,11,12,13,14};

    public:
        /**
         *  @Description: Maze constructor clears all entries of the maze.
         */
        Maze();

        /**
         *  @Description: setMaze sets all the hamming distances (to the center)
         *  of the maze.
         */
        void setMaze();

        /**
         *  @Description: getMaze returns a read only 2d array of the maze.
         *  @Return: const int**, pointer to the maze
         */
        const int** getMaze();

        // Maze specific api to emulate mouse sensors
};

#endif
