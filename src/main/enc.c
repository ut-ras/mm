#include "driver/gpio.h"
#include "driver/pcnt.h"
#include "driver/periph_ctrl.h"
#include "enc.h"
#include "esp_attr.h"
#include "esp_log.h"
#include "freertos/portmacro.h"
#include "soc/gpio_sig_map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PCNT_H_LIM_VAL INT16_MAX
#define PCNT_L_LIM_VAL INT16_MIN
#define PCNT_FILTER_VAL 100
#define ACTIVE_ENCODERS 2

pcnt_isr_handle_t user_isr_handle = NULL; // user's ISR service handle

/* Decode what PCNT's unit originated an interrupt
 * and pass this information together with the event type
 * the main program using a queue.
 */
static void IRAM_ATTR pcnt_enc_intr_handler(void *arg) {
  uint32_t intr_status = PCNT.int_st.val;
  int i;
  pcnt_evt_t evt;
  portBASE_TYPE HPTaskAwoken = pdFALSE;

  for (i = 0; i < PCNT_UNIT_MAX; i++) {
    if (intr_status & (BIT(i))) {
      evt.unit = i;
      /* Save the PCNT event type that caused an interrupt
         to pass it to the main program */
      evt.status = PCNT.status_unit[i].val;
      PCNT.int_clr.val = BIT(i);
      xQueueSendFromISR(pcnt_evt_queue, &evt, &HPTaskAwoken);
      if (HPTaskAwoken == pdTRUE) {
        portYIELD_FROM_ISR();
      }
    }
  }
}

static void pcnt_init(int unit, int encA, int encB) {
  pcnt_config_t pcnt_config = {
      .pulse_gpio_num = encA,
      .ctrl_gpio_num = encB,
      .channel = PCNT_CHANNEL_0,
      .unit = unit,
      .pos_mode = PCNT_COUNT_INC,      // increment on enc A posedge
      .neg_mode = PCNT_COUNT_DIS,      // ignore enc B negedge
      .lctrl_mode = PCNT_MODE_KEEP,    // ignore enc B low
      .hctrl_mode = PCNT_MODE_REVERSE, // decrement mode when enc B high
      .counter_h_lim = PCNT_H_LIM_VAL, // set max
      .counter_l_lim = PCNT_L_LIM_VAL, // set min
  };
  pcnt_unit_config(&pcnt_config);

  pcnt_set_filter_value(
      unit,
      PCNT_FILTER_VAL); // ignore pulse if less than val*12.5ns
  pcnt_filter_enable(unit);

  pcnt_event_enable(unit, PCNT_EVT_H_LIM);
  pcnt_event_enable(unit, PCNT_EVT_L_LIM);

  pcnt_counter_pause(unit);
  pcnt_counter_clear(unit);

  pcnt_isr_register(pcnt_enc_intr_handler, NULL, 0, &user_isr_handle);
  pcnt_intr_enable(unit);

  pcnt_counter_resume(unit);
}

int getTicks(int enc_num) { return encoders[enc_num]->count; }

void readEncoders() {
  int16_t count = 0;
  pcnt_evt_t evt;
  portBASE_TYPE res;
  res = xQueueReceive(pcnt_evt_queue, &evt, 0);
  if (res == pdTRUE) {
    pcnt_get_counter_value(evt.unit, &count);
    encoders[evt.unit]->sum =
        encoders[evt.unit]->sum + count; // manage overflow of 16-bit counter
    printf("Event PCNT unit[%d]; cnt: %d\n", evt.unit, count);
    if (evt.status & PCNT_STATUS_L_LIM_M) {
      printf("L_LIM EVT\n");
    }
    if (evt.status & PCNT_STATUS_H_LIM_M) {
      printf("H_LIM EVT\n");
    }
  } else {
    for (int i = 0; i < ACTIVE_ENCODERS; i++) {
      pcnt_get_counter_value(i, &count);
      if (count < encoders[i]->count - encoders[i]->sum) {
        encoders[i]->direction = backward;
      } else {
        encoders[i]->direction = forward;
      }
      encoders[i]->count = count + encoders[i]->sum;
      // printf("Enc %d :%d\n", i, encoders[i]->count);
    }
  }
  if (user_isr_handle) {
    esp_intr_free(user_isr_handle);
    user_isr_handle = NULL;
  }
}

void enc_init() {
  pcnt_evt_queue = xQueueCreate(10, sizeof(pcnt_evt_t));

  encoders[0] = (Enc *)malloc(sizeof(Enc));
  encoders[0]->count = 0;
  encoders[0]->sum = 0;
  encoders[0]->direction = forward;
  encoders[0]->pcnt = PCNT_UNIT_0;
  pcnt_init(encoders[0]->pcnt, 5,
            10); // pcnt 0, A=gpio5, B=gpio10

  encoders[1] = (Enc *)malloc(sizeof(Enc));
  encoders[1]->count = 0;
  encoders[1]->sum = 0;
  encoders[1]->direction = forward;
  encoders[1]->pcnt = PCNT_UNIT_1;
  pcnt_init(encoders[1]->pcnt, 25,
            26); // pcnt 0, A=gpio25, B=gpio26
}
