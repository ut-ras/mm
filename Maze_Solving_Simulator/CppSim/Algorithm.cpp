#include "Algorithm.h"
#include <iostream>
#include <ostream>

Algorithm::Algorithm() {
    populateMap();
    hasRotated = false;
    currX = 0;
    currY = 0;
    prevX = 0;
    prevY = 0;
    currDir = 1;
    dendrev = false;
}

void Algorithm::populateMap() {
    for(int i = 0; i < 16; i++){
        hamDist[0][i] = top[i];
    }
    for(int i = 1; i < 8; i++){
        for(int j = 0; j < 16; j++){
            hamDist[i][j] = hamDist[i-1][j] - 1;
        }
    }
    for(int i = 0; i < 16; i++){
        hamDist[8][i] = hamDist[7][i];
    }
    for(int i = 9; i < 16; i++){
        for(int j = 0; j < 16; j++){
            hamDist[i][j] = hamDist[i-1][j] + 1;
        }
    }
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
            juncDir[i][j] = -1;
        }
    }
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
            hist[i][j] = 0;
        }
    }
}

void Algorithm::getCheck(bool inp[3], int inp2[3]) {
    openF = inp[0] == 0;
    openR = inp[1] == 0;
    openL = inp[2] == 0;
    prevX = currX;
    prevY = currY;
    currX = inp2[0];
    currY = inp2[1];
    if(inp2[2] == 90.0){
        currDir = 1;
    }
    else if (inp2[2] == 180.0){
        currDir = 2;
    }
    else if(inp2[3] == 270.0){
        currDir = 3;
    }
    else{
        currDir = 0;
    }
}

int Algorithm::numPath() {
    int i = 0;
    if(openF){i++;}
    if(openR){i++;}
    if(openL){i++;}
    return i;
}

void Algorithm::moveCorr() {
    if(!hasRotated){
        if(openF){
            retDir = currDir;
            choice = 0;
            hasRotated = false;
        }
        else if(openL){
            rotation = 90;
            choice = 2;
            hasRotated = true;
        }
        else if(openR){
            rotation = -90;
            choice = 2;
            hasRotated = true;
        }
    }
}

void Algorithm::dEnd() {
    if(!hasRotated){
        rotation = 180;
        choice = 2;
        hasRotated = true;
    }
    dendrev = true;
}

void Algorithm::chooseDir() {
    if(dendrev){
        dendrev = false;
        hamDist[prevX][prevY] = 100;
    }
    int maxVal = 99;
    switch(currDir){
        case 0:
            if(openF){
                if(hamDist[currX + 1][currY] < maxVal) {
                    retDir = currDir;
                    choice = 0;
                    hasRotated = false;
                    maxVal = hamDist[currX + 1][currY];
                }
            }
            if(openL){
                if(hamDist[currX][currY + 1] < maxVal) {
                    rotation = 90;
                    choice = 2;
                    hasRotated = true;
                    maxVal = hamDist[currX + 1][currY];
                }
            }
            if(openR){
                if(hamDist[currX][currY - 1] < maxVal) {
                    rotation = -90;
                    choice = 2;
                    hasRotated = true;
                }
            }
        case 1:
            if(openR){
                if(hamDist[currX + 1][currY] < maxVal) {
                    rotation = -90;
                    choice = 2;
                    hasRotated = true;
                    maxVal = hamDist[currX + 1][currY];
                }
            }
            if(openF){
                if(hamDist[currX][currY + 1] < maxVal) {
                    retDir = currDir;
                    choice = 0;
                    hasRotated = false;
                    maxVal = hamDist[currX][currY + 1];
                }
            }
            if(openL){
                if(hamDist[currX - 1][currY] < maxVal) {
                    rotation = 90;
                    choice = 2;
                    hasRotated = true;
                }
            }
        case 2:
            if(openR){
                if(hamDist[currX][currY + 1] < maxVal) {
                    rotation = -90;
                    choice = 2;
                    hasRotated = true;
                    maxVal = hamDist[currX][currY + 1];
                }
            }
            if(openF){
                if(hamDist[currX - 1][currY] < maxVal) {
                    retDir = currDir;
                    choice = 0;
                    hasRotated = false;
                    maxVal = hamDist[currX - 1][currY];
                }
            }
            if(openL){
                if(hamDist[currX][currY - 1] < maxVal) {
                    rotation = 90;
                    choice = 2;
                    hasRotated = true;
                }
            }
        default:
            if(openL){
                if(hamDist[currX + 1][currY] < maxVal) {
                    rotation = 90;
                    choice = 2;
                    hasRotated = true;
                    maxVal = hamDist[currX + 1][currY];
                }
            }
            if(openR){
                if(hamDist[currX - 1][currY] < maxVal) {
                    rotation = -90;
                    choice = 2;
                    hasRotated = true;
                    maxVal = hamDist[currX - 1][currY];
                }
            }
            if(openF){
                if(hamDist[currX][currY - 1] < maxVal) {
                    retDir = currDir;
                    choice = 0;
                    hasRotated = false;
                }
            }
    }
}

int* Algorithm::decide() {
    if(hamDist[currX][currY] == 0){
        return 0;
    }
    if(hasRotated){
        retDir = currDir;
        choice = 0;
        hasRotated = false;
    }
    else{
        if(numPath() == 0){
            dEnd();
        }
        else if(numPath() == 1){
            moveCorr();
        }
        else{
            chooseDir();
        }
    }
    if(!hasRotated){
        out[0] = choice;
        out[1] = retDir;
    }
    else{
        out[0] = choice;
        out[1] = rotation;
        hasRotated = false;
    }
    cout << "Internal Algo Pos (X|Y|dir): " << currX << "|" << currY << "|" << currDir << endl;
    cout << "Decision: " << out[0] << "|" << out[1] << endl;
    return out;
}

void Algorithm::printMaze(){
    int i = 0;  // future print the maze
}
