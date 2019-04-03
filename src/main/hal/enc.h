#ifndef ENC_H
#define ENC_H

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include<stdlib.h>

xQueueHandle pcnt_evt_queue; // A queue to handle pulse counter events

enum Direction{
  forward = 0,
  backward = 1,
  stop = 2
};

/* A sample structure to pass events from the PCNT
 * interrupt handler to the main program.
 */
typedef struct {
  int unit;        // the PCNT unit that originated an interrupt
  uint32_t status; // information on the event type that caused the interrupt
} pcnt_evt_t;


typedef struct{
  int count;
  int sum;
  int pcnt;
  int direction;
}Enc;

Enc *encoders[4];

void enc_init();
void readEncoders();
int getTicks(int enc_num);

#endif
