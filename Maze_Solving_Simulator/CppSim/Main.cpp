#include "Simulator.h"
#include <iostream>
#include <ostream>

int main(int argc, char* argv[]){
    cout << "Hello World I compile!" << endl;
    if(argv[1] != nullptr){
        cout << "Arguments passed.." << endl;
        std:string fileName(argv[1]);
        Simulator* sim = new Simulator(fileName);
        sim->printTotalMaze();
        cout << "End Load Maze test 1." << endl;
        delete sim;
    }
    return 0;
}
