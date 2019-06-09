#include "Algorithm.h"
#include <iostream>
#include <ostream>

void Algorithm::populateMap() {       // creates a default tremaux map and solution map.
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
            for(int k = 0; k < 5; k++)
                tremauxMap[i][j][k] = 0;
        }
    }
    tremauxMap[0][15][0] = -1;
    tremauxMap[7][7][0] = -1;
    tremauxMap[7][8][0] = -1;
    tremauxMap[8][7][0] = -1;
    tremauxMap[8][8][0] = -1;

    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++)
            solutionMap[i][j] = 0;
    }
}

// precondition: if only one direction is open
void Algorithm::mvCorr() {
    if(openF){  // dead end, has rotated, move forward.
        out[0] = 0;
        out[1] = 1;
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

    tremauxMap[currX][currY][0] = DEAD_END;
}

// precondition: more than 1 paths are open
void Algorithm::mvJunct() {
    int rotation = 0;
    bool hasRotated = false;

    // first check if there is a priority among tremaux
    int lowestSide = 0; //front
    int lowestVal = 99;
    int front, left, right;
    switch(currDir){
        case 0: // east
            front = tremauxMap[currX + 1][currY][0];
            left = tremauxMap[currX][currY - 1][0];
            right = tremauxMap[currX][currY + 1][0];

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
            front = tremauxMap[currX][currY - 1][0];
            left = tremauxMap[currX - 1][currY][0];
            right = tremauxMap[currX + 1][currY][0];

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
            front = tremauxMap[currX - 1][currY][0];
            left = tremauxMap[currX][currY + 1][0];
            right = tremauxMap[currX][currY - 1][0];

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
            front = tremauxMap[currX][currY + 1][0];
            left = tremauxMap[currX + 1][currY][0];
            right = tremauxMap[currX - 1][currY][0];

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

    if(hasRotated){
        out[0] = 2;
        out[1] = rotation;
    }else{
        out[0] = 0;
        out[1] = 1;
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

    openL = openL && tremauxMap[left[0]][left[1]][0] < DEAD_END;
    openF = openF && tremauxMap[front[0]][front[1]][0] < DEAD_END;
    openR = openR && tremauxMap[right[0]][right[1]][0] < DEAD_END;

    if(openL){i++;}
    if(openF){i++;}
    if(openR){i++;}
    return i;
}

// update the algorithm hamming map based on displacement.
void Algorithm::updateMap(){
    switch(currDir){
        case 0: // east
            tremauxMap[currX][currY][1] = openF;
            tremauxMap[currX][currY][2] = openL;
            tremauxMap[currX][currY][3] = 1;
            tremauxMap[currX][currY][4] = openR;
            break;
        case 1: // north
            tremauxMap[currX][currY][1] = openR;
            tremauxMap[currX][currY][2] = openF;
            tremauxMap[currX][currY][3] = openL;
            tremauxMap[currX][currY][4] = 1;
            break;
        case 2: // west
            tremauxMap[currX][currY][1] = 1;
            tremauxMap[currX][currY][2] = openR;
            tremauxMap[currX][currY][3] = openF;
            tremauxMap[currX][currY][4] = openL;
            break;
        case 3: // south
            tremauxMap[currX][currY][1] = openL;
            tremauxMap[currX][currY][2] = 1;
            tremauxMap[currX][currY][3] = openR;
            tremauxMap[currX][currY][4] = openF;
            break;
        default:
            cout << "Algorithm::updateMap(): Invalid restricted heading - " << currDir << endl;
            break;
    }
}

/* --- Public functions --- */
Algorithm::Algorithm() {
    populateMap();
}

int* Algorithm::decide() {
    int numPaths = numPath();
    cout << "Internal Algo Pos (X|Y|dir): " << currX << "|" << currY << "|" << currDir << endl;
    cout << "Num Paths: " << numPaths << endl;

    switch(numPaths){
        case 0: // dead end (turn around!)
            mvDEnd();
            break;
        case 1: // corridor (move forward after hitting a dead end)
            mvCorr();
            if(tremauxMap[currX][currY][0] != -1)
                tremauxMap[currX][currY][0]++;
            break;
        case 2:
        case 3: // junction (decide where to go!)
            mvJunct();
            if(tremauxMap[currX][currY][0] != -1)
                tremauxMap[currX][currY][0]++;
            break;
        default:
            cout << "Algorithm::decide(): Invalid numPath (" << numPath() << ")." << endl;
            break;
    }

    if((currX == 7 || currX == 8) && (currY == 7 || currY == 8)){ //if reached center, set finish flag
        out[0] = 3;
    }

    cout << "Decision: " << out[0] << "|" << out[1] << endl;
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
            else if(tremauxMap[j][i][0] >= DEAD_END)
                cout << "\u25A0" << "\t";
            else cout << tremauxMap[j][i][0] << "\t";
        }
        cout << endl;
    }
    cout << "--- end tremaux map ---" << endl;
}

// BFS implementation modified from https://www.geeksforgeeks.org/shortest-path-in-a-binary-maze/.
std::stack<Point> Algorithm::getShortestPath(){
    std::queue<Point> queue;

    // start with cell at 0|15 (X).
    struct Point p = {0, 15};
    queue.push(p);

    Point endPoint;

    // iterative: while the queue is not empty
    int round = 1;
    bool nEnd = true;
    int size = 1;

    while(size > 0 && nEnd){
        // for each point in the queue, assign it a value if it has not already received one
        size = queue.size();
        for(int i = 0; i < size; i++){
            struct Point pt = queue.front();
            queue.pop();

            // if endpoint is found, exit.
            if(tremauxMap[pt.x][pt.y][0] == -1 && pt.x != 0 && pt.y != 15){
                solutionMap[pt.x][pt.y] = round;
                endPoint = pt;
                nEnd = false;
                break;
            }

            if(pt.x >= 0 && pt.x <= 15 && pt.y >= 0 && pt.y <= 15
                && tremauxMap[pt.x][pt.y][0] != 0 && solutionMap[pt.x][pt.y] == 0){
                    // set value of flood fill iteration
                    solutionMap[pt.x][pt.y] = round;

                    // find all nearby possible path points and add to queue.
                    for(int nearby = 0; nearby < 4; nearby++){
                        switch(nearby){
                            case 0: // E
                                // and is an open path, and has been explored, and is not part of another solution
                                if(tremauxMap[pt.x][pt.y][1] == 1){
                                    struct Point p = {pt.x + 1, pt.y};
                                    queue.push(p);
                                }
                                break;
                            case 1: // N
                                // and is an open path, and has been explored, and is not part of another solution
                                if(tremauxMap[pt.x][pt.y][2] == 1){
                                    struct Point p = {pt.x, pt.y - 1};
                                    queue.push(p);
                                }
                                break;
                            case 2: // W
                                // and is an open path, and has been explored, and is not part of another solution
                                if(tremauxMap[pt.x][pt.y][3] == 1){
                                    struct Point p = {pt.x - 1, pt.y};
                                    queue.push(p);
                                }
                                break;
                            case 3: // S
                                // and is an open path, and has been explored, and is not part of another solution
                                if(tremauxMap[pt.x][pt.y][4] == 1){
                                    struct Point p = {pt.x, pt.y + 1};
                                    queue.push(p);
                                }
                                break;
                        }
                    }
            }
        }
        round++;
    }

    do{
        // push the next last point onto the stack
        solution.push(endPoint);
        // find the next adjacent neighbor (E/N/W/S)
        int val = solutionMap[endPoint.x][endPoint.y];
        if(val == solutionMap[endPoint.x + 1][endPoint.y] + 1){
            struct Point p = {endPoint.x + 1, endPoint.y};
            endPoint = p;
        }else if(val == solutionMap[endPoint.x][endPoint.y - 1] + 1){
            struct Point p = {endPoint.x, endPoint.y - 1};
            endPoint = p;
        }else if(val == solutionMap[endPoint.x - 1][endPoint.y] + 1){
            struct Point p = {endPoint.x - 1, endPoint.y};
            endPoint = p;
        }else if(val == solutionMap[endPoint.x][endPoint.y + 1] + 1){
            struct Point p = {endPoint.x, endPoint.y + 1};
            endPoint = p;
        }
    }while(!(endPoint.x == 0 && endPoint.y == 15));

    p = {0, 15};
    solution.push(p);

    // return solution;
    return solution;
}
