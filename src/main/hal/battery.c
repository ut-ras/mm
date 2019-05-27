#include "battery.h"
#include <driver/adc.h>

void initBattery(void) {
  adc1_config_channel_atten(ADC1_CHANNEL_5, ADC_ATTEN_DB_6);
}

int getBatteryVal(void) { return adc1_get_raw(ADC1_CHANNEL_5); }
