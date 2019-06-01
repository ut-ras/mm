#include <stdlib.h>
#include "esp_timer.h"
#include "hal/inc/motorController.h"
#include "hal/inc/movement.h"

void app_main() {
  if (init()) exit(1);

  zero();
  while (true) {
    struct movement_info info = moveIR(8.5);
    if (!info.left || !info.right) break;
    turn180(-15.0);
  }
}
