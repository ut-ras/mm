#include "hal/movement.h"
#include "hal/motorController.h"
#include "esp_timer.h"

void app_main() {
  if (init())
      exit(1);

  zero();

  moveIR(10.0);
  turn90(-15.0);
  turn90(-15.0);
  moveIR(10.0);

  while(true){}
}
