#include "Algorithm.h"
#include <iostream>
#include <ostream>

void Algorithm::populateMap() {       // creates hamDist maze
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
        for(int j = 0; j < 16; j++)
            tremauxMap[i][j] = 0;
    }
    tremauxMap[0][15] = -1;
    tremauxMap[7][7] = -1;
    tremauxMap[7][8] = -1;
    tremauxMap[8][7] = -1;
    tremauxMap[8][8] = -1;
}

// emulate moving through corridor in algorithm history
void Algorithm::mvCorr() {            // if only one direction is open, move through corridor
    if(openF){  // dead end, has rotated, move forward.
        out[0] = 0;
        out[1] = 0;
    }else if(openL || openR){   // corner, left or right is open.
        if(openL){  // rotate left
            out[0] = 2;
            out[1] = 90;
        }else{  // rotate right
            out[0] = 2;
            out[1] = -90;
        }
    }else{
        cout << "Algorithm::mvCorr(): Invalid boolean set " << openL << "|" << openF << "|" << openR << endl;
    }
}

// precondition: mvDEnd is not called if the mouse has not moved (prevX|prevY == currX|currY)
void Algorithm::mvDEnd() {            // if no way is open, reverse
    // order a rotation.
    out[0] = 2;
    out[1] = 180;

    tremauxMap[currX][currY] = DEAD_END;
    // set dEnd for blocking out after moving away
    // dEnd = true;
}

void Algorithm::mvJunct() {           // method for dealing with junctions, where >1 paths are open
    // int maxVal = DEAD_END;                  // max hamming distance

    int rotation = 0;
    bool hasRotated = false;
    // first check if there is a priority among tremaux
    int lowestSide = 0; //front
    int lowestVal = 99;
    int front, left, right;
    switch(currDir){
        case 0: // east
            front = tremauxMap[currX + 1][currY];
            left = tremauxMap[currX][currY - 1];
            right = tremauxMap[currX][currY + 1];

            if(openF)                       // front
                lowestVal = front;
            if(right < lowestVal && openR){ // right
                lowestSide = 2;
                lowestVal = right;
            }
            if(left < lowestVal && openL){  // left
                lowestSide = 1;
                lowestVal = left;
            }
            if(lowestSide == 0){
                hasRotated = false;
            }
            else if(lowestSide == 1){
                rotation = 90;
                hasRotated = true;
            }else if(lowestSide == 2){
                rotation = -90;
                hasRotated = true;
            }else{
                cout << "Algorithm::mvJunct(): invalid lowest side error." << endl;
            }
            break;
        case 1: // north
            front = tremauxMap[currX][currY - 1];
            left = tremauxMap[currX - 1][currY];
            right = tremauxMap[currX + 1][currY];

            if(openF)                       // front
                lowestVal = front;
            if(right < lowestVal && openR){ // right
                lowestSide = 2;
                lowestVal = right;
            }
            if(left < lowestVal && openL){  // left
                lowestSide = 1;
                lowestVal = left;
            }
            if(lowestSide == 0){
                hasRotated = false;
            }
            else if(lowestSide == 1){
                rotation = 90;
                hasRotated = true;
            }else if(lowestSide == 2){
                rotation = -90;
                hasRotated = true;
            }else{
                cout << "Algorithm::mvJunct(): invalid lowest side error." << endl;
            }
            break;
        case 2: // west
            front = tremauxMap[currX - 1][currY];
            left = tremauxMap[currX][currY + 1];
            right = tremauxMap[currX][currY - 1];

            if(openF)                       // front
                lowestVal = front;
            if(right < lowestVal && openR){ // right
                lowestSide = 2;
                lowestVal = right;
            }
            if(left < lowestVal && openL){  // left
                lowestSide = 1;
                lowestVal = left;
            }
            if(lowestSide == 0){
                hasRotated = false;
            }
            else if(lowestSide == 1){
                rotation = 90;
                hasRotated = true;
            }else if(lowestSide == 2){
                rotation = -90;
                hasRotated = true;
            }else{
                cout << "Algorithm::mvJunct(): invalid lowest side error." << endl;
            }
            break;
        case 3: // south
            front = tremauxMap[currX][currY + 1];
            left = tremauxMap[currX + 1][currY];
            right = tremauxMap[currX - 1][currY];

            if(openF)                       // front
                lowestVal = front;
            if(right < lowestVal && openR){ // right
                lowestSide = 2;
                lowestVal = right;
            }
            if(left < lowestVal && openL){  // left
                lowestSide = 1;
                lowestVal = left;
            }
            if(lowestSide == 0){
                hasRotated = false;
            }
            else if(lowestSide == 1){
                rotation = 90;
                hasRotated = true;
            }else if(lowestSide == 2){
                rotation = -90;
                hasRotated = true;
            }else{
                cout << "Algorithm::mvJunct(): invalid lowest side error." << endl;
            }
            break;
        default:
            cout << "Algorithm::myJunct(): invalid currDir" << endl;
    }

    // switch(currDir){
    //     case 0:
    //         if(openF){
    //             if(hamDist[currX + 1][currY] < maxVal) {    //when hamming distance for east tile is less than the curr max hamdist
    //                 hasRotated = false;                     //no need to rotate
    //                 maxVal = hamDist[currX + 1][currY];     //sets new maxval to compare and see if anything is lower
    //             }
    //         }
    //         if(openL){
    //             if(hamDist[currX][currY - 1] < maxVal) {
    //                 rotation = 90;
    //                 hasRotated = true;
    //                 maxVal = hamDist[currX][currY - 1];     //set max val
    //             }
    //         }
    //         if(openR){
    //             if(hamDist[currX][currY + 1] < maxVal) {    //and current max hamdist is less than current
    //                 rotation = -90;                          //set rotation to left
    //                 hasRotated = true;                      //set flag for has rotated
    //                 maxVal = hamDist[currX][currY + 1];
    //             }
    //         }
    //         break;
    //     case 1:
    //         if(openF){
    //             if(hamDist[currX][currY - 1] < maxVal) {
    //                 hasRotated = false;
    //                 maxVal = hamDist[currX][currY - 1];
    //             }
    //         }
    //         if(openL){
    //             if(hamDist[currX - 1][currY] < maxVal) {
    //                 rotation = 90;
    //                 hasRotated = true;
    //                 maxVal = hamDist[currX - 1][currY];
    //             }
    //         }
    //         if(openR){
    //             if(hamDist[currX + 1][currY] < maxVal) {
    //                 rotation = -90;
    //                 hasRotated = true;
    //                 maxVal = hamDist[currX + 1][currY];
    //             }
    //         }
    //         break;
    //     case 2:
    //         if(openF){
    //             if(hamDist[currX - 1][currY] < maxVal) {
    //                 hasRotated = false;
    //                 maxVal = hamDist[currX - 1][currY];
    //             }
    //         }
    //         if(openL){
    //             if(hamDist[currX][currY + 1] < maxVal) {
    //                 rotation = 90;
    //                 hasRotated = true;
    //                 maxVal = hamDist[currX][currY + 1];
    //             }
    //         }
    //         if(openR){
    //             if(hamDist[currX][currY - 1] < maxVal) {
    //                 rotation = -90;
    //                 hasRotated = true;
    //                 maxVal = hamDist[currX][currY - 1];
    //             }
    //         }
    //         break;
    //     case 3:
    //         if(openF){
    //             if(hamDist[currX][currY + 1] < maxVal) {
    //                 hasRotated = false;
    //                 maxVal = hamDist[currX][currY + 1];
    //             }
    //         }
    //         if(openL){
    //             if(hamDist[currX + 1][currY] < maxVal) {
    //                 rotation = 90;
    //                 hasRotated = true;
    //                 maxVal = hamDist[currX + 1][currY];
    //             }
    //         }
    //         if(openR){
    //             if(hamDist[currX - 1][currY] < maxVal) {
    //                 rotation = -90;
    //                 hasRotated = true;
    //                 maxVal = hamDist[currX - 1][currY];
    //             }
    //         }
    //         break;
    // }
    if(hasRotated){
        out[0] = 2;
        out[1] = rotation;
    }else{
        out[0] = 0;
        out[1] = 0;
        tremauxMap[currX][currY]++;
    }
}

int Algorithm::numPath() {
    int i = 0;                          //finds number of open paths
    int left[2], front[2], right[2];
    switch(currDir){
        case 0:
            left[0] = currX;
            left[1] = currY - 1;
            front[0] = currX + 1;
            front[1] = currY;
            right[0] = currX;
            right[1] = currY + 1;
            break;
        case 1:
            left[0] = currX - 1;
            left[1] = currY;
            front[0] = currX;
            front[1] = currY - 1;
            right[0] = currX + 1;
            right[1] = currY;
            break;
        case 2:
            left[0] = currX;
            left[1] = currY + 1;
            front[0] = currX - 1;
            front[1] = currY;
            right[0] = currX;
            right[1] = currY - 1;
            break;
        case 3:
            left[0] = currX + 1;
            left[1] = currY;
            front[0] = currX;
            front[1] = currY + 1;
            right[0] = currX - 1;
            right[1] = currY;
            break;
    }

    openL = openL && tremauxMap[left[0]][left[1]] < DEAD_END;
    openF = openF && tremauxMap[front[0]][front[1]] < DEAD_END;
    openR = openR && tremauxMap[right[0]][right[1]] < DEAD_END;

    if(openL){i++;}
    if(openF){i++;}
    if(openR){i++;}
    return i;
}

// update the algorithm hamming map based on displacement.
void Algorithm::updateMap(){
    if(currX != prevX){ // only X has changed
        if(currX-prevX > 1){    // moved east
            for(int i = prevX + 1; i < currX; i++){
                if(tremauxMap[i][currY] != -1)
                    tremauxMap[i][currY]++;
            }
        }else{  // moved west
            for(int i = currX + 1; i < prevX; i++){
                if(tremauxMap[i][currY] != -1)
                    tremauxMap[i][currY]++;
            }
        }
    }else{  // only y has changed
        if(currY-prevY > 1){    // moved south
            for(int i = prevY + 1; i < currY; i++){
                if(tremauxMap[currX][i] != -1)
                    tremauxMap[currX][i]++;
            }
        }else{  // moved north
            for(int i = currY + 1; i < prevY; i++){
                if(tremauxMap[currX][i] != -1)
                    tremauxMap[currX][i]++;
            }
        }
    }
}

/* --- Public functions --- */
Algorithm::Algorithm() {
    populateMap();
}

int* Algorithm::decide() {
    int numPaths = numPath();
    switch(numPaths){
        case 0: // dead end (turn around!)
            mvDEnd();
            break;
        case 1: // corridor (move forward after hitting a dead end)
            mvCorr();
            break;
        case 2:
        case 3: // junction (decide where to go!)
            mvJunct();
            break;
        default:
            cout << "Algorithm::decide(): Invalid numPath (" << numPath() << ")." << endl;
            break;
    }

    if(hamDist[currX][currY] == 0){ //if reached center
        out[0] = 3;                 //set finish flag
    }

    // cout << "Internal Algo Pos (X|Y|dir): " << currX << "|" << currY << "|" << currDir << endl;
    // cout << "Decision: " << out[0] << "|" << out[1] << endl;
    return out;
}

void Algorithm::getCheck(bool* wallCheck, int* mousePos) {
    openL = wallCheck[0];                               // 1 = open, 0 = blocked
    openF = wallCheck[1];
    openR = wallCheck[2];

    // save old position and heading
    prevX = currX;
    prevY = currY;
    prevDir = currDir;

    currX = mousePos[0];
    currY = mousePos[1];

    // adjust internal heading
    switch(mousePos[2]){
        case 0:
            currDir = 0;
            break;
        case 90:
            currDir = 1;
            break;
        case 180:
            currDir = 2;
            break;
        case 270:
            currDir = 3;
            break;
        default:
            cout << "Algorithm::getCheck(): Invalid restricted heading - " << mousePos[2] << endl;
            break;
    }

    updateMap();
}

void Algorithm::printMaze(){
    cout << "--- begin tremaux map ---" << endl;
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
            if(currY == i && currX == j){
                switch(currDir){  // mouse already takes care of heading double-ness
                    default:
                    case 0:
                        cout << " \u2192\t";
                        break;
                    case 1:
                        cout << " \u2191\t";
                        break;
                    case 2:
                        cout << " \u2190\t";
                        break;
                    case 3:
                        cout << " \u2193\t";
                        break;
                }}
            else if(tremauxMap[j][i] >= DEAD_END)
                cout << "\u25A0" << "\t";
            else cout << tremauxMap[j][i] << "\t";
        }
        cout << endl;
    }
    cout << "--- end tremaux map ---" << endl;
}

std::vector<Decision> Algorithm::getShortestPath(){

    return solution;
}
