/**
 * Neighbor.c
 * Author: Matthew Yu
 * Last modified: 11/30/18
 *
 * This file defines the function definitions declared in Neighbor.h.
 **/
#include "Neighbor.h"

void initNeighbor(Neighbor *neighbor, int id, bool pathBool, int distance){
    neighbor->id = id;
    neighbor->pathBool = pathBool;
    neighbor->distance = distance;
}

void setNeighborId(Neighbor *neighbor, int _id){
    neighbor->id = _id;
}

void setPath(Neighbor *neighbor, bool _path){
    neighbor->pathBool = _path;
}

void setDistance(Neighbor *neighbor, int _dist){
    neighbor->distance = _dist;
}
