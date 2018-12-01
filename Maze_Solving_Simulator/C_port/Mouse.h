/**
 * Mouse.h
 * Author: Matthew Yu
 * Last modified: 11/30/18
 *
 * This file describes the mmouse class and the functions that it uses.
 * This class is dependent on the following classes and their source files:
 *      @class Node m_Node.js
 *      @class Neighbor m_Neighbor.js
 *
 * TODO: Clean up input parameters since some duplicate off class
 **/
#ifndef MOUSE_H
#define MOUSE_H
#include "Structs.h"

/**
 * @class Mouse: the relationship between two nodes.
 * @param position - grid cell position of mouse
 * @param heading - direction the mouse is facing
 **/
typdef struct Mouse{
    Position position;
    int heading;
}Mouse;

void initMouse(Mouse *mouse, int posX, int posY, int heading);

/**
 *  @function move - move the Mouse an arbitrary distance (1 cell)
 *      in a given direction
 *  @param mouse : Mouse
 *      mouse to move
 *  @param activeDir : int
 *     direction to move towards.
 **/
void move(Mouse *mouse, int activeDir);

/**
 *  @function getCellType - uses IR sensors to determine existence of walls
 *      in each Math.absolute direction
 *  @param mouse : Mouse
 *      mouse to move
 *  @return cell_environment : CellEnv
 *      refer to Structs.h.
 **/
void getCellType(CellEnv *cellEnv);

/**
 *  @function findHammingDist - given a position and direction to move towards,
 *     findHammingDist finds the distance to the center of the field.
 *  @param pos : int[2]
 *     (X, Y) coordinate of the mmouse.
 *  @param dir : int
 *     direction of possible travel. 0=N, 1=E, 2=S, 3=W
 *  @return dist : int
 **/
int findHammingDist(Position position, int dir);

/**
 *  @function getPosition
 *  @param mouse : Mouse
 *     mouse to move
 *  @return position : Position
 *     current position of the Mouse
 **/
Position getPosition(Mouse *mouse);

/**
 *  @function findDir - determines the direction the mmouse should travel after
 *     reaching a junction
 *  @param mouse : Mouse
 *     mouse to find direction from
 *  @param currNode : Node()
 *     secondary cell wall input for wall pruning checking
 *  @param pos : int[2]
 *     (x,y) coordinates of the mmouse.
 *  @param dir : int
 *     Math.absolute direction the mmouse entered the current junction from.
 *     0=N, 1=E, 2=S, 3=W
 *  @return int
 *     direction mmouse should now go (0=N, 1=E, 2=S, 3=W)
 **/
int findDir(Mouse *mouse, Node currNode, Position position, int dir);

/**
 *  @function movePath - Move mouse until junction is reached.
 *  @param mouse : Mouse
 *      mouse to move
 *  @param pos : Position
 *     (x,y) coordinates of the mmouse before it starts moving.
 *  @param dir :int
 *     Math.absolute direction the mmouse leaves from the current junction
 *  @return location : Location
 *     location = Location{newPos, moveDist, directionEntered}
 **/
Location movePath(Mouse *mouse, Position position, int dir);

/*wrapper functions defined for low level moving of the mouse and determining
heading here?*/
//return abs direction mouse is facing
int heading();


#endif
