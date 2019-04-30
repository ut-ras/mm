/**
 *  Mouse.cpp (Simulator Mouse)
 *  @Description: This class manages the mouse state. Functions
 *  are implemented by sending calls to the Maze API.
 *  @Authors: Matthew Yu and Ahmad Ahbab
 *  @Org: Micromouse
 */
#include "Mouse.h"

Mouse::Mouse(Maze& maze){
	x = 0;
	y = 0;
	heading = 90.0;
	this->maze = &maze;
}

Mouse::Mouse(int x, int y, double heading, Maze& maze){
	this->x = x;
	this->y = y;
	this->heading = heading;
	this->maze = &maze;
}

void Mouse::moveForward(int steps){
	switch((int) heading){
		case 0:
			x += steps;
			break;
		case 90:
			y -= steps;
			break;
		case 180:
			x -= steps;
			break;
		case 270:
			y += steps;
			break;
		default:
			cout << "Invalid restricted heading: " << heading << endl;
			break;
	}
}

void Mouse::moveBackward(int steps){
	switch((int) heading){
		case 0:
			x -= steps;
			break;
		case 90:
			y += steps;
			break;
		case 180:
			x += steps;
			break;
		case 270:
			y -= steps;
			break;
		default:
			cout << "Invalid restricted heading: " << heading << endl;
			break;
	}
}

void Mouse::rotate(double degrees){
	// if I turn 90+300 degrees, I return to 30 abs degrees.
	heading = fmod(heading + degrees, 360);
}

// private sim mouse function that translates chacking for maze queries.
bool Mouse::check(double heading_v){
	switch((int) heading_v){
		case 0:	// East
			return maze->query(x*2+1, y*2);	// scaled by 2 to match 2d maze
		case 90: // North
			return maze->query(x*2, y*2-1);
		case 180: // West
			return maze->query(x*2-1, y*2);
		case 270: // South
			return maze->query(x*2, y*2+1);
		default:
			cout << "Invalid restricted heading: " << heading_v << endl;
			return false;
	}
}

bool Mouse::checkFront(){
	return check(heading);
}

bool Mouse::checkLeft(){
	return check(fmod(heading + 90, 360));
}

bool Mouse::checkRight(){
	return check(heading - 90 + 360);
}

int Mouse::getPositionX(){
	return x;
}

int Mouse::getPositionY(){
	return y;
}

double Mouse::getHeading(){
	return heading;
}
