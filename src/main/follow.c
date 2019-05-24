#include "hal/movement.h"
#include "hal/motorController.h"
#include "esp_timer.h"

void app_main() {
  if (init())
      exit(1);

  zero();

  moveIR(10.0);

  while(true){}
}
