#include "movement.h"

#define MAZE_UNIT_SIZE 210

static struct movement_info moveCenter(float speed) {
  struct movement_info info;
  do {
    info = moveIR(8.5);
  } while(!info.front && info.left && info.right);

  if (info.front)
    moveEnc(-speed, (info.ticksTraveled % MAZE_UNIT_SIZE));
  else {
    int forwardTicks = MAZE_UNIT_SIZE - (info.ticksTraveled % MAZE_UNIT_SIZE);
    if (forwardTicks <= MAZE_UNIT_SIZE / 3)
      forwardTicks += MAZE_UNIT_SIZE;
    moveEnc(speed, forwardTicks);
  }

  return info;
}

void moveTest(float speed) {
  moveCenter(speed);
}
