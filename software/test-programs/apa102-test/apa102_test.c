#define LED_DATA_PIN 4
#define LED_CLK_PIN 32

#include "apa102.h"
#include "freertos/task.h"

uint32_t wheel(uint8_t wheel_pos) {
  if (wheel_pos < 85) {
    return RGB_COLOR(wheel_pos * 3, 255 - wheel_pos * 3, 0);
  } else if (wheel_pos < 170) {
    wheel_pos -= 85;
    return RGB_COLOR(255 - wheel_pos * 3, 0, wheel_pos * 3);
  } else {
    wheel_pos -= 170;
    return RGB_COLOR(0, wheel_pos * 3, 255 - wheel_pos * 3);
  }
}

int app_main() {
  LedStrip* leds = new_led_strip(HSPI_HOST, LED_DATA_PIN, LED_CLK_PIN, 2);

  color_single(leds, RGB_COLOR(0xFF, 0x00, 0x00));

  int j = 0;
  while (1) {
    start_sequence(leds);
    for (int i = 0; i < leds->length; i++)
      send_pixel(leds, wheel(((i * 256 / leds->length) + j++) & 255));
    end_sequence(leds);
    vTaskDelay(25 / portTICK_RATE_MS);
  }
}