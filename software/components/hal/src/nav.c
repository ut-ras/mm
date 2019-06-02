#include "nav.h"

#define MAZE_UNIT_SIZE 215

struct movement_info moveCenter(float speed) {
  struct movement_info info;
  do { info = moveIR(8.5); } while (!info.front && info.left && info.right);

  if (info.front)
    moveEnc(-speed, (info.ticksTraveled % MAZE_UNIT_SIZE));
  else if (info.right) {
    moveEnc(speed, 154);
  } else if (info.left) {
    moveEnc(speed, 123);
  }

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
