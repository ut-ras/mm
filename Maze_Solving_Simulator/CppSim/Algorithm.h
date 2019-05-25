#pragma once

#include <string>
#include <iostream>
using namespace std;

class Algorithm{
    private:
        int hamDist[16][16];
        int juncDir[16][16];
        int hist[16][16];
        int top[16] = {14,13,12,11,10,9,8,7,7,8,9,10,11,12,13,14};
        int out[2];
        void populateMap();
        void moveCorr();
        void dEnd();
        void chooseDir();
        int numPath();
        bool openF;
        bool openR;
        bool openL;
        bool dendrev;
        bool hasRotated;
        int retDir;
        int rotation;
        int choice;
        int currX;
        int currY;
        int prevX;
        int prevY;
        int currDir;
    public:
        Algorithm();
        int* decide();
        void getCheck(int inp[3], int inp2[3]);
        void printMaze();
};
