/**
 * JS Implementation of Tremaux's algorithm for IEEE RAS MM
 * Authors: Matthew Yu and Ahmad Ahbab
 * Last Modified: 11/7/18
 * TODO: go over general algorithm and class function requirements
 **/

// clear the driver object.
driver = {};
// CONSTS
const ROWS = 16, COLS = 16;
const GOAL_POS = [[7,8], [8,8], [8,7], [7,7]]; //top right, ctr-clockwise respectively

// global vars
let nodes = [];
let currentNode;
let position;
let travelDirection;
let id = 0;
let dirEntered;
let dirLeft;
let mmouse;


 // boolean. TRUE = go to goal.  FALSE = go home
 driver.goGoal;

 // Gets called only when downloaded to the mouse
 // Performs initialization
 driver.load = function() {
     // default maze
     //mouse.loadMaze("91japa1");
     driver.goGoal = true;

     //main starts here
     mmouse = new Mmouse();
     position = mmouse.getPosition();
     //nodes.push(new Node(id, position));
     currentNode = new Node(0, mmouse.getPosition());
     id++;
     dirEntered = 2;
     dirLeft = null;
     nodes = [];
 }


 // Figure out next move.
 // Gets called each iteration of the simulator.
 driver.next = function() {
     console.log("stepping");
     //given the robot position, find the best direction of travel and move
     //along that corridor till another junction is reached.
     let travelDirection = mmouse.findDir(currentNode, position, dirEntered);
     //newPlace = [newPosition, mvDist, directionEntered]
     let newPlace = mmouse.movePath(position, travelDirection);
     //set position as new position
     position = newPlace[0];
     dirEntered = newPlace[2];

     //search list of nodes to see if an existing node is reached
     let found = false;
     let foundID = null;
     for (node of nodes){
         //if mouse reached an existing node, add relations
         let posC = node.getPosition();
         if (posC[0] == position[0] && posC[1] == position[1]){
             found = true;
             currentNode.addRelation(node, travelDirection, newPlace[2], newPlace[1]);
             currentNode = node;//new Node(node.getID(), node.getPosition(), node.getNeighbors());
             break;
         }
     }
     //if there is no reached existing node, make a new node and add relations
     if (found == false){
         let newNode = new Node(id, position);
         currentNode.addRelation(newNode, travelDirection, newPlace[2], newPlace[1]);
         nodes.push(newNode);
         currentNode = newNode;
         id++;
     }
 }
