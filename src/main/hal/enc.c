#include "enc.h"
#include "driver/pcnt.h"

#define PCNT_H_LIM_VAL INT16_MAX
#define PCNT_L_LIM_VAL INT16_MIN
#define PCNT_FILTER_VAL 100
#define ACTIVE_ENCODERS 2

pcnt_isr_handle_t user_isr_handle = NULL;  // user's ISR service handle
xQueueHandle pcnt_evt_queue;  // A queue to handle pulse counter events

/* A sample structure to pass events from the PCNT
 * interrupt handler to the main program.
 */
typedef struct {
  int unit;         // the PCNT unit that originated an interrupt
  uint32_t status;  // information on the event type that caused the interrupt
} pcnt_evt_t;

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
      if (HPTaskAwoken == pdTRUE) { portYIELD_FROM_ISR(); }
    }
  }
}

static void pcnt_init(int unit, int encA, int encB) {
  pcnt_config_t pcnt_config = {
      .pulse_gpio_num = encA,
      .ctrl_gpio_num = encB,
      .channel = PCNT_CHANNEL_0,  // encA goes to input channel, encB connected
                                  // to ctrl input
      .unit = unit,
      .pos_mode = PCNT_COUNT_INC,       // increment on enc A posedge
      .neg_mode = PCNT_COUNT_DIS,       // ignore enc B negedge
      .lctrl_mode = PCNT_MODE_KEEP,     // ignore enc B low
      .hctrl_mode = PCNT_MODE_REVERSE,  // decrement mode when enc B high
      .counter_h_lim = PCNT_H_LIM_VAL,  // set max
      .counter_l_lim = PCNT_L_LIM_VAL,  // set min
  };
  pcnt_unit_config(&pcnt_config);

  // filter noise
  pcnt_set_filter_value(
      unit,
      PCNT_FILTER_VAL);  // ignore pulse if less than val*12.5ns
  pcnt_filter_enable(unit);

  pcnt_event_enable(unit,
                    PCNT_EVT_H_LIM);  // enable events for hitting
                                      // max capacity on the 16-bit counter
  pcnt_event_enable(unit, PCNT_EVT_L_LIM);

  pcnt_counter_pause(unit);
  pcnt_counter_clear(unit);

  // register and enable interrupts
  pcnt_isr_register(pcnt_enc_intr_handler, NULL, 0, &user_isr_handle);
  pcnt_intr_enable(unit);

  pcnt_counter_resume(unit);
}

void readEncoders() {
  int16_t count = 0;
  pcnt_evt_t evt;
  portBASE_TYPE res;
  res = xQueueReceive(pcnt_evt_queue, &evt, 0);
  if (res == pdTRUE) {
    // if we got an event it means our counter is going to overflow
    pcnt_get_counter_value(evt.unit, &count);  // read counter
    // store overflow in sum so counter can be cleared
    encoders[evt.unit]->sum =
        encoders[evt.unit]->sum +
        count;  // manage overflow of 16-bit counter, currently untested
    pcnt_counter_clear(evt.unit);  // clear overflowing counter
    printf("Event PCNT unit[%d]; cnt: %d\n", evt.unit, count);
    if (evt.status & PCNT_STATUS_L_LIM_M) {
      // detect hitting min counter value
      printf("L_LIM EVT\n");
    }
    if (evt.status & PCNT_STATUS_H_LIM_M) {
      // detect hitting max counter value
      printf("H_LIM EVT\n");
    }
  } else {
    for (int i = 0; i < ACTIVE_ENCODERS; i++) {
      pcnt_get_counter_value(i, &count);
      // enc.count (real tick count)-enc.sum(sum of all overflows/underflows)
      // gives us last known value in the hardware counter which we can then
      // compare to count to determine direction
      if (count < (encoders[i]->count - encoders[i]->sum)) {
        encoders[i]->direction = backward;
      } else if (count > (encoders[i]->count - encoders[i]->sum)) {
        encoders[i]->direction = forward;
      } else {
        encoders[i]->direction = stop;
      }
      // add sum to count to keep accurate count even after counter overflow
      // warning: overflow handling not completely tested
      // real count = current counter value + sum of any overflows
      encoders[i]->count = count + encoders[i]->sum;
      // printf("Enc %d :%d\n", i, encoders[i]->count);
    }
  }
  if (user_isr_handle) {
    esp_intr_free(user_isr_handle);
    user_isr_handle = NULL;
  }
}

int getTicks(int enc_num) {
  readEncoders();
  return encoders[enc_num]->count;
}

int getAvgTicks(void) { return (getTicks(0) + getTicks(1)) / 2; }

void enc_init() {
  pcnt_evt_queue = xQueueCreate(10, sizeof(pcnt_evt_t));

  // initialize encoders using Enc struct
  encoders[right_enc] = (Enc *)malloc(sizeof(Enc));
  encoders[right_enc]->count = 0;
  encoders[right_enc]->sum = 0;
  encoders[right_enc]->direction = stop;
  encoders[right_enc]->pcnt = PCNT_UNIT_0;
  // initialize pulse counter 0 and pass in input pins of encoder
  pcnt_init(encoders[right_enc]->pcnt, 5,
            10);  // pcnt 0, A=gpio5, B=gpio10

  encoders[left_enc] = (Enc *)malloc(sizeof(Enc));
  encoders[left_enc]->count = 0;
  encoders[left_enc]->sum = 0;
  encoders[left_enc]->direction = stop;
  encoders[left_enc]->pcnt = PCNT_UNIT_1;
  // initialize pulse counter 1 and pass in input pins of encoder
  pcnt_init(encoders[left_enc]->pcnt, 25,
            26);  // pcnt 1, A=gpio25, B=gpio26
}
