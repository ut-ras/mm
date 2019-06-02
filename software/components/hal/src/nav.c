#include "nav.h"
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define MAZE_UNIT_SIZE 215

struct movement_info moveCenter(float speed) {
  struct movement_info info;
  do { info = moveIRU(8.5); } while (!info.front && info.left && info.right);
  vTaskDelay(250 / portTICK_RATE_MS);

  return info;
}

struct movement_info turnCenter(float speed) {
  turn90(speed);
  struct movement_info info;
  info = moveEnc(8.5, 190);
  vTaskDelay(250 / portTICK_RATE_MS);

  return info;
}

void turn180Center(float speed) { turn180(speed); }

void moveTest(float speed) { moveCenter(speed); }
