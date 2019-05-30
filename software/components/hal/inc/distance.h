#ifndef DISTANCE_H
#define DISTANCE_H

#include <driver/adc.h>

struct distance {
  adc1_channel_t front;
  adc1_channel_t side;
  gpio_num_t emitter;
} typedef distance;

int init_distance_sensor(distance *sensor, int front_pin, int side_pin,
                         int emitter_pin);

void read_distance(distance *sensor, int *vals);

#endif /* DISTANCE_H */
