/**
 * Algorithm_v1.js
 * Created by Matthew Yu
 * Last modified: 9/22/18
 * This is a basic micromouse main loop algorithm to navigate a virtual maze
 * (no hardware implementation and thus real sensor methods)
 * Future version will be ported to C on the ESP32 microcontroller.
 * TODO: Complete implementation of the exploration main loop and test and debug.
 */

/**
 * @class node: the junction and its relationship to the maze.
 * @param id - the permanent id number of the node
 * @param coordinate - the cell location in y,x format
 * @param direction - north, east, south, west: relative objects
 */
class Node {
  constructor(id, coordinate = [15, 0], direction = [null, null, null, null]){
    this.id = id;
    this.coordinate = coordinate;
    this.direction = direction;
  }
  getDirection(){}
}

/**
 * @class relative: the relationship between two nodes.
 * @param open - whether a wall exists or not or direction is open or not
 *        1 - direction is open, 0 - not (other two variables are thus -1)
 * @param id - the permanent id number of the node
 * @param distance - the distance between nodes (travel cells)
 */
class Relative {
  constructor(open = 0, id = -1, distance = -1){
    this.open = open;
    this.id = id;
    this.distance = distance;
  }
}

//Global variables and consts
let nodes = [];
let currentNode;
let position;
let travelDirection;

const ROWS = 16, COLS = 16;
const GOAL_POS = [[8,9], [8,8], [9,8], [9,9]]; //top right, ctr-clockwise respectively

function main() {
  //create the first node and set it at the start
  nodes.push(new Node(0, [15,0], [new Relative(), new Relative(), new Relative(), new Relative()]));
  currentNode = 0;
  position = nodes[currentNode][1];

  //main exploration loop
  do{
    //using the sensors, find and pick the direction of travel.
    travelDirection = getDirection();
    //move in travelDirection until a junction is reached
    location = movePath(position, travelDirection);

    //compare position with existing list of nodes to see if we reached a mapped node
      //assumption is that there is a 1:1 path correlation between nodes.
      //if an existing node matches the present position, then no other nodes will.
    let found = false;
    for(node of nodes){
      //if so, edit relatives of src&dst nodes
      if(node[1] === position){
        found = true;

      }
    }
    //if no existing node matches, make a new node and edit relationships
    if(found === false){

      //set new node
      //TODO: figure out current node (since each new discovered node may not be in sequential id order)
      nodes.push(new Node(currentNode, position, [new Relative(), new Relative(), new Relative(), new Relative()]));
    }

    //check if end is reached
  }while(position == GOAL_POS[0] || position == GOAL_POS[1] || position == GOAL_POS[2] || position == GOAL_POS[3]);

    //TODO decide what happens when end is reached, how to go back a different way



  //main run loop
    //given the existing data graph, use cul-de-sac sealer to block off dead loops,
    //dead ends, and unexplored directions.
    //TODO finish this loop
}

//these methods rely on sensor input, not the data structure.
function move(travelDirection){}
function isJunction(position){}



/******************************************************************/

  //link current node to previous node
  nodes[currentNode][2][travelDirection].open = 1;
  nodes[currentNode][2][travelDirection].id = currentNode+1;
  nodes[currentNode][2][travelDirection].distance = mvDist;



/*
Main Algo outline

Explore towards center
Explore back towards start, potentially avoiding explored places
Process map and find shortest path based on priorities
Speed Run along map
