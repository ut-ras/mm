#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "hal/inc/enc.h"

void app_main() {
  enc_init();

  while (1) {
    printf("Left: %d\n", getTicks(1));
    printf("Right: %d\n", getTicks(0));
    vTaskDelay(10 / portTICK_RATE_MS);
  }
}
