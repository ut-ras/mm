#pragma once

#include <string>
#include <iostream>
#include <queue>
#include <stack>
#define DEAD_END 99
using namespace std;

struct Point{
    int x;
    int y;
};

class Algorithm{
    private:
        int tremauxMap[16][16][5];  // move history, east, north, west, south wall check
        int solutionMap[16][16];
        std::stack<Point> solution;
	int out[2];

        bool openL = false, openF = false, openR = false;
        bool dEnd = false;

        int currX = 0, currY = 15;   // current position
        int prevX = 0, prevY = 15;   // old position
        int currDir = 1, prevDir = 1;

        void populateMap();
        void mvCorr();
        void mvDEnd();
        void mvJunct();
        int numPath();
        void updateMap();

    public:
        Algorithm();
        int* decide();
        void getCheck(bool* wallCheck, int* mousePos);
        void printMaze();
        std::stack<Point> getShortestPath();
};
