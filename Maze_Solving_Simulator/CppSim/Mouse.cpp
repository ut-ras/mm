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
	y = 15;	// bottom left corner
	heading = 90.0;	// due north
	this->maze = &maze;
}

Mouse::Mouse(int x, int y, double heading, Maze& maze){
	this->x = x;
	this->y = y;
	this->heading = heading;
	this->maze = &maze;
}

void Mouse::moveForward(int steps){
	heading = fmod(heading+360, 360);
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
			cout << "Mouse::moveForwards(): Invalid restricted heading - " << heading << endl;
			break;
	}
}

void Mouse::moveBackward(int steps){
	heading = fmod(heading+360, 360);
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
			cout << "Mouse::moveBackwards(): Invalid restricted heading - " << heading << endl;
			break;
	}
}

void Mouse::rotate(double degrees){
	// if I turn 90+300 degrees, I return to 30 abs degrees.
	heading = fmod(heading + degrees + 360, 360);
}

// private sim mouse function that translates chacking for maze queries.
bool Mouse::check(double heading_v){
	heading_v = fmod(heading_v+360, 360);
	cout << "heading check: " << heading_v << ":\t";
	bool result;
	// scale coordinates to match maze
	int s_x = x*2 + 1;
	int s_y = y*2 + 1;
	switch((int) heading_v){
		case 0:	// East
			s_x += 1;
			result = maze->query(s_x, s_y);
			break;
		case 90: // North
			s_y -= 1;
			result = maze->query(s_x, s_y);
			break;
		case 180: // West
			s_x -= 1;
			result = maze->query(s_x, s_y);
			break;
		case 270: // South
			s_y += 1;
			result = maze->query(s_x, s_y);
			break;
		default:
			cout << "\tMouse::Check(): Invalid restricted heading - " << heading_v << endl;
			result = false;
			break;	
	}
	cout << "(" << s_x << "|" << s_y << ")";
	if(result)
		cout << "1/PATH" << endl;
	else
		cout << "0/WALL" << endl;
	return result;
}

bool Mouse::checkFront(){
	return check(heading);
}

bool Mouse::checkLeft(){
	return check(heading + 90);
}

bool Mouse::checkRight(){
	return check(heading - 90);
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
