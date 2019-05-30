#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "hal/inc/distance.h"

#define LEFT_FRONT_PIN 37
#define LEFT_SIDE_PIN 38
#define LEFT_EMITTER 15

#define RIGHT_FRONT_PIN 34
#define RIGHT_SIDE_PIN 35
#define RIGHT_EMITTER 2

void app_main() {
  distance left;
  distance right;

  init_distance_sensor(&left, LEFT_FRONT_PIN, LEFT_SIDE_PIN, LEFT_EMITTER);

  init_distance_sensor(&right, RIGHT_FRONT_PIN, RIGHT_SIDE_PIN, RIGHT_EMITTER);

  int leftVals[2];
  int rightVals[2];

  while (true) {
    read_distance(&left, leftVals);
    read_distance(&right, rightVals);

    printf("Left: %d\nLeftF: %d\nRight: %d\nRightF: %d\n", leftVals[1],
           leftVals[0], rightVals[1], rightVals[0]);
    vTaskDelay(10 / portTICK_RATE_MS);
  }
}
