/**
 * Neighbor.c
 * Author: Matthew Yu
 * Last modified: 11/30/18
 *
 * This file defines the function definitions declared in Neighbor.h.
 * 11/30/18 - Neighbor basic functionality tested, works
 **/
#include "Neighbor.h"
// #include <stdio.h> //uncomment when unit testing

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
//
// int test_neighbor(){
//     Neighbor myNeighbor;
//     initNeighbor(&myNeighbor, 2, false, 15);
//     printf("id:%s\n", getPath(&myNeighbor) ? "true" : "false");
//     setPath(&myNeighbor, true);
//     printf("new id:%s\n", getPath(&myNeighbor) ? "true" : "false");
//     return 0;
// }
