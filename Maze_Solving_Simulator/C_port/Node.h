/**
 * Node.h
 * Author: Matthew Yu
 * Last modified: 11/30/18
 *
 * This file describes the Node class and the functions that it uses.
 * The Node object. This variable is exported to the global namespace.
 * API is made available through this object.
 **/
#ifndef NODE_H
#define NODE_H
#include "Structs.h"
#include "Neighbor.h"

/**
 * @class Mouse: the relationship between two nodes.
 * @param position - grid cell position of mouse
 * @param heading - direction the mouse is facing
 **/
typedef struct Node{
    int id;
    Position position;
    Neighbor neighbors[4];
}Node;

void initNode(Node *node, int id, Position position);

/**
 * @function getID
 * @param node : Node
 *      reference of the node to get ID from
 **/
int getID(Node *node);

/**
 * @function getPosition
 * @param node : Node
 *      reference of the node to get position from
 * @return position : Position
 **/
Position getNodePosition(Node *node);

/**
 * @function getNeighbors - gets individual Neighbors
 * @param node : Node
 *      referene of the node to get neighbors from
 * @param neighborArr[4] : Neighbors[]
 *      pass by reference array to fill with Neighbor data
 **/
void getNeighbors(Node *node, Neighbor neighborArr[4]);

/**
 *  @function addRelation - given the previous and newly reached node,
 *     adjust the node to add or prune connections.
 *  @param prevNode : Node
 *     the previous node that the mouse was just at.
 *  @param currNode : Node
 *     the node that the mouse has currently reached
 *  @param dirLeft : int
 *     the direction that the mouse left from the PREVIOUS node.
 *  @param dirEntered : int
 *     the direction that the mouse entered into the CURRENT node.
 *  @param mvDist : int
 *     the distance between the two nodes in travel displacement
 **/
void addRelation(Node *prevNode, Node *currNode, int dirLeft, int dirEntered, int mvDst);

/*wrapper functions defined for low level moving of the mouse and determining
heading here?*/



#endif
