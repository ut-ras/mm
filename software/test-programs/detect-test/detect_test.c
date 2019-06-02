#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "movement.h"

#define LEFT_FRONT_PIN 37
#define LEFT_SIDE_PIN 38
#define LEFT_EMITTER 15

#define RIGHT_FRONT_PIN 34
#define RIGHT_SIDE_PIN 35
#define RIGHT_EMITTER 2

#define b(boolean) ((boolean) ? "true" : "false")

void app_main() {
  init();

  struct movement_info info = getWalls(NULL, NULL);

  while (true) {
    printf("Left %s\n", b(info.left));

    printf("Right %s\n", b(info.right));

    printf("Front %s\n", b(info.front));

    vTaskDelay(10 / portTICK_RATE_MS);

    info = getWalls(NULL, NULL);
  }
}
