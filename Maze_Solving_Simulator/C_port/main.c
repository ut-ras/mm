#include "Node.h"
#include "Neighbor.h"
#include "Mouse.h"
#include <stdio.h> //uncomment when unit testing

#define NORTH   0
#define EAST    1
#define SOUTH   2
#define WEST    3
#define MAX_NODES 256 //if the entire 16x16 field has no walls

const int ROWS = 16, COLS = 16;
const int GOAL_POS[4][2] = {{7,8}, {8,8}, {8,7}, {7,7}};

void printNode(Node *node);
void printNeighbor(Neighbor *neighbor);

int main(){
    //build a new mouse and a node
    Mouse mouse;
    Node nodeList[MAX_NODES];
    Node newNode;
    int id = 1;
    int dirLeft = NORTH;
    int dirEntered = NORTH;
    int mvDst = 0;

    Position initPos = {0, 15};
    initMouse(&mouse, initPos, NORTH);
    initNode(&nodeList[id], id, initPos);

    //check node test
    printNode(&nodeList[id]);

    //Neighbor edit testing
    Neighbor myNeighbors[4];
    getNeighbors(&nodeList[id], myNeighbors);
    setNeighborId(&myNeighbors[0], 1);
    setPath(&myNeighbors[1], 1);
    setDistance(&myNeighbors[2], 23);
    for(int i = 0; i < 4; i++){
        printNeighbor(&myNeighbors[i]);
    }
    id++;

    //check position test
    Position outPos;
    getPosition(&outPos, &mouse);
    printf("Mouse position (x;y): %i;%i\n",
        outPos.x, outPos.y);

    //move test
    dirLeft = NORTH;
    mvDst = 0;
    move(&mouse, NORTH);
    move(&mouse, NORTH);
    move(&mouse, EAST);
    mvDst = 3;
    dirEntered = (EAST+2)%4;
    printf("Expected position: 1;13\n");
    getPosition(&outPos, &mouse);
    printf("Mouse position (x;y): %i;%i\n",
        outPos.x, outPos.y);

    //add a new node test
    initNode(&nodeList[id], id, outPos);
    //check node test
    printNode(&nodeList[id]);

    //addrelations basic test
    printf("left:%i; entered:%i\n", dirLeft, dirEntered);
    addRelation(&nodeList[id-1], &nodeList[id], dirLeft, dirEntered, mvDst);
    //check node test
    printNode(&nodeList[id-1]);
    printNode(&nodeList[id]);

    id++;

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


int main_o(){
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
