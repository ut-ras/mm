#include <stdio.h>
#include "hal/enc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main1() {
  
  enc_init();

  while(1) {
    printf("Left: %d\n", getTicks(1));
    printf("Right: %d\n", getTicks(0));
    vTaskDelay(10 / portTICK_RATE_MS);
  }
}
