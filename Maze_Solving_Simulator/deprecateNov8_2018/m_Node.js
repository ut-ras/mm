/**
 * m_Node.js
 * Author: Matthew Yu
 * Last modified: 10/24/18
 *
 * This file describes the Node class and the functions that it uses.
 */

 /**
  * @class node: the junction and its relationship to the maze.
  * @param _id - id number of the node.
  * @param _position - the cell position in X,Y format.
  * @param _neighbors - north, east, south, west: Neighbor objects.
  *     default neighbor objects are null (unexplored).
  */
 var Node = function(_id, _position, _neighbors = [null, null, null, null]){
     var id = _id;
     var position = _position;
     var neighbors = _neighbors;

     //private functions
     //var functionName = function () { /*stuff in here*/ };

     //public functions
     return{
         getId : function(){
             return id;
         }
         getPosition : function(){
             return position;
         }
         getNeighbors : function(){
             return neighbors;
         }

         /**
          *  @function addRelation - given the previous and newly reached node,
          *     adjust the nodeList to add connections or prune the wall.
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
         addRelation : function(currNode, dirLeft, dirEntered, mvDist){
             if(id == currNode.id){
                 neighbors[dirLeft].setNeighborPath(0);
                 neighbors[dirEntered].setNeighborPath(0);
             }else{
                 neighbors[dirLeft].setNeighborId(currNode.id);
                 neighbors[dirLeft].setNeighborDist(mvDist);
                 currNode.neighbors[dirEntered].setNeighborId(prevNode.id);
                 currNode.neighbors[dirEntered].setNeighborDist(mvDst);
             }
         }
     }
 }
