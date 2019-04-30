/**
 *  Mouse.h
 *  @Description: This class manages the mouse state.
 *  The API has two sets of identical functions, simulator-based mouse functions
 *  and real mouse functions.
 *  @Authors: Matthew Yu and Ahmad Ahbab
 *  @Org: Micromouse
 */
#pragma once
#include "Maze.h" // Query function for look API
#include <math.h>
#include <iostream>
using namespace std;

class Mouse{
    private:
        // The mouse holds an internal position and heading.
        int x;
        int y;
        Maze* maze;  // needs a reference to the maze to access queries

	    /* precondition: heading is restricted to 0/90/180/270 deg */
        double heading; /*0 - east, 90 - north, 180 - west, 270 - south*/

        /**
         * @Description: check determines if a cell in a certain heading contains a wall
         *  using the Maze API.
         * @param  double heading_v - heading of the mouse to look at
         * @return  bool - true if wall exists, false elsewise
         */
        bool check(double heading_v);
    public:
        /**
         *  @Description: Mouse constructor sets up a default mouse at position (0, 0),
         *      facing 90 deg due North.
         */
        Mouse(Maze& maze);

        /**
         * Mouse constructor sets up a mouse at position (x, y) facing (n) degrees.
         * @param x       x position in the maze.
         * @param y       y position in the maze.
         * @param heading degrees counterclockwise the mouse is facing.
         */
        Mouse(int x, int y, double heading, Maze& maze);

        /**
         * moveForward moves the mouse position forward relatively by n steps.
         * @param steps number of steps to move forward.
	     */
        void moveForward(int steps);

        /**
         * moveBackward moves the mouse position backward relatively by n steps.
         * @param steps number of steps to move backward.
         */
        void moveBackward(int steps);

        /**
         * rotate shifts the mouse heading relatively by n degrees.
         * @param degrees degrees to rotate left or right.
         */
        void rotate(double degrees);

        /**
         * checkFront checks if the sensors detect a wall in front.
         * @return true if a wall exists in front, false elsewise
         */
        bool checkFront();

        /**
         * checkLeft checks if the sensors detect a wall to the left.
         * @return true if a wall exists to the left, false elsewise
         */
        bool checkLeft();

        /**
         * checkRight checks if the sensors detect a wall to the right.
         * @return true if a wall exists to the right, false elsewise
         */
        bool checkRight();

        /**
         * getPositionX returns the mouse X position in the maze.
         * @return int X position
         */
        int getPositionX();

        /**
         * getPositionY returns the mouse Y position in the maze.
         * @return int Y position
         */
        int getPositionY();

        /**
         * getHeading returns the mouse absolute heading in the maze.
         * @return double heading, counterclockwise
         */
        double getHeading();
};
