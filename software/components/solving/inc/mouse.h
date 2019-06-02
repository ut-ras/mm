/**
 *  Mouse.h (Hardware Mouse)
 *  @Description: This class manages the mouse state and unit movement. Functions
 *  are implemented by sending calls to HAL API.
 *  @Authors: Matthew Yu and Ahmad Ahbab
 *  @Org: Micromouse
 *  @last modified: 6/1/19
 */
#pragma once
// HAL API
#include "hal/inc/nav.h"
#include "solving/inc/Algorithm.h"
#include <math.h>
using namespace std;

class Mouse{
    private:
        // The mouse holds an internal position and heading.
        int speed = 10; // TODO: magic number!!
        int x;
        int y;

	    /* precondition: heading is restricted to 0/90/180/270 deg */
        int heading; /*0 - east, 90 - north, 180 - west, 270 - south*/

        // for purposes of retrieval by the algorithm component.
        bool wallCheck[3];  // left, front, right
        int mouseChange[3]; // x_c, y_c, h_c

    public:
        /**
         *  @Description: Mouse constructor sets up a default mouse at position (0, 15),
         *      facing 90 deg due North.
         */
        Mouse();

        /**
         * Mouse constructor sets up a mouse at position (x, y) facing (n) degrees.
         * @param x       x position in the maze.
         * @param y       y position in the maze.
         * @param heading degrees counterclockwise the mouse is facing.
         */
        Mouse(int x, int y, int heading);

        /**
         * moveUntilIntersection moves the mouse position until it finds a junction (wall in front or multiple paths).
         * sets movement and walls conditions for retrieval.
         **/
        void moveUntilJunct();

        /**
         * getWallCheck
         **/
        bool* getWallCheck(){ return wallCheck; };

        /**
         * getMouseChange
         **/
        int* getMouseChange(){ return mouseChange; };

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
        void rotate(int degrees);

        /**
         * checkFront checks if the sensors detect a wall in front.
         * @return true if a path exists in front, false elsewise
         */
        bool checkFront();

        /**
         * checkLeft checks if the sensors detect a wall to the left.
         * @return true if a path exists to the left, false elsewise
         */
        bool checkLeft();

        /**
         * checkRight checks if the sensors detect a wall to the right.
         * @return true if a path exists to the right, false elsewise
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
         * @return int heading, counterclockwise
         */
        int getHeading();

        void speedRun(std::stack<Point> shortestPath);
};
