/**
 *  Maze.cpp
 *  @Description: This class manages maze functions.
 *  @Authors: Matthew Yu and Ahmad Ahbab
 *  @Org: Micromouse
 */
#include "Maze.h"
#include <iostream>


/* Private */
void Maze::parse(string input){
    cout << "Looking at file input.." << endl;

    std::string line;
    ifstream myfile (input);
    if (myfile.is_open()) {
        cout << "File opened!" << endl;

        // get height of maze
        int row = 0;
        while(getline(myfile, line))
            row++;
        // return to beginning
        myfile.clear();
        myfile.seekg(0, ios::beg);
        MAZE_HEIGHT = MAZE_WIDTH = row;

        // fill up maze array
        int** linePtrs = new int*[MAZE_HEIGHT];
        for (int row = 0; row < MAZE_HEIGHT && getline(myfile, line); row++) {
            char linechar[MAZE_WIDTH];
            strcpy(linechar, line.c_str());
            int* line = new int[MAZE_WIDTH];
            for (int col = 0; col < MAZE_WIDTH; col++) {
                if (linechar[col] == ' ') {
                    line[col] = 0;
                } else {
                    line[col] = 1;
                }
            }

            linePtrs[row] = line;
        }
        maze = linePtrs;
        myfile.close();

        cout << "Maze loaded." << endl;
    }else{
        cout << "No file found." << endl;
    }
}

/* Public*/
Maze::Maze(){
    MAZE_HEIGHT = 16;
    MAZE_WIDTH = 16;
    int* linePtrs[MAZE_HEIGHT];
    for(int row = 0; row < MAZE_HEIGHT; row++){
        int line[MAZE_WIDTH];
        for(int col = 0; col < MAZE_WIDTH; col++){
            line[col] = 0;
        }
        linePtrs[row] = line;
    }
    maze = linePtrs;

    cout << "Maze generated." << endl;
}

Maze::Maze(string input){
    parse(input);
}

int Maze::numPaths(int x, int y){
    if((x < 0 || x >= 16) && (y < 0 || y >= 16)){
        int paths = 4;
        for(int i = 0; i < 4; i++){
            int x_n = x;
            int y_n = y;
            switch(i){
                case 0:
                    x_n++;
                    break;
                case 1:
                    x_n--;
                    break;
                case 2:
                    y_n++;
                    break;
                case 3:
                    y_n--;
                    break;
                default:
                    break;
            }

            if(maze[x_n][y_n] == 1 &&
                (x_n < 0 || x_n >= 16) &&
                (y_n < 0 || y_n >= 16))
                paths--;
        }
        return paths;
    }else{
        printf("Maze::numPaths(): Overflow/Underflow err - X:%i|Y:%i\n", x, y);
        return 0;
    }
}

bool Maze::query(int x, int y){
    if(!(x < 0 || x >= 32) && !(y < 0 || y >= 32)){
        if(maze[x][y] == 1)
            return true;    // wall exists
        return false;
    }
    else if((x < 0 || x >= 32) && (y < 0 || y >= 32)){
        return true;
    }
    else{
        printf("Maze::query(): Overflow/Underflow err - X:%i|Y:%i\n", x, y);
        return false;
    }
}

void Maze::printMaze(int x, int y, double heading){
    cout << "---Begin Maze---" << endl;
    for(int row = 0; row < MAZE_HEIGHT; row++){
        int line[MAZE_WIDTH];
        for(int col = 0; col < MAZE_WIDTH; col++){
            if(row == y*2 + 1 && col == x*2 + 1){
                switch((int) heading){  // mouse already takes care of heading double-ness
                    default:
                    case 0:
                        cout << " \u2192";
                        break;
                    case 90:
                        cout << " \u2191";
                        break;
                    case 180:
                        cout << " \u2190";
                        break;
                    case 270:
                        cout << " \u2193";
                        break;
                }
            }else{
                if(maze[row][col] == 1)
                    cout << " \u25A1";
                else
                    cout << " \u25A0";
            }
        }
        cout << endl;
    }
    cout << "---End Maze---" << endl;
}

int Maze::getMazeWidth(){
    return MAZE_WIDTH;
}
int Maze::getMazeHeight(){
    return MAZE_HEIGHT;
}
