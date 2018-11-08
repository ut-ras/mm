/**
 * m_Node.js
 * Author: Matthew Yu
 * Last modified: 10/24/18
 *
 * This file describes the Node class and the functions that it uses.
 * The Node object. This variable is exported to the global namespace.
 * API is made available through this object.
 *
 */
/**
 * @class node: the junction and its relationship to the maze.
 * @param _id - id number of the node.
 * @param _position - the cell position in X,Y format.
 * @param _neighbors - north, east, south, west: Neighbor objects.
 *     default neighbor objects are null (unexplored).
 */
class Node{
    constructor(id = 0, position = [15, 0], neighbors = [new Neighbor(), new Neighbor(), new Neighbor(), new Neighbor()]){
        this.id = id;
        this.position = position;
        this.neighbors = neighbors;
    }
    getID(){
        return this.id;
    }
    getPosition(){
        return this.position;
    }
    getNeighbors(){
        return this.neighbors;
    }
    /**
     *  @function addRelation - given the previous and newly reached node,
     *     adjust the node to add connections or prune the wall.
     *  @param prevNode (implicit) : Node
     *     the previous Node that the mouse was just at.
     *     NOTE: call this function like prevNode.addRelation(currNode, ...)
     *  @param currNode : Node
     *     the node that the mouse has currently reached
     *  @param dirLeft : int
     *     the direction that the mouse left from the previous node.
     *  @param dirEntered : int
     *     the direction that the mouse entered into the current node.
     *  @param mvDist : int
     *     the distance between the two nodes in travel displacement
     */
    addRelation(currNode, dirLeft, dirEntered, mvDist){
        if(this.id == currNode.id){
            //default pathBool is open, set to closed (0) if return to node
            this.neighbors[dirLeft].setNeighborPath(0);
            this.neighbors[dirEntered].setNeighborPath(0);
        }else{
            this.neighbors[dirLeft].setNeighborId(currNode.id);
            this.neighbors[dirLeft].setNeighborDist(mvDist);
            currNode.neighbors[dirEntered].setNeighborId(this.id);
            currNode.neighbors[dirEntered].setNeighborDist(mvDist);
            //set path to previously visited
            this.neighbors[dirLeft].setNeighborPath(1);
            currNode.neighbors[dirEntered].setNeighborPath(1);
        }
    }
}
