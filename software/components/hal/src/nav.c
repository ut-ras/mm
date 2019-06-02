#include "nav.h"
#include <stdlib.h>

#define MAZE_UNIT_SIZE 215

struct movement_info moveCenter(float speed) {
  struct movement_info info;
  do { info = moveEncU(8.5); } while (!info.front && info.left && info.right);

  int travel = 0;
  if (info.front) {
    travel = (info.ticksTraveled % MAZE_UNIT_SIZE) * -1;
  } else if (info.right) {
    travel = 154;
  } else if (info.left) {
    travel = 123;
  }

  struct movement_info encMove = moveEnc(travel < 0 ? -8.5 : 8.5, abs(travel));
  info.ticksTraveled += encMove.ticksTraveled;

  return info;
}

struct movement_info turnCenter(float speed) {
  turn90(speed);
  struct movement_info info;
  info = moveEnc(8.5, 170);

  return info;
}

void turn180Center(float speed) { turn180(speed); }

void moveTest(float speed) { moveCenter(speed); }
