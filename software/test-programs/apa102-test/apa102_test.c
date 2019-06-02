
#define LED_DATA_PIN 4
#define LED_CLK_PIN 32

#include <stdio.h>
#include <string.h>
#include "assert.h"
#include "driver/spi_master.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void send_frame(spi_device_handle_t spi, uint32_t frame) {
  esp_err_t ret;
  spi_transaction_t t;

  memset(&t, 0, sizeof(t));
  t.length = 32;         // 32 bits in a frame.
  t.tx_buffer = &frame;  // TX buffer is our frame.

  ret = spi_device_polling_transmit(spi, &t);  // Send! (polling is fine)
  assert(ret == ESP_OK);
}

// BGR for APA102s: (capital = MSB, lowercase = LSB)
// 0b11111111B------bG------gR------r
// 0bA------aB------bG------gR------r (w/brightness)
//
// The ESP32 is little-endian:
// For a 32 bit uint, the send order will be:
//   7 ... 0, 15 ... 8, 23 ... 16, 31 ... 24
//
// So, we want our packed data frame to be stored as:
// 0bR------rG-------gB------b111111111
// 0bR------rG-------gB------bA------a (w/brightness)
#define RGBA_COLOR(r, g, b, a)                                   \
  ((((r)&0xFF) << 24) | (((g)&0xFF) << 16) | (((b)&0xFF) << 8) | \
   (((a)&0xFF) | (0b11100000)))

#define RGB_COLOR(r, g, b) RGBA_COLOR(r, g, b, 0xFF)

// Assuming 0b00000000R------rG------gB------b
// Uses full brightness
#define HEX_COLOR(c) ((((c)&0x00FFFFFF) << 8) | (0xFF))

#define SEQ_START(spi) send_frame(spi, 0x00000000)
#define SEQ_END(spi) send_frame(spi, 0xFFFFFFFF)

typedef struct led_strip_t {
  uint64_t length;
  spi_device_handle_t spi_dev;
} LedStrip;

void color_single(LedStrip* strip, uint32_t color) {
  assert(strip != NULL);

  SEQ_START(strip->spi_dev);
  for (int i = 0; i < strip->length; i++) { send_frame(strip->spi_dev, color); }

  // for (int i = 0; i < strip->length; i++) {
  SEQ_END(strip->spi_dev);
  // }
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

int app_main() {
  LedStrip* leds = new_led_strip(HSPI_HOST, LED_DATA_PIN, LED_CLK_PIN, 2);

  color_single(leds, RGB_COLOR(0xFF, 0x00, 0x00));

  uint32_t d = 0;

  while (1) {
    // color_single(leds, RGB_COLOR(0x00, 0x00, 0xFF));
    color_single(leds, HEX_COLOR(d));
    // vTaskDelay(25 / portTICK_RATE_MS);
    d += 5;
    printf("yo: %#08x\n", d);
  }
}