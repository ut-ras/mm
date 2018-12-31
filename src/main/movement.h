#include "distance.h"
#include "motorController.c"
#include <math.h>

#define PCONST 0.004

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

	mcpwm_example_gpio_initialize();
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

void setMotorsPidBasic(int error, float maxSpeed) {
	float speedReduc = abs(error * PCONST);
	if (error > 10)
		setMotors(maxSpeed - speedReduc, maxSpeed);
	else if (error < 10)
		setMotors(maxSpeed, maxSpeed - speedReduc);
	else
		setMotors(maxSpeed, maxSpeed);
}

void moveUntilInter(float maxSpeed, short* walls) {
	int dists[2];

	read_distance(&left, dists);
	int frontLeft = dists[0];
	int sideLeft = dists[1];

	read_distance(&right, dists);
	int frontRight = dists[0];
	int sideRight = dists[1];
	
	int currError = (LEFT_SIDE_ZERO - sideLeft + sideRight - RIGHT_SIDE_ZERO) / 2;
	int lastError = currError;

	while(frontLeft > LEFT_FRONT_THRESH && frontRight > RIGHT_FRONT_THRESH
		&& sideLeft < LEFT_SIDE_THRESH && sideRight < RIGHT_SIDE_THRESH) {
		currError = (LEFT_SIDE_ZERO - sideLeft + sideRight - RIGHT_SIDE_ZERO) / 2;
		setMotorsPidBasic(currError, maxSpeed);
	}

	walls[0] = sideLeft < LEFT_SIDE_THRESH ? 1 : 0;
	walls[2] = sideRight < RIGHT_SIDE_THRESH ? 1 : 0;
	walls[1] = (frontLeft > LEFT_FRONT_THRESH && frontRight > RIGHT_FRONT_THRESH) ? 0 : 1;
}