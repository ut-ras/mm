#include "hal/movement.h"
#include "esp_timer.h"

void app_main() {
    if (init())
        exit(1);

	/*int left_read = read_distance_side(&left);
	int right_read = read_distance_side(&left);*/

    short vals[3];
    zero();
    followPBasic(30.0, vals);


	while(1) {

		//printf("Left: %d\n", read_distance_side(&left));
		//printf("Right: %d\n", read_distance_side(&right));

        //setMotors(30.0, 30.0);
		/*left_read = read_distance_side(&left);
		right_read = read_distance_side(&right);
		printf("Left: %d\n", left_read);
		vTaskDelay(10 / portTICK_RATE_MS);
		printf("Right: %d\n", right_read);*/

		/*currRead = read_distance_front(&right);
		if (currRead > 250 && currRead - lastRead > 10) {
			setMotors(20.0, 10.0);
		} else if (currRead < 250 && currRead - lastRead < 10) {
			setMotors(10.0, 20.0);
		} else {
			setMotors(20.0, 20.0);
		}*/

	}
}
