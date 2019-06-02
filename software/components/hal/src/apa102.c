#include "apa102.h"
#include <stdio.h>
#include <string.h>
#include "assert.h"
#include "driver/spi_master.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define REPEATED_END false

static void send_frame(spi_device_handle_t spi, uint32_t frame) {
  esp_err_t ret;
  spi_transaction_t t;

  memset(&t, 0, sizeof(t));
  t.length = 32;         // 32 bits in a frame.
  t.tx_buffer = &frame;  // TX buffer is our frame.

  ret = spi_device_polling_transmit(spi, &t);  // Send! (polling is fine)
  assert(ret == ESP_OK);
}

#define SEQ_START(spi) send_frame(spi, 0x00000000)
#define SEQ_END(spi) send_frame(spi, 0xFFFFFFFF)

void send_pixel(LedStrip* strip, uint32_t color) {
  assert(strip != NULL);
  send_frame(strip->spi_dev, color);
}

inline void start_sequence(LedStrip* strip) {
  assert(strip != NULL);
  SEQ_START(strip->spi_dev);
}

inline void end_sequence(LedStrip* strip) {
  assert(strip != NULL);
  SEQ_END(strip->spi_dev);

  if (REPEATED_END) {
    for (int i = 0; i < strip->length; i++) { SEQ_END(strip->spi_dev); }
  }
}

void color_single(LedStrip* strip, uint32_t color) {
  assert(strip != NULL);

  start_sequence(strip);
  for (int i = 0; i < strip->length; i++) { send_frame(strip->spi_dev, color); }
  end_sequence(strip);
}

LedStrip* new_led_strip(spi_host_device_t host, int data_pin, int clk_pin,
                        uint16_t length) {
  LedStrip* strip = malloc(sizeof(LedStrip));
  assert(strip != NULL);

  spi_bus_config_t bus_cfg = {
      .miso_io_num = -1,    // Unused
      .quadwp_io_num = -1,  // Unused
      .quadhd_io_num = -1,  // Unused
      .mosi_io_num = data_pin,
      .sclk_io_num = clk_pin,
  };

  spi_device_interface_config_t dev_cfg = {
      .clock_speed_hz = 1200 * 1000,  // 1.2 MHz
      // .mode = 0,
      .spics_io_num = -1,  // Unused
      .queue_size = 5,
      .pre_cb = NULL,
  };

  ESP_ERROR_CHECK(spi_bus_initialize(host, &bus_cfg, 1));  // DMA Channel 1
  ESP_ERROR_CHECK(spi_bus_add_device(host, &dev_cfg, &(strip->spi_dev)));

  strip->length = length;

  return strip;
}

void free_led_strip(LedStrip* strip) {
  if (strip == NULL) return;

  spi_bus_remove_device(strip->spi_dev);
  free(strip);
}
