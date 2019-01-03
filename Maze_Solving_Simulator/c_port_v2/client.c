/**
 * @Author: Matthew Yu
 * @Last Modifed: 1/1/19
 * @Changelog:
 * @Help: mmsim.readthedocs.io
 * @Purpose: for use for UT IEEE RAS Micromouse team, 2018-2019.
 * @Compile: "gcc -o client client.c -lzmq"
 */
#include <stdio.h>
#include <string.h>
#include <zmq.h>
#define INP_BUFF 10
#define MAZE_SIZE 16

static void *requester;

typedef struct State{
    int x;
    int y;
    char dir;
}State;

/**
 *  @func getResponse: prints response of server and client call
 */
void getResponse(){
    char buffer[256] = {0};
    zmq_recv(requester, buffer, 256, 0);
    printf("%s\n", buffer);
}

/**
 *  @func getInput: gets user input for controls.
 *  @precondition: no invalid output.
 *  @return int input
 */
int getInput(){
    char input[INP_BUFF];
    printf("Input >\t");
    fgets(input, INP_BUFF, stdin);
    return atoi(input);
}

/**
 *  @func getWalls: gets state of walls (relative to facing direction)
 *  @param [x,y]: current position
 *  @param direction: direction
 */
void getWalls(State s){
    char msg[4], walls[3] = { 0 };
    msg[0] = 'W'; //read walls
    msg[1] = s.x;  //x pos
    msg[2] = s.y;  //y pos
    msg[3] = s.dir;  //heading
    zmq_send(requester, msg, 4, 0);
    zmq_recv(requester, walls, 3, 0);
    printf("L:%i, F:%i, R:%i\n", walls[0], walls[1], walls[2]);
}

void sendState(int posX, int posY, char direction){
    char state[2 * (MAZE_SIZE * MAZE_SIZE) + 6];
    state[0] = 'S';
    state[1] = (char) posX;
    state[2] = (char) posY;
    state[3] = direction;
    state[4] = 'C';
    for(int i = 0; i < MAZE_SIZE * MAZE_SIZE; i++)
        state[i + 5] = 0;
    state[261] = 'C';
    for(int i = 0; i < MAZE_SIZE * MAZE_SIZE; i++)
        state[i + 262] = 0;

    // Display input to be sent
    // for(int i = 0; i < 4; i++)
    //     printf("%i ", state[i]);
    // printf("\n");
    zmq_send(requester, state, 518, 0);

    char buffer[2] = {0};
    zmq_recv(requester, buffer, 2, 0);

    // Display output msg, "ok" if command processed properly
    for(int i = 0; i < 2; i++)
        printf("%c", buffer[i]);
    printf("\n");
}

/**
 * @func move: takes user input to move then sends move req to server
 */
State move(State s){
    int mvInp = 0;
    mvInp = getInput(); //replace control of input with cpu algo l8r
    switch(mvInp){
        case 0: //N
            s.y++;
            s.dir = 'N';
            break;
        case 1: //E
            s.x++;
            s.dir = 'E';
            break;
        case 2: //S
            s.y--;
            s.dir = 'S';
            break;
        case 3: //W
            s.x--;
            s.dir = 'W';
            break;
    }
    sendState(s.x, s.y, s.dir);
    return s;
}


int main (void){
    void *context = zmq_ctx_new();
    requester = zmq_socket(context, ZMQ_REQ);

    zmq_connect(requester, "tcp://127.0.0.1:6574");

    //beep
    zmq_send(requester, "ping", 4, 0);
    getResponse();
    //reset
    zmq_send(requester, "reset", 5, 0);
    getResponse();


    //set pos
    State state = {0, 0, 'N'};
    /**
     *  input:
     *  -1 - exit and close connection to mmsim
     *  0 - default, no action taken
     *  1 - reset commands (and state)
     *  2 - getWalls
     *  3 - move
     */
    int input = 0;
    while(input != -1){
        input = getInput();
        switch(input){
            case 0: //beep
                zmq_send(requester, "ping", 4, 0);
                getResponse();
                break;
            case 1: //reset
                printf("resetting, ");
                zmq_send(requester, "reset", 5, 0);
                getResponse();
                state.x = 0;
                state.y = 0;
                state.dir = 'N';
                break;
            case 2: //getWalls
                printf("Walls:\t");
                getWalls(state);
                break;
            case 3: //move
                printf("Move:\t");
                state = move(state);
                break;
        }
    }


    printf("Closing client.\n");
    zmq_close(requester);
    zmq_ctx_destroy(context);
    return 0;
}
