/**
 * Mmouse.js
 * Author: Matthew Yu
 * Last modified: 10/24/18
 *
 * This file describes the mmouse class and the functions that it uses.
 * This class is dependent on the following classes and their source files:
 *      @class Node m_Node.js
 *      @class Neighbor m_Neighbor.js
 * This class also calls the methods available from the mmouse API
 * from the MicromouseSimulator.
 * https://github.com/bblodget/MicromouseSim/wiki/Mouse-API
 */
class Mmouse{
    constructor(position = [0, 15]){
        this.position = position;
        this.mvDir = null;
    }
    //private functions
    /**
     *  @function moveMouse - move the mmouse an arbitrary distance (1 cell)
     *      in a given Math.absolute direction
     *  @param activeDir : int
     *     direction to move towards.
     */
    moveMouse(activeDir){
        let facing = mouse.heading();
        switch(facing){
            case 'N':
                break;
            case 'E':
                mouse.left();
                break;
            case 'S':
                mouse.left(2);
                break;
            case 'W':
                mouse.right(1);
                break;
        }
        switch(activeDir){
            case 0: //N
                mouse.fwd();
                break;
            case 1: //E
                mouse.right();
                mouse.fwd();
                break;
            case 2: //S
                mouse.right(2);
                mouse.fwd();
                break;
            case 3: //W
                mouse.left();
                mouse.fwd();
                break;
        }
    }
    /**
     *  @function getCellType - uses IR sensors to determine existence of walls
     *      in each Math.absolute direction
     *  @return int[5]
     *      first 4 indices refer to each direction, N/E/S/W,
     *      and 1 = no wall, 0 = wall; 5th index is the no. of open walls
     */
    getCellType(){
        let cell = [0, 0, 0, 0, 0];
        let facing = mouse.heading();
        switch(facing){
            case 'N':
                break;
            case 'E':
                mouse.left();
                break;
            case 'S':
                mouse.left(2);
                break;
            case 'W':
                mouse.right(1);
                break;
        }
        if(mouse.isPathFwd()){
            cell[0] = 1;
            cell[4]++;
        }
        if(mouse.isPathRight()){
            cell[1] = 1;
            cell[4]++;
        }
        if(mouse.isPathBack()){
            cell[2] = 1;
            cell[4]++;
        }
        if(mouse.isPathLeft()){
            cell[3] = 1;
            cell[4]++;
        }
        return cell;
    }
    /**
     *  @function findHammingDist - given a position and direction to move towards,
     *     findHammingDist finds the distance to the center of the field.
     *  @param pos : int[2]
     *     (X, Y) coordinate of the mmouse.
     *  @param dir : int
     *     direction of possible travel. 0=N, 1=E, 2=S, 3=W
     */
    findHammingDist(pos, dir){
        let cpos = [pos[0],pos[1]];
        switch(dir){
            case 0:
                cpos[1]--;
                break;
            case 1:
                cpos[0]++;
                break;
            case 2:
                cpos[1]++;
                break;
            case 3:
                cpos[0]--;
                break;
        }
        if(cpos[0] > 7){
            if(cpos[1] > 7)
                return Math.abs(cpos[0]-8) + Math.abs(cpos[1]-8);
            else
                return Math.abs(cpos[0]-8) + Math.abs(cpos[1]-7);
        }else{
            if(cpos[1] > 7)
                return Math.abs(cpos[0]-7) + Math.abs(cpos[1]-8);
            else
                return Math.abs(cpos[0]-7) + Math.abs(cpos[1]-7);
        }
    }
    //public functions
    getPosition(){
        return this.position;
    }
    /**
     *  @function findDir - determines the direction the mmouse should travel after
     *     reaching a junction
     *  @param currNode : Node()
     *     secondary cell wall input for wall pruning checking
     *  @param pos : int[2]
     *     (x,y) coordinates of the mmouse.
     *  @param dir : int
     *     Math.absolute direction the mmouse entered the current junction from.
     *     0=N, 1=E, 2=S, 3=W
     *  @return int
     *     direction mmouse should now go (0=N, 1=E, 2=S, 3=W)
     */
    findDir(currNode, pos, dir){
     let cell = [[],[0,0,0,0,0]];
     //find directions with open walls
     cell[0] = this.getCellType();    //only access first 4 entries since 5th is no of open walls
     let neighbors = currNode.getNeighbors();
     //determine HammingDist of each direction
     for(let i = 0; i < 4; i++){
         //if direction has no wall or is unvisited
         if(cell[0][i] == 1 && neighbors[i].getAccessible() != 0){
             //if direction is not from where the mmouse came from
             if(dir != i)
                 cell[1][i] = this.findHammingDist(pos, i);
             else
                 cell[1][i] = -1;
         //if direction has wall
         }else{
             cell[1][i] = -1;
         }
     }
     //choose direction with neighbor cell with smallest Hamming dist to center
     let bestDir = 0;
     let tally = 0;
     //init direction is a direction that is not invalid
     for(let i = 3; i >= 0; i--){
         if(neighbors[i].getAccessible() != 0){
            if(neighbors[i].getAccessible() == -1  && cell[1][i] != -1)
                bestDir = i;
            if(neighbors[i].getAccessible() == 1 && cell[1][i] != -1 && tally == 0)
                bestDir = i;
            tally++;
         }
     }
     if(tally != 0){
         for(let i = 0; i < 4; i++){
            //if dir hamming distance is closer to center than the bestDir
            if(cell[1][i] < cell[1][bestDir] && cell[1][i] != -1 && neighbors[i].getAccessible() == -1){
                    bestDir = i;
            }
         }
     }else{
         for(let i = 0; i < 4; i++){
            //if dir hamming distance is closer to center than the bestDir
            if(cell[1][i] < cell[1][bestDir] && cell[1][i] != -1){
                bestDir = i;
            }
         }
     }

     return bestDir;
    }
    /**
     *  @function movePath - directs a mmouse along a corridor until it reaches a junction.
     *  @param pos : int[2]
     *     (x,y) coordinates of the mmouse before it starts moving.
     *  @param dir :int
     *     Math.absolute direction the mmouse leaves from the current junction
     *  @return int[2], where [0] = int[2]
     *     location - [newPos, moveDist, directionEntered]
     */
    movePath(pos_o, dir){
        let pos = [pos_o[0], pos_o[1]];
        //let y = pos[1];
        let activeDir = dir;
        let mvDst = 0;
        let cell;
        let deadEnd = false;

        //hardware driver funct - move the mmouse an arbitrary distance (1 cell)
        //in the activeDirection

        //go one cell into the corridoor.
        this.moveMouse(activeDir);
        //change position based on direction to move before moving
        switch(activeDir){
            case 0:
            pos[1]--;
            break;
            case 1:
            pos[0]++;
            break;
            case 2:
            pos[1]++;
            break;
            case 3:
            pos[0]--;
            break;
        }
        mvDst++;
        //hardware driver funct - use onboard IR sensors to determine which directions are open
        //requires the mmouse Math.absolute direction and returns a struct containing the
        //status of each direction (wall or not) and the number of directions open
        cell = this.getCellType();
        //while cell is a dead end or corridor
        while(cell[4] == 1 || cell[4] == 2){
            //if cell is a corridor
            if(cell[4] == 2){
                //if cell is at a corner - wall exists in front
                if(cell[activeDir] == 0){
                    //"block" off path from behind
                    cell[(activeDir+2)%4] = 0;
                    //change active direction based on what side is open
                    for(let i = 0; i < 4; i++){
                        if(cell[i] == 1){
                            activeDir = i;
                        }
                    }
                }
            }
            //if cell is a dead eand
            if(cell[4] == 1){
                deadEnd = true;
                //flip activeDir - turn around
                activeDir = (activeDir+2)%4;
            }
            mvDst++;
            this.moveMouse(activeDir);
            //change position based on direction to move before moving
            switch(activeDir){
                case 0:
                pos[1]--;
                break;
                case 1:
                pos[0]++;
                break;
                case 2:
                pos[1]++;
                break;
                case 3:
                pos[0]--;
                break;
            }
            cell = this.getCellType();
        }

        //assumption is that dead ends mean you return to the previous junction
        if(deadEnd)
            return [pos, 0, dir];
        else
            return [pos, mvDst, (activeDir+2)%4];
    }

    //Mouse API defined functions
    // var heading = function(){};
    // var left = function(){};
    // var right = function(){};
    // var forward = function(){};
    // var isPathFwd = function(){};
    // var isPathBack = function(){};
    // var isPathLeft = function(){};
    // var isPathRight = function(){};
}
