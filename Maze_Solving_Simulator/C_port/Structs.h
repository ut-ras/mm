/**
 * Structs.h
 * Author: Matthew Yu
 * Last Modified: 11/30/18
 *
 * This file describes structures used for the "class" definitions of
 * the other classes in MM.
 **/
#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Position{
    int X;
    int Y;
}Position;

typedef struct Location{
    Position position;
    int mvDst;
    int dirEntered;
}Location;

/**
 *  N  E  S  W
 * [ ][ ][ ][ ] <- open or not (1 - no wall, 0 - wall)
 * [ ][ ][ ][ ] <- hamming dist from pos to center of field
 * int numOpen - number of paths open
 **/
typedef struct CellEnv{
    int bounds[2][4];
    int numOpen;
}CellEnv;

#endif
