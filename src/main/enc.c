#include "driver/gpio.h"
#include "enc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GPIO_INPUT_IO_0 4
#define GPIO_INPUT_IO_1 5
#define GPIO_INPUT_PIN_SEL                                                     \
  ((1ULL << GPIO_INPUT_IO_0) | (1ULL << GPIO_INPUT_IO_1))
#define ESP_INTR_FLAG_DEFAULT 0

static xQueueHandle gpio_evt_queue = NULL;

static void IRAM_ATTR gpio_isr_handler(void *arg) {
  uint32_t gpio_num = (uint32_t)arg;
  xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL);
}

static void gpio_task(void *arg) {
  uint32_t io_num;
  for (;;) {
    if (xQueueReceive(gpio_evt_queue, &io_num, portMAX_DELAY)) {
      printf("GPIO[%d] intr, val: %d\n", io_num, gpio_get_level(io_num));
      int level = gpio_get_level(io_num);
      if (io_num == GPIO_INPUT_IO_0) {
        enc.levA = level;
      } else {
        enc.levB = level;
      }

      if (io_num != enc.lastGpio) { // Debounce
        enc.lastGpio = io_num;
        if ((io_num == enc.encA) && (level == 1)) {
          if (enc.levB) {
            ++enc.pos;
          } else if ((io_num == enc.encB) && (level == 1)) {
            if (enc.levA) {
              --enc.pos;
            }
          }
        }
      }
    }
  }
}
/*
  void _cb(int gpio, int level, uint32_t tick, void *user) {
    Enc *enc = (Enc *)user;
    if (gpio == enc.encA) {
      enc.levA = level;
    } else {
      enc.levB = level;
    }
  }
*/
void enc_init() {
  enc.encA = GPIO_INPUT_IO_0;
  enc.encB = GPIO_INPUT_IO_1;
  enc.levA = 0;
  enc.levB = 0;
  enc.pos = 0;
  enc.lastGpio = -1;

  gpio_config_t io_conf;
  io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
  io_conf.mode = GPIO_MODE_INPUT;
  io_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL;
  io_conf.pull_down_en = 0;
  gpio_set_intr_type(GPIO_INPUT_IO_0, GPIO_INTR_ANYEDGE);
  gpio_set_intr_type(GPIO_INPUT_IO_1, GPIO_INTR_ANYEDGE);
  gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));
  xTaskCreate(gpio_task, "encoder_task", 2048, NULL, 10, NULL);
  gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
  gpio_isr_handler_add(GPIO_INPUT_IO_0, gpio_isr_handler,
                       (void *)GPIO_INPUT_IO_0);
  gpio_isr_handler_add(GPIO_INPUT_IO_1, gpio_isr_handler,
                       (void *)GPIO_INPUT_IO_1);
}
