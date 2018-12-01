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

 void initMouse(Mouse *mouse, int posX, int posY, int heading){
     mouse->position->x = posX;
     mouse->position->y = posY;
     mouse->heading = heading;
 }

 void move(Mouse *mouse, int activeDir){
     let facing = heading();
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
     getCellType(&cellEnv);

     Neighbors neighbors[4];
     getNeighbors(&currNode, neighbors);

     //determine hammingDist of each direction
     for(int i = 0; i < 4; i++){
         //if direction has no wall or is unvisited
         if(cellEnv.bounds[0][i] == 1 && neighbors[i].getAccessible() != 0){
             //if direction is not from where the mouse came from
             if(dir != i)
         }
     }
 }
