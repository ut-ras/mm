#ifndef _ALGO_H
#define _ALGO_H

#include <string>

using namespace std;

class Algo{
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
        bool hasRotated;
        int retDir;
        int rotation;
        int choice;
        int currX;
        int currY;
        int currDir;
    public:
        Algo();
        int* decide();
        void getCheck(bool inp[3]);
};
#endif
