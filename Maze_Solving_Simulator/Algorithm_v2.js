/**
 * Algorithm_v2.js
 * Created by Matthew Yu
 * Last modified: 10/26/18
 * This is a basic micromouse main loop algorithm to navigate a virtual maze
 * Future version will be ported to C on the ESP32 microcontroller.
 */
let nodes = [];
let currentNode;
let position;
let travelDirection;
let id = 0;

const ROWS = 16, COLS = 16;
const GOAL_POS = [[7,8], [8,8], [8,7], [7,7]]; //top right, ctr-clockwise respectively

function main() {
    //instantiate mouse at bottom left position
    var mouse = new Mouse();
    nodes.push(new Node(id, mouse.getPosition()));
    currentNodeID = id;
    id++;
    position = currentNode.getPosition();
    dirEntered = 'N';
    dirLeft = null;

    /*
        Main exploration loop
        every loop update:
            ~current position
            ~current node ID
            ~nodeList nodes
    */
    do{
        //given the robot position, find the best direction of travel and move
        //along that corridoor till another junction is reached.
        let travelDirection = mouse.findDir(position, dirEntered);
        //newPlace = [newPosition, mvDist]
        let newPlace = mouse.movePath(position, travelDirection);

        //search list of nodes to see if an existing node is reached
        let found = false;
        let foundID = null;
        for (node of nodes){
            //if mouse reached an existing node, add relations
            if (node[1] == newPlace[0]){
                found = true;
                nodes[currentNodeID].addRelation(node, travelDirection, newPlace[2], newPlace[1]);
            }
        }
        //if there is no reached existing node, make a new node and add relations
        if (found == false){
            let newNode = new Node(id, position);
            nodes[currentNodeID].addRelation(newNode, travelDirection, newPlace[2], newPlace[1]);
            nodes.push(newNode);
            id++;
        }

        //set reached node as current node
        currentNodeID = id;
        //set position as new position
        position = newPlace[0];

    }while(position == GOAL_POS[0] || position == GOAL_POS[1] ||
        position == GOAL_POS[2] || position == GOAL_POS[3]);
}
