#include "hal/motorController.h"

void app_main1() {
  mcpwm_initialize();

  setMotors(10.0, 10.0);
  while(1){}
}

