#include "movement.h"

void app_main() {
  enc_init();

  int lastRead = read_distance_side(&left);
  int currRead = read_distance_side(&left);

  while (1) {

    // printf("Left: %d\n", read_distance_side(&left));
    // printf("Right: %d\n", read_distance_side(&right));
    /*
        printf("Left: %d\n", currRead);
        vTaskDelay(10 / portTICK_RATE_MS);
        currRead = read_distance_side(&left);
        if (currRead > 250 && currRead - lastRead > 10) {
          setMotors(20.0, 10.0);
        } else if (currRead < 250 && currRead - lastRead < 10) {
          setMotors(10.0, 20.0);
        } else {
          setMotors(20.0, 20.0);
        }
        */
    readEncoders();
    printf("encoder %d -> %d, direction %d\n", 0, getTicks(0),
           encoders[0]->direction);
    printf("encoder %d -> %d, direction %d\n", 1, getTicks(1),
           encoders[1]->direction);
    vTaskDelay(10 / portTICK_RATE_MS);
  }
}
