#ifndef APA102_H
#define APA102_H

#include <stdint.h>
#include "driver/spi_master.h"

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

typedef struct led_strip_t {
  uint64_t length;
  spi_device_handle_t spi_dev;
} LedStrip;

void start_sequence(LedStrip* strip);

void end_sequence(LedStrip* strip);

void send_pixel(LedStrip* strip, uint32_t color);

void color_single(LedStrip* strip, uint32_t color);

LedStrip* new_led_strip(spi_host_device_t host, int data_pin, int clk_pin,
                        uint16_t length);

#endif /* APA102_H */
