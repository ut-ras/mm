/**
 * Mouse.c
 * Author: Matthew Yu
 * Last modified: 11/30/18
 *
 * This file describes the mmouse class and the functions that it uses.
 * This class is dependent on the following classes and their source files:
 *      @class Node
 *      @class Neighbor
 *
 * TODO: Clean up input parameters since some duplicate off class
 **/
#include "Mouse.h"
#include <stdlib.h>
#include <stdio.h>
#define TRUE 1
#define FALSE 0
#define UNKNOWN -1

void initMouse(Mouse *mouse, int posX, int posY, int heading){
    mouse->position->x = posX;
    mouse->position->y = posY;
    mouse->heading = heading;
}

void move(Mouse *mouse, int activeDir){
    int facing = heading();
    //orientate mouse based on heading
    //move
    //adjust virtual position in mouse memory
    //loop
}

int findHammingDist(Position position, int dir){
    switch(dir){
        case 0:
            position.y--;
            break;
        case 1:
            position.x++;
            break;
        case 2:
            position.y++;
            break;
        case 3:
            position.x--;
            break;
    }
    if(position.x > 7){
        if(position.y > 7)
            return abs(position.x-8) + abs(position.y-8);
        else
            return abs(position.x-8) + abs(position.y-7);
    }else{
        if(position.y > 7)
            return abs(position.x-7) + abs(position.y-8);
        else
            return abs(position.x-7) + abs(position.y-7);
    }
}

void getCellType(CellEnv *cellEnv){
    //compile the CellEnv by running the sensors
}

void getPosition(Position *position, Mouse *mouse){
    position->x = mouse->position->x;
    position->y = mouse->position->y;
}

int findDir(Mouse *mouse, Node currNode, Position position, int dir){
    CellEnv cellEnv;

    //find directions with open walls
    getCellType(&cellEnv);

    //determine hammingDist of each direction
    for(int i = 0; i < 4; i++){
        //if direction has no wall and is not blocked in memory
        if(cellEnv.bounds[0][i] == 1 && currNode.neighbors[i].getPath() != FALSE){
            //if direction is not from where the mouse came from
            if(dir != i)
                cellEnv.bounds[1][i] = this.findHammingDist(position, i);
            else
                cellEnv[1][i] = -1;
        }else{//if direction has wall
            cellEnv[1][i] = -1;
        }
    }

    //chose direction/neighbor cell with smallest Hamming distance
    int bestDir = 0;
    int unknownBool = FALSE;  //tally of paths/directions previously visited

    //init direction is a valid direction
    for(int i = 3; i >= 0 && unknownBool == FALSE; i--){
        bool accessible = currNode.neighbors[i].getPath();
        //isn't already blocked off in memory and isn't a wall
        if(accessible != FALSE && cellEnv.bounds[1][i] != -1){
            //not visited
            if(accessible == UNKNOWN){
                bestDir = i;
                unknownBool = TRUE;
            }else if(accessible == TRUE && unknownBool == FALSE){
                //visited && no unvisited paths found yet
                bestDir = i;
            }
        }
    }

    //strictly choose among unknown open paths
    if(unknownBool == TRUE){
        for(int i = 0;i < 4; i++){
            //if dir's hamming dist is closer to center than the bestDir
            if(cellEnv.bounds[1][i] < cellEnv.bounds[1][bestDir] &&
                cellEnv.bounds[1][i] != -1 && currNode.neighbors[i].getPath() == UNKNOWN){
                bestDir = i;
            }
        }
        
    //strictly choose on known open paths
    }else{
        for(int i = 0; i < 4; i++){
            //if dir's hamming dist is closer to center than the bestDir
            if(cellEnv.bounds[1][i] < cellEnv.bounds[1][bestDir] && cellEnv.bounds[1][i] != -1){
                bestDir = i;
            }
        }
    }

    return bestDir;

 }
