#include "hal/inc/motorController.h"

void app_main() {
  mcpwm_initialize();

  setMotors(-10.0, -10.0);
  while (1) {}
}
