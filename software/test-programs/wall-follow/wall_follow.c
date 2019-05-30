#include <stdlib.h>
#include "esp_timer.h"
#include "hal/inc/motorController.h"
#include "hal/inc/movement.h"

void app_main() {
  if (init()) exit(1);

  zero();
  while (true) {
    moveIR(8.0);
    turn180(-15.0);
  }
}
