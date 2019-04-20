/**
 *  Maze.cpp
 *  @Description: This class manages maze functions.
 *  @Authors: Matthew Yu and Ahmad Ahbab
 *  @Org: Micromouse
 */
#include "Maze.h"
using namespace std;

void Maze::parse(string filename){
    int maze[32][32];
    string line;
    ifstream myfile (filename);
    if (myfile.is_open()) {
        for (int j = 31; j > -1 && getline(myfile, line); j--) {
            char linechar[line.size() + 1];
            strcpy(linechar, line.c_str());
            for (int i = 0; i < 32; i++) {
                if (linechar[i] == ' ') {
                    maze[i][j] = 0;
                } else {
                    maze[i][j] = 1;
                }
            }
        }
        myfile.close();
    }
}

Maze::Maze(){
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
            maze[i][j] = 0;
        }
    }
}

Maze::Maze(char *argv[]){
    if(argc != null)
        parse(str(argv[1]));
    else
        printf("Maze::Maze(): null argument err\n");
}

const int** Maze::getMaze(){
    return maze;
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
    if((x < 0 || x >= 16) && (y < 0 || y >= 16)){
        if(maze[x][y] == 1)
            return true;    // wall exists
        return false;
    }else{
        printf("Maze::query(): Overflow/Underflow err - X:%i|Y:%i\n", x, y);
        return false;
    }
}
