#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"

void app_main() {
	adc1_config_width(ADC_WIDTH_BIT_12);
	adc1_config_channel_atten(ADC_CHANNEL_0, ADC_ATTEN_DB_6);

	gpio_config_t conf;
	conf.intr_type = GPIO_PIN_INTR_DISABLE;
	conf.mode = GPIO_MODE_OUTPUT;
	conf.pin_bit_mask = 1ULL<<2;
    conf.pull_down_en = 0;
    conf.pull_up_en = 0;

    gpio_config(&conf);

	gpio_set_level(GPIO_NUM_2, 1);

	uint32_t val;

	while (1) {
		val = adc1_get_raw(ADC_CHANNEL_6);
		printf("Vals %d\n", val);
	}
}
