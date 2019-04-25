#include <iostream>

#include "Algo.h"

using namespace std;

Algo::Algo() {
    populateMap();
    hasRotated = false;
    currX = 0;
    currY = 0;
    currDir = 1;
}

void Algo::populateMap() {
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

void Algo::getCheck(bool *inp) {
    openF = inp[0];
    openR = inp[1];
    openL = inp[2];
}

int Algo::numPath() {
    int i = 0;
    if(openF){i++;}
    if(openR){i++;}
    if(openL){i++;}
    return i;
}

void Algo::moveCorr() {
    if(!hasRotated){
        if(openF){
            retDir = 1;
            choice = 0;
            hasRotated = false;
        }
        else if(openL){
            rotation = 45;
            currDir = (currDir + 1) % 4;
            choice = 2;
            hasRotated = true;
        }
        else if(openR){
            rotation = -45;
            currDir = (currDir - 1) % 4;
            choice = 2;
            hasRotated = true;
        }
    }
}

void Algo::dEnd() {
    if(!hasRotated){
        rotation = 180;
        currDir = (currDir + 2) % 4;
        choice = 2;
        hasRotated = true;
    }
}

void Algo::chooseDir() {
        int maxVal = 99;
        switch(currDir){
            case 0:
                if(openF){
                    if(hamDist[currX + 1][currY] < maxVal) {
                        retDir = 1;
                        choice = 0;
                        hasRotated = false;
                        maxVal = hamDist[currX + 1][currY];
                    }
                }
                if(openL){
                    if(hamDist[currX][currY + 1] < maxVal) {
                        rotation = 45;
                        currDir = (currDir + 1) % 4;
                        choice = 2;
                        hasRotated = true;
                        maxVal = hamDist[currX + 1][currY];
                    }
                }
                if(openR){
                    if(hamDist[currX][currY - 1] < maxVal) {
                        rotation = -45;
                        currDir = (currDir - 1) % 4;
                        choice = 2;
                        hasRotated = true;
                    }
                }
            case 1:
                if(openR){
                    if(hamDist[currX + 1][currY] < maxVal) {
                        rotation = -45;
                        currDir = (currDir - 1) % 4;
                        choice = 2;
                        hasRotated = true;
                        maxVal = hamDist[currX + 1][currY];
                    }
                }
                if(openF){
                    if(hamDist[currX][currY + 1] < maxVal) {
                        retDir = 1;
                        choice = 0;
                        hasRotated = false;
                        maxVal = hamDist[currX][currY + 1];
                    }
                }
                if(openL){
                    if(hamDist[currX - 1][currY] < maxVal) {
                        rotation = 45;
                        currDir = (currDir + 1) % 4;
                        choice = 2;
                        hasRotated = true;
                    }
                }
            case 2:
                if(openR){
                    if(hamDist[currX][currY + 1] < maxVal) {
                        rotation = -45;
                        currDir = (currDir - 1) % 4;
                        choice = 2;
                        hasRotated = true;
                        maxVal = hamDist[currX][currY + 1];
                    }
                }
                if(openF){
                    if(hamDist[currX - 1][currY] < maxVal) {
                        retDir = 1;
                        choice = 0;
                        hasRotated = false;
                        maxVal = hamDist[currX - 1][currY];
                    }
                }
                if(openL){
                    if(hamDist[currX][currY - 1] < maxVal) {
                        rotation = 45;
                        currDir = (currDir + 1) % 4;
                        choice = 2;
                        hasRotated = true;
                    }
                }
            default:
                if(openL){
                    if(hamDist[currX + 1][currY] < maxVal) {
                        rotation = 45;
                        currDir = (currDir + 1) % 4;
                        choice = 2;
                        hasRotated = true;
                        maxVal = hamDist[currX + 1][currY];
                    }
                }
                if(openR){
                    if(hamDist[currX - 1][currY] < maxVal) {
                        rotation = -45;
                        currDir = (currDir - 1) % 4;
                        choice = 2;
                        hasRotated = true;
                        maxVal = hamDist[currX - 1][currY];
                    }
                }
                if(openF){
                    if(hamDist[currX][currY - 1] < maxVal) {
                        retDir = 1;
                        choice = 0;
                        hasRotated = false;
                    }
                }
        }
}

int* Algo::decide() {
    if(hasRotated){
        retDir = 1;
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
        switch(currDir){
            case 0:
                currX++;
            case 1:
                currY++;
            case 2:
                currX--;
            default:
                currY--;
        }
    }
    if(!hasRotated){
        out[0] = choice;
        out[1] = retDir;
    }
    else{
        out[0] = choice;
        out[1] = rotation;
    }
    return out;
}