/**
 * Matthew Yu and Ammad
 * HighLevelFunctions.js
 * Micromouse Algorithm Testing
 * TODO: write addRelation
 */

/**
 *  @function findDir - determines the direction the mouse should travel after
 *  reaching a junction
 *  @param pos - coordinates of the junction the mouse is at [x,y]
 *  @param dir - direction from whence the mouse came from
 *  @return bestDir - direction mouse should now go (1-N, 2-E, 3-S, 4-W)
 */
findDir(pos, dir){
    let cell[2][5];
    //find directions with open walls
    cell[0] = getCellType();    //only access first 4 entries since 5th is no of open walls
    //determine HammingDist of each direction
    for(int i = 0; i < 4; i++){
        //if direction has no wall
        if(cell[0][i] == 1){
            //if direction is not from where the mouse came from
            if(dir != i)
                cell[1][i] = findHammingDist(pos, i);
        //if direction has wall
        }else{
            cell[1][i] = -1;
        }
    }
    //choose direction with neighbor cell with smallest Hamming dist to center
    let bestDir = 0;
    for(int i = 0; i < 4; i++){
        if (cell[1][i] < cell[1][bestDir])
            bestDir = i;
    }

    return bestDir;
}

findHammingDist(pos, dir){
    switch(dir){
        case 0:
            pos[1]--;
            break;
        case 1:
            pos[0]--;
            break;
        case 2:
            pos[1]++;
            break;
        case 3:
            pos[0]++;
            break;
    }
    if(pos[0] > 7){
        if(pos[1] > 7)
            return abs(pos[0]-8) + abs(pos[1]-8);
        else
            return abs(pos[0]-8) + abs(pos[1]-7);
    }else{
        if(pos[1] > 7)
            return abs(pos[0]-7) + abs(pos[1]-8);
        else
            return abs(pos[0]-7) + abs(pos[1]-7);
    }
}


/**
 *  @function movePath - directs a mouse along a corridor until it reaches a junction.
 *  @param pos - coordinates of the junction before the mouse moves [x,y]
 *  @param dir - direction mouse goes from the current junction
 *  @return location - [newPos, moveDist]
 */
movePath(pos, dir){
    let activeDir = dir;
    let mvDst = 0;
    let cell;
    let deadEnd = false;

    //hardware driver funct - move the mouse an arbitrary distance (1 cell)
    //in the activeDirection
    moveMouse(activeDir);
    //hardware driver funct - use onboard IR sensors to determine which directions are open
    //requires the mouse absolute direction and returns a struct containing the
    //status of each direction (wall or not) and the number of directions open
    cell = getCellType();
    //while cell is a dead end or corridor
    while(cell[4] == 1 || cell[4] == 2){
        //if cell is a corridor
        if(cell[4] == 2){
            //if cell is at a corner - wall exists in front
            if(cell[activeDir == 0]){
                //"block" off path from behind
                if(activeDir == 0 || activeDir == 1){
                    cell[activeDir+2] = 0;
                }
                else{
                    cell[activeDir-2] = 0;
                }
                //change active direction based on what side is open
                for(int i = 0; i < 4; i++){
                    if(cell[i] == 1){
                        activeDir = i;
                    }
                }
            }
            //change position based on direction to move before moving
            switch(activeDir){
                case 0:
                    pos[1]++;
                    break;
                case 1:
                    pos[0]++;
                    break;
                case 2:
                    pos[1]--;
                    break;
                case 3:
                    pos[0]--;
                    break;
            }
        }

        //if cell is a dead eand
        if(cell[4] == 1){
            deadEnd = true;
            //flip activeDir - turn around
            if(activeDir==0||activeDir==1){
                activeDir += 2;
            }
            else{
                activeDir -= 2;
            }
        }
        mvDst++;
        moveMouse(activeDir);
        cell = getCellType();
    }
    //assumption is that dead ends mean you return to the previous junction
    if(deadEnd)
        return [0, pos];
    else
        return [mvDst, pos];
}

/**
 *  @function addRelation - given the previous and newly reached node, adjust the
 *  nodeList to add connections or prune the wall.
 *  @param prevNode - previous node
 *  @param currNode - node mouse currently reached
 */
addRelation(prevNode, currNode){

}
