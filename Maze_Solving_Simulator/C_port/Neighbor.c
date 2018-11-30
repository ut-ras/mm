/**
 * Neighbor.c
 * Author: Matthew Yu
 * Last modified: 11/30/18
 *
 * This file defines the function definitions declared in Neighbor.h.
 **/
#include "Neighbor.h"

void Neighbor(Neighbor *neighbor, int id, bool pathBool, int distance){
    neighbor->id = id;
    neighbor->pathBool = pathBool;
    neighbor->distance = distance;
}
