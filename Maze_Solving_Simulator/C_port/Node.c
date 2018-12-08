/**
 *  Node.h
 *  Author: Matthew Yu
 *  Last modified: 12/7/18
 *  This file defines the function definitions
 **/
#include "Node.h"

 void initNode(Node *node, int id, Position position){
     node->id = id;
     node->position = position;
     for(int i = 0; i < 4; i++){
         node->neighbors[i].id = 0;
         node->neighbors[i].pathBool = -1;
         node->neighbors[i].distance = 0;         
     }
 }

 int getID(Node *node){
     return node->id;
 }

 Position getNodePosition(Node *node){
     return node->position;
 }

 void getNeighbors(Node *node, Neighbor neighborArr[4]){
     for(int i = 0; i < 4; i++){
         neighborArr[i] = node->neighbors[i];
     }
 }

 void addRelation(Node *prevNode, Node *currNode, int dirLeft, int dirEntered, int mvDst){
     if(prevNode->id == currNode->id){
         //close path if mouse returns to node it left
         setPath(&(prevNode->neighbors[dirLeft]), 0);
         setPath(&(prevNode->neighbors[dirEntered]), 0);
     }else if(1 != 0){//some condition){
         int i = 0;
     }else{
         setNeighborId(&(prevNode->neighbors[dirLeft]), currNode->id);
         setDistance(&(prevNode->neighbors[dirLeft]), mvDst);
         setNeighborId(&(currNode->neighbors[dirEntered]), prevNode->id);
         setDistance(&(currNode->neighbors[dirEntered]), mvDst);
         //set path to previously visited
         setPath(&(prevNode->neighbors[dirLeft]), 1);
         setPath(&(currNode->neighbors[dirEntered]), 1);
     }
 }
