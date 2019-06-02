#include "mouse.h"
#include "Algorithm.h"


bool iterateStep();

Mouse* mouse;
Algorithm* algo;
extern "C" void app_main(void) {
	mouse = new Mouse();
	algo = new Algorithm();

	while(iterateStep());
}

bool iterateStep(){
	bool check[3] = {(mouse->getWallCheck())[0], (mouse->getWallCheck())[1], (mouse->getWallCheck())[2]};
	int mousePos[5] = {mouse->getPositionX(), mouse->getPositionY(), (int) mouse->getHeading(), (mouse->getMouseChange())[0], (mouse->getMouseChange())[1]};
	
	algo->getCheck(check, mousePos);
	int* decision = algo->decide();

	switch(decision[0]){
		case 0:		// move forward until junction is found
			mouse->moveUntilJunct();
			break;
		case 2:		// rotate, N degrees
			mouse->rotate(decision[1]);
			break;
		case 3:		// end condition is met
			return false;
		default:	// error output
			return false;
	}
	return true;
}
