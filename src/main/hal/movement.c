#include "distance.h"
#include "movement.h"
#include "motorController.h"
#include "enc.h"
#include <math.h>

#define PCONST 0.0075

#define LEFT_FRONT_PIN 37
#define LEFT_SIDE_PIN 38
#define LEFT_EMITTER 15

#define RIGHT_FRONT_PIN 34
#define RIGHT_SIDE_PIN 35
#define RIGHT_EMITTER 2

int LEFT_SIDE_ZERO = 250;
int LEFT_SIDE_THRESH = 1000;
int RIGHT_SIDE_ZERO = 250;
int RIGHT_SIDE_THRESH = 1000;

int LEFT_FRONT_ZERO = 250;
int LEFT_FRONT_THRESH = 1000;
int RIGHT_FRONT_ZERO = 250;
int RIGHT_FRONT_THRESH = 1000;

distance left;
distance right;

void setMotors(float left, float right) {
	setLeftSpeed(left);
	setRightSpeed(right);
}

int init() {
	if (init_distance_sensor(&left, LEFT_FRONT_PIN, LEFT_SIDE_PIN, LEFT_EMITTER)) {
		printf("Init sensor left failed");
		return 1;
	}
	if (init_distance_sensor(&right, RIGHT_FRONT_PIN, RIGHT_SIDE_PIN, RIGHT_EMITTER)) {
		printf("Init sensor right failed");
		return 2;
	}

    //Initialize Encoders
    enc_init();


	//mcpwm_example_gpio_initialize();
    mcpwm_initialize();

	return 0;
}

void zero() {
	int dists[2];

	read_distance(&left, dists);
	LEFT_FRONT_ZERO = dists[0];
	LEFT_SIDE_ZERO = dists[1];

	read_distance(&right, dists);
	RIGHT_FRONT_ZERO = dists[0];
	RIGHT_SIDE_ZERO = dists[1];
}

void setMotorsP(int error, float maxSpeed) {
	float speedReduc = error * PCONST;
    setMotors(maxSpeed - speedReduc, maxSpeed + speedReduc + 18);
}

/*void followP(float maxSpeed, short* walls) {
	int dists[2];

	read_distance(&left, dists);
	int frontLeftLast = dists[0];
	int sideLeftLast = dists[1];

	read_distance(&right, dists);
	int frontRightLast = dists[0];
	int sideRightLast = dists[1];

    int error = 0;

    uint64_t prevTime = (uint64_t)esp_timer_get_time();

	while(frontLeft > LEFT_FRONT_THRESH && frontRight > RIGHT_FRONT_THRESH
		&& sideLeft < LEFT_SIDE_THRESH && sideRight < RIGHT_SIDE_THRESH) {
        setMotorsP(error, maxSpeed);

        read_distance(&left, dists);
        int frontLeftCurr = dists[0];
	    int sideLeftCurr = dists[1];

        read_distance(&right, dists);
        int frontRightCurr = dists[0];
        int sideRightCurr = dists[1];

	}

	walls[0] = sideLeft < LEFT_SIDE_THRESH ? 1 : 0;
	walls[2] = sideRight < RIGHT_SIDE_THRESH ? 1 : 0;
	walls[1] = (frontLeft > LEFT_FRONT_THRESH && frontRight > RIGHT_FRONT_THRESH) ? 0 : 1;
}*/

void followPBasic(float maxSpeed, short* walls) {
    int dists[2];

	read_distance(&left, dists);
	int frontLeft = dists[0];
	int sideLeft = dists[1];

	read_distance(&right, dists);
	int frontRight = dists[0];
	int sideRight = dists[1];

    int error;

	while(/*frontLeft > LEFT_FRONT_THRESH && frontRight > RIGHT_FRONT_THRESH
		&& sideLeft < LEFT_SIDE_THRESH && sideRight < RIGHT_SIDE_THRESH*/1) {

        read_distance(&left, dists);
        frontLeft = dists[0];
	    sideLeft = dists[1];

        read_distance(&right, dists);
        frontRight = dists[0];
        sideRight = dists[1];

        error = (LEFT_SIDE_ZERO - sideLeft) + (sideRight - RIGHT_SIDE_ZERO);
        printf("error: %d l: %d r: %d\n", error, sideLeft, sideRight);
        setMotorsP(error, maxSpeed);
	}

	walls[0] = sideLeft < LEFT_SIDE_THRESH ? 1 : 0;
	walls[2] = sideRight < RIGHT_SIDE_THRESH ? 1 : 0;
	walls[1] = (frontLeft > LEFT_FRONT_THRESH && frontRight > RIGHT_FRONT_THRESH) ? 0 : 1;
}
