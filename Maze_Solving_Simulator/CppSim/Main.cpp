#include "Simulator.h"
#include <iostream>
#include <ostream>

void loadMazeTest(char* argv[]);
void basicMouseTest();
void comprehensiveMouseTest();
void printMousePosition();

Simulator* sim;
int main(int argc, char* argv[]){
    cout << "Micromouse Simulator 2019." << endl;
    if(argv[1] != nullptr){
        cout << "Arguments passed.." << endl;

        loadMazeTest(argv);
        // basicMouseTest();
        comprehensiveMouseTest();

        delete sim;
    }
    cout << "UT IEEE RAS (2019)." << endl;
    return 0;
}

// show that the maze can be properly generated and displayed.
void loadMazeTest(char* argv[]){
    cout << "Start Load Maze check." << endl;
    std:string fileName(argv[1]);
    sim = new Simulator(fileName);
    sim->printTotalMaze();
    cout << "End Load Maze check." << endl;
}

// show that the mouse exists and can move.
void basicMouseTest(){
    cout << "Start basic Mouse check." << endl;
    printMousePosition();
    cout << "Move right then up one space." << endl;
    Mouse* mouse = sim->getMouse();
    mouse->rotate(-90);
    mouse->moveForward(1);
    mouse->rotate(90);
    mouse->moveForward(1);
    printMousePosition();
    cout << "Spin clockwise (-heading) 270 deg and go backwards two spaces." << endl;
    mouse->rotate(-270);
    mouse->moveBackward(2);
    printMousePosition();
    cout << "Display mouse on field." << endl;
    sim->printTotalMaze();
    cout << "End basic Mouse check." << endl;
}

// show that the mouse can iterate according to the algorithm for 5 steps.
void comprehensiveMouseTest(){
    cout << "Start comprehensive Mouse check." << endl;
    
    printMousePosition();
    sim->run(1);

    for(int i = 0; ; i++){
	cout << "Press any key to continue or q to quit." << endl;
	char c = getchar();
	if(c == 'q')
		return;
	system("clear");

	cout << "Step: " << i+1 << endl;
	printMousePosition();
	sim->run(1);
    }
    
    
    cout << "End comprehensive Mouse check." << endl;

}

void printMousePosition(){
    cout << "--Mouse Info.--" << endl;
    cout << "---------------" << endl;
    Mouse* mouse = sim->getMouse();
    cout << "x: " << mouse->getPositionX() << "\ty: " << mouse->getPositionY()
        << "\th: " << mouse->getHeading() << endl;
    cout << "---------------" << endl;
}
