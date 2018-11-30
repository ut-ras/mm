/**
 * Neighbor.h
 * Author: Matthew Yu
 * Last modified: 11/30/18
 *
 * This file describes the Neighbor class and the functions that it uses.
 **/
#ifndef NEIGHBOR_H
#define NEIGHBOR_H
#include <stdbool.h>


/**
 * @class Neighbor: the relationship between two nodes.
 * @param id - id number of the connected node.
 * @param pathBool - whether or not a path exists to a node.
 *     1 = no wall, 0 = wall, -1 = unexplored
 * @param distance - the distance between nodes (in unit hamming distance cells).
 **/
typdef struct Neighbor{
    int id;
    bool pathBool;
    int distance;
}Neighbor;

/**
 * Use:
 *
 *
 **/
void Neighbor(Neighbor *neighbor, int id, bool pathBool, int distance);

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
 *      true - path exists; false - wall exists;
 **/
bool getPath(Neighbor *neighbor);

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
void setNeighborId(Neighbor *neighbor, int id);

/**
 * @function setPath
 * @param neighbor : Neighbor
 *      reference of the neighbor to set pathBool
 * @param path : bool
 *      pathBool to set
 **/
void setPath(Neighbor *neighbor, bool path);

/**
 * @function setDistance
 * @param neighbor : Neighbor
 *      reference of the neighbor to set distance
 * @param dist : int
 *      distance to set
 **/
void setDistance(Neighbor *neighbor, int dist);

#endif
