#include "Node.h"
#include "Neighbor.h"
#include <stdio.h> //uncomment when unit testing

void printNode(Node *node);
void printNeighbor(Neighbor *neighbor);

int main(){
    printf("Hello world\n");

    //Node instantiate testing
    Node myNode;
    Position myPosition = {10, 20};
    initNode(&myNode, 1, myPosition);
    printNode(&myNode);

    //Neighbor edit testing
    Neighbor myNeighbors[4];
    getNeighbors(&myNode, myNeighbors);
    setNeighborId(&myNeighbors[0], 1);
    setPath(&myNeighbors[1], 1);
    setDistance(&myNeighbors[2], 23);
    for(int i = 0; i < 4; i++){
        printNeighbor(&myNeighbors[i]);
    }


    return 0;
}

void printNode(Node *node){
    printf("Node ID: %i\tPosition: %i;%i\n",
        node->id, node->position.x, node->position.y);
    for(int i = 0; i <4; i++){
        printf("Neighbor[%i]: ", i);
        printNeighbor(&(node->neighbors[i]));

    }
}

void printNeighbor(Neighbor *neighbor){
    printf("ID: %d\tPath: %d\tDist: %d\n",
        neighbor->id, neighbor->pathBool, neighbor->distance);
}
