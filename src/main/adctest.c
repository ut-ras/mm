#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"

void app_main1() {
	adc1_config_width(ADC_WIDTH_BIT_12);
	adc1_config_channel_atten(ADC_CHANNEL_2, ADC_ATTEN_DB_6);
	adc1_config_channel_atten(ADC_CHANNEL_7, ADC_ATTEN_DB_6);
	adc1_config_channel_atten(ADC_CHANNEL_6, ADC_ATTEN_DB_6);
	adc1_config_channel_atten(ADC_CHANNEL_1, ADC_ATTEN_DB_6);
	gpio_config_t conf;
	conf.intr_type = GPIO_PIN_INTR_DISABLE;
	conf.mode = GPIO_MODE_OUTPUT;
	conf.pin_bit_mask = 1ULL<<2;
    conf.pull_down_en = 0;
    conf.pull_up_en = 0;

    gpio_config(&conf);

    conf.pin_bit_mask = 1ULL<<15;
    gpio_config(&conf);

	gpio_set_level(GPIO_NUM_2, 1);
	gpio_set_level(GPIO_NUM_15, 1);

	uint32_t val;
	uint32_t val2;
	uint32_t val3;
	uint32_t val4;

	while (1) {
		val = adc1_get_raw(ADC_CHANNEL_7);
		val2 = adc1_get_raw(ADC_CHANNEL_6);
		val3 = adc1_get_raw(ADC_CHANNEL_1);
		val4 = adc1_get_raw(ADC_CHANNEL_2);


		printf("Vals %d %d %d %d\n", val, val2, val3, val4);
	}
}
