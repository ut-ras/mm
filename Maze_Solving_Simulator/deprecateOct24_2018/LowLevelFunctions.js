//Low Level Mouse Functions (Hardware Driver)

int CellType[5];

/**
 *  @function moveMouse - move the mouse an arbitrary distance (1 cell)
 *  in a given absolute direction
 *  @param activeDir - given absolute direction of movement
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
 *  in each absolute direction
 *  @return - CellType: an int array of size 5, first 4 indices refer to each
 *  direction, N/E/S/W, and 1 = no wall, 0 = wall; 5th index is the no. of open walls
 */
getCellType(){
    cell = {0, 0, 0, 0, 0};
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
