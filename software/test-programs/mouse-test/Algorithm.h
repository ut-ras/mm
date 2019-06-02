#pragma once

#include <string>
#include <iostream>
#include <vector>
#define DEAD_END 99
using namespace std;

typedef struct Decision{
    int param1;
    int param2;
}Decision;

class Algorithm{
    private:
        int hamDist[16][16];
        int tremauxMap[16][16];
        vector<Decision> solution;
        const int top[16] = {14,13,12,11,10,9,8,7,7,8,9,10,11,12,13,14};
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
        std::vector<Decision> getShortestPath();
};
