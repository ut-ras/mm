/**
 *  Simulator.cpp
 *  @Description: This class manages the maxe and mouse state.
 *      It can run plug-in algorithms to traverse the mouse across the maze.
 *  @Authors: Matthew Yu and Ahmad Ahbab
 *  @Org: Micromouse
 */

Simulator::Simulator(){
    maze = Maze();
    mouse = Mouse();
}

void Simulator::printMaze(){
    int** mazeData = maze.getMaze();
    for(int i = 15; i > -1; i--){
        for(int j = 0; j < 16; j++){
            if(mouse.getx()==j && mouse.gety()==i){
                printf("**|");
            }
            else{
                printf("%02d|", mazeData[j][i]);
            }
        }
        printf("\n");
        for(int j = 0; j < 16; j++){
            printf("---");
        }
        printf("\n");
    }
    printf("\n\n");
}
