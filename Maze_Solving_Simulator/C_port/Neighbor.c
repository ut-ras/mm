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
// #define TRUE 1
// #define FALSE 0
// #define UNKNOWN -1

void initNeighbor(Neighbor *neighbor, int id, int pathBool, int distance){
    neighbor->id = id;
    neighbor->pathBool = pathBool;
    neighbor->distance = distance;
}

void setNeighborId(Neighbor *neighbor, int _id){
    neighbor->id = _id;
}

void setPath(Neighbor *neighbor, int _path){
    neighbor->pathBool = _path;
}

void setDistance(Neighbor *neighbor, int _dist){
    neighbor->distance = _dist;
}



// int main(){
//     Neighbor myNeighbor;
//     initNeighbor(&myNeighbor, 2, UNKNOWN, 15);
//     printf("id:%i\n", getPath(&myNeighbor));
//     setPath(&myNeighbor, FALSE);
//     printf("new id:%i\n", getPath(&myNeighbor));
//     return 0;
// }
