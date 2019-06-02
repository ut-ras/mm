#include "nav.h"
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define MAZE_UNIT_SIZE 215

struct movement_info moveCenter(float speed) {
  struct movement_info info = getWalls(NULL, NULL);
  do {
    if (!info.left && !info.right)
      info = moveEnc(8.5, 210);
    else
      info = moveIRU(8.5);
    vTaskDelay(250 / portTICK_RATE_MS);
  } while (!info.front && info.left && info.right);
  vTaskDelay(250 / portTICK_RATE_MS);

  return info;
}

struct movement_info turnCenter(float speed) {
  turn90(speed);
  struct movement_info info;
    if (!info.left && !info.right)
      moveEnc(8.5, 190);
    else
      info = moveIRU(8.5);
  //info = moveEnc(8.5, 180);
  vTaskDelay(250 / portTICK_RATE_MS);

  return info;
}

struct movement_info turn180Center(float speed) { 
  turn180(speed);

  struct movement_info info;
    if (!info.left && !info.right)
      moveEnc(8.5, 190);
    else
      info = moveIRU(8.5);
  return info;
}

void moveTest(float speed) { moveCenter(speed); }
