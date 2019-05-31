#include "hal/movement.h"
#include "hal/motorController.h"
#include "esp_timer.h"
#include <stdlib.h>

void app_main() {
  if (init())
      exit(1);

  zero();
  while (true) {
    struct movement_info info = moveIR(9.0);
    if (!info.left || !info.right) break;
    turn180(-15.0);
  }
}
