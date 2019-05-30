#include "distance.h"

int init_distance_sensor(distance *sensor, int front_pin, int side_pin,
                         int emitter_pin) {
  switch (front_pin) {
    case 36:
      sensor->front = ADC1_CHANNEL_0;
      break;
    case 37:
      sensor->front = ADC1_CHANNEL_1;
      break;
    case 38:
      sensor->front = ADC1_CHANNEL_2;
      break;
    case 39:
      sensor->front = ADC1_CHANNEL_3;
      break;
    case 32:
      sensor->front = ADC1_CHANNEL_4;
      break;
    case 33:
      sensor->front = ADC1_CHANNEL_5;
      break;
    case 34:
      sensor->front = ADC1_CHANNEL_6;
      break;
    case 35:
      sensor->front = ADC1_CHANNEL_7;
      break;
    default:
      return 1;
  }

  switch (side_pin) {
    case 36:
      sensor->side = ADC1_CHANNEL_0;
      break;
    case 37:
      sensor->side = ADC1_CHANNEL_1;
      break;
    case 38:
      sensor->side = ADC1_CHANNEL_2;
      break;
    case 39:
      sensor->side = ADC1_CHANNEL_3;
      break;
    case 32:
      sensor->side = ADC1_CHANNEL_4;
      break;
    case 33:
      sensor->side = ADC1_CHANNEL_5;
      break;
    case 34:
      sensor->side = ADC1_CHANNEL_6;
      break;
    case 35:
      sensor->side = ADC1_CHANNEL_7;
      break;
    default:
      return 2;
  }

  switch (emitter_pin) {
    case 1:
      sensor->emitter = GPIO_NUM_1;
      break;
    case 2:
      sensor->emitter = GPIO_NUM_2;
      break;
    case 3:
      sensor->emitter = GPIO_NUM_3;
      break;
    case 4:
      sensor->emitter = GPIO_NUM_4;
      break;
    case 5:
      sensor->emitter = GPIO_NUM_5;
      break;
    case 6:
      sensor->emitter = GPIO_NUM_6;
      break;
    case 7:
      sensor->emitter = GPIO_NUM_7;
      break;
    case 8:
      sensor->emitter = GPIO_NUM_8;
      break;
    case 9:
      sensor->emitter = GPIO_NUM_9;
      break;
    case 10:
      sensor->emitter = GPIO_NUM_10;
      break;
    case 11:
      sensor->emitter = GPIO_NUM_11;
      break;
    case 12:
      sensor->emitter = GPIO_NUM_12;
      break;
    case 13:
      sensor->emitter = GPIO_NUM_13;
      break;
    case 14:
      sensor->emitter = GPIO_NUM_14;
      break;
    case 15:
      sensor->emitter = GPIO_NUM_15;
      break;
    case 16:
      sensor->emitter = GPIO_NUM_16;
      break;
    case 17:
      sensor->emitter = GPIO_NUM_17;
      break;
    case 18:
      sensor->emitter = GPIO_NUM_18;
      break;
    case 19:
      sensor->emitter = GPIO_NUM_19;
      break;
    case 21:
      sensor->emitter = GPIO_NUM_21;
      break;
    case 22:
      sensor->emitter = GPIO_NUM_22;
      break;
    case 23:
      sensor->emitter = GPIO_NUM_23;
      break;
    case 25:
      sensor->emitter = GPIO_NUM_25;
      break;
    case 26:
      sensor->emitter = GPIO_NUM_26;
      break;
    case 27:
      sensor->emitter = GPIO_NUM_27;
      break;
    case 32:
      sensor->emitter = GPIO_NUM_32;
      break;
    case 33:
      sensor->emitter = GPIO_NUM_33;
      break;
    case 34:
      sensor->emitter = GPIO_NUM_34;
      break;
    case 35:
      sensor->emitter = GPIO_NUM_35;
      break;
    case 36:
      sensor->emitter = GPIO_NUM_36;
      break;
    case 37:
      sensor->emitter = GPIO_NUM_37;
      break;
    case 38:
      sensor->emitter = GPIO_NUM_38;
      break;
    case 39:
      sensor->emitter = GPIO_NUM_39;
      break;
    default:
      return 3;
  }

  gpio_config_t conf;
  conf.intr_type = GPIO_PIN_INTR_DISABLE;
  conf.mode = GPIO_MODE_OUTPUT;
  conf.pin_bit_mask = (1ULL << emitter_pin);
  conf.pull_down_en = 0;
  conf.pull_up_en = 0;

  gpio_config(&conf);

  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(sensor->front, ADC_ATTEN_DB_6);
  adc1_config_channel_atten(sensor->side, ADC_ATTEN_DB_6);

  gpio_set_level(sensor->emitter, 0);

  return 0;
}

void read_distance(distance *sensor, int *vals) {
  gpio_set_level(sensor->emitter, 1);

  vals[0] = adc1_get_raw(sensor->front);
  vals[1] = adc1_get_raw(sensor->side);

  gpio_set_level(sensor->emitter, 0);
}

int read_distance_front(distance *sensor) {
  int vals[2];
  read_distance(sensor, vals);
  return vals[0];
}

int read_distance_side(distance *sensor) {
  int vals[2];
  read_distance(sensor, vals);
  return vals[1];
}
