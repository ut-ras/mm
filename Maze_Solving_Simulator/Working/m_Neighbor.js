/**
 * m_Neighbor.js
 * Author: Matthew Yu
 * Last modified: 10/24/18
 *
 * This file describes the Neighbor class and the functions that it uses.
 */
 /**
  * @class neighbor: the relationship between two nodes.
  * @param _id - id number of the connected node.
  * @param _pathBool - whether or not a path exists to a node.
  *     1 = no wall, 0 = wall, -1 = unexplored
  * @param _distance - the distance between nodes (in unit hamming distance cells).
  */
class Neighbor{
    constructor(id = 0, pathBool = -1, distance = 0){
        this.id = id;
        this.pathBool = pathBool;
        this.distance = distance;
    }
    getNeighborId(){
        return this.id;
    }
    getAccessible(){
        return this.pathBool;
    }
    getDistance(){
        return this.distance;
    }
    setNeighborId(id){
        this.id = id;
    }
    setNeighborPath(pathBool){
        this.pathBool = pathBool;
    }
    setNeighborDist(distance){
        this.distance = distance;
    }
}
