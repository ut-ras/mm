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

const int** Maze::getMaze(){
    return maze;
}