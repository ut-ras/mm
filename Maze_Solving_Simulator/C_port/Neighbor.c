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

int getNeighborId(Neighbor *neighbor){
    return neighbor->id;
}

int getPath(Neighbor *neighbor){
    return neighbor->pathBool;
}

int getDistance(Neighbor *neighbor){
    return neighbor->distance;
}

void setNeighborId(Neighbor *neighbor, int id){
    neighbor->id = id;
}

void setPath(Neighbor *neighbor, int path){
    neighbor->pathBool = path;
}

void setDistance(Neighbor *neighbor, int dist){
    neighbor->distance = dist;
}



// int main(){
//     Neighbor myNeighbor;
//     initNeighbor(&myNeighbor, 2, UNKNOWN, 15);
//     printf("id:%i\n", getPath(&myNeighbor));
//     setPath(&myNeighbor, FALSE);
//     printf("new id:%i\n", getPath(&myNeighbor));
//     return 0;
// }
