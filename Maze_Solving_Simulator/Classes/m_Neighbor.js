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
  *     1 = no wall, 0 = wall
  * @param _distance - the distance between nodes (in unit hamming distance cells).
  */
var Neighbor = function(_id, _pathBool, _distance){
    var id = _id;
    var pathBool = _pathBool;
    var distance = _distance;

    //private functions
    //var functionName = function () { /*stuff in here*/ };

    //public functions
    return{
        getNeighborId : function(){
            return id;
        }
        getAccessible : function(){
            return pathBool;
        }
        getDistance : function(){
            return distance;
        }

        setNeighborId : function( _id ){
            id = _id;
        }
        setNeighborPath : function( _pathBool ){
            pathBool = _path;
        }
        setNeighborDist : function( _distance){
            distance = _distance;
        }

    }
}
