#include "mouse.h"
#include "hal/inc/nav.h"
#define FORWARD_TICKS 100
#define MOTOR_SPEED 8.0
Mouse::Mouse(){
	x = 0;
	y = 15;	// bottom left corner
	heading = 90;	// due north
}

Mouse::Mouse(int x, int y, int heading){
	this->x = x;
	this->y = y;
	this->heading = heading;
}

void Mouse::moveUntilJunct(){
	int x_old = x, y_old = y;
	struct movement_info movement;
	
	movement = moveCenter(MOTOR_SPEED);
	// returns movement_info struct.

	// adjust internal position
	switch(heading){
		case 0:	// east, +x
			x += movement.ticksTraveled;
			break;
		case 90: // north, -y
			y -= movement.ticksTraveled;
			break;
		case 180: // west, -x
			x -= movement.ticksTraveled;
			break;
		case 270: // south, +y
			y += movement.ticksTraveled;
			break;
	}
	// adjust wallCheck (left, front, right)
	wallCheck[0] = movement.left;	// TRUE IF PATH
	wallCheck[1] = movement.front;
	wallCheck[2] = movement.right;
	// adjust mouseChange[3] (x_change, y_change, heading_change)
	mouseChange[0] = x - x_old;
	mouseChange[1] = y - y_old;
	mouseChange[2] = heading;	// expect no change to heading
}

// unused as of right now
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
			break;
	}
}

void Mouse::rotate(int degrees){
	// if I turn 90+300 degrees, I return to 30 abs degrees.
	heading = fmod(heading + degrees + 360, 360);
	switch(degrees){
		case 0:
		default:
			break;
		case 90:
			turnCenter(speed);
			break;
		case 180:
			turn180Center(speed);
			break;
		case 270:
			turnCenter(-speed);
			break;
	}
}

bool Mouse::checkFront(){
	return false;	// return getWalls.front;
}

bool Mouse::checkLeft(){
	return false;	// return getWalls.left;
}

bool Mouse::checkRight(){
	return false;	// return getWalls.right;
}

int Mouse::getPositionX(){
	return x;
}

int Mouse::getPositionY(){
	return y;
}

int Mouse::getHeading(){
	return heading;
}
