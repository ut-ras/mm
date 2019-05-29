#include "hal/movement.h"
#include "hal/motorController.h"
#include "esp_timer.h"
#include <stdlib.h>

void app_main() {
  if (init())
      exit(1);

  zero();
  while (true) {
    moveIR(8.0);
    turn180(-15.0);
  }
}
