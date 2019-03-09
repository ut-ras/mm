/**
 *  Maze.cpp
 *  @Description: This class manages maze functions.
 *  @Authors: Matthew Yu and Ahmad Ahbab
 *  @Org: Micromouse
 */
Maze::Maze(){
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
            maze[i][j] = 0;
        }
    }
}

void Maze::setMaze(){
    for(int i = 0; i < 16; i++){
        maze[0][i] = top[i];
    }
    for(int i = 1; i < 8; i++){
        for(int j = 0; j < 16; j++){
            maze[i][j] = maze[i-1][j] - 1;
        }
    }
    for(int i = 0; i < 16; i++){
        maze[8][i] = maze[7][i];
    }
    for(int i = 9; i < 16; i++){
        for(int j = 0; j < 16; j++){
            maze[i][j] = maze[i-1][j] + 1;
        }
    }
}

const int** Maze::getMaze(){
    return maze;
}
