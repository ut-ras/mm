/**
 * Neighbor.h
 * Author: Matthew Yu
 * Last modified: 11/30/18
 *
 * This file describes the Neighbor class and the functions that it uses.
 **/
#ifndef NEIGHBOR_H
#define NEIGHBOR_H

/**
 * @class Neighbor: the relationship between two nodes.
 * @param id - id number of the connected node.
 * @param pathBool - whether or not a path exists to a node.
 *     1 = no wall, 0 = wall, -1 = unexplored
 * @param distance - the distance between nodes (in unit hamming distance cells).
 **/
typedef struct Neighbor{
    int id;
    int pathBool;
    int distance;
}Neighbor;

/**
 * Use:
 * Neighbor myNeighbor;
 * initNeighbor(&myNeighbor, id, pathBool, distance);
 **/
void initNeighbor(Neighbor *neighbor, int id, int pathBool, int distance);

/**
 * @function getNeighborId
 * @param neighbor : Neighbor
 *      reference of the neighbor to get ID from
 * @return id : int
 **/
int getNeighborId(Neighbor *neighbor);

/**
 * @function getPath
 * @param neighbor : Neighbor
 *      reference of the neighbor to get pathBool from
 * @return pathBool : bool
 *      1 - path exists; 0 - wall exists; -1 - unknown
 **/
int getPath(Neighbor *neighbor);

/**
 * @function getDistance
 * @param neighbor : Neighbor
 *      reference of the neighbor to get distance from
 * @return distance : int
 *      distance to the connecting node, if any (else 0)
 **/
int getDistance(Neighbor *neighbor);

/**
 * @function setNeighborId
 * @param neighbor : Neighbor
 *      reference of the neighbor to set ID
 * @param id : int
 *      id to set
 **/
void setNeighborId(Neighbor *neighbor, int _id);

/**
 * @function setPath
 * @param neighbor : Neighbor
 *      reference of the neighbor to set pathBool
 * @param path : bool
 *      pathBool to set
 **/
void setPath(Neighbor *neighbor, int _path);

/**
 * @function setDistance
 * @param neighbor : Neighbor
 *      reference of the neighbor to set distance
 * @param dist : int
 *      distance to set
 **/
void setDistance(Neighbor *neighbor, int _dist);

#endif
