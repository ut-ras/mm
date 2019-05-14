#include "movement.h"
#include "distance.h"
#include "enc.h"
#include "motorController.h"
#include "pid.h"

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

PID irPID;

int init() {
  if (init_distance_sensor(&left, LEFT_FRONT_PIN, LEFT_SIDE_PIN,
                           LEFT_EMITTER)) {
    printf("Init sensor left failed");
    return 1;
  }
  if (init_distance_sensor(&right, RIGHT_FRONT_PIN, RIGHT_SIDE_PIN,
                           RIGHT_EMITTER)) {
    printf("Init sensor right failed");
    return 2;
  }

  // Initialize Encoders
  enc_init();

  // mcpwm_example_gpio_initialize();
  mcpwm_initialize();

  initPID(&irPID, 0.01, 0.01, 0.000);
  set(irPID, 0);

  return 0;
}

void zero(void) {
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

static int calculateIRError() {
  int dists[2];

  read_distance(&left, dists);
  int frontLeft = dists[0];
  int sideLeft = dists[1];

  read_distance(&right, dists);
  int frontRight = dists[0];
  int sideRight = dists[1];

  return (LEFT_SIDE_ZERO - sideLeft) + (sideRight - RIGHT_SIDE_ZERO);
}

struct movement_info moveIR(float speed) {

  double lastTime = esp_timer_get_time() / 1000000;
  double currentTime = lastTime;

  while (frontLeft < LEFT_FRONT_THRES && frontRight < RIGHT_FRONT_THRESH && sideLeft > LEFT_SIDE_THRESH && sideRiht > RIGHT_SIDE_THRESH) {
    
    double currentTime = esp_timer_get_time() / 1000000;

    double curr = update(&irPID, calculateIRError(), currentTime - lastTime);
    setMotors(speed - curr, speed + curr);
  }

  struct movement_info mov;

  return mov;
}

void followPBasic(float maxSpeed, short *walls) {
  int dists[2];

  read_distance(&left, dists);
  int frontLeft = dists[0];
  int sideLeft = dists[1];

  read_distance(&right, dists);
  int frontRight = dists[0];
  int sideRight = dists[1];

  int error;

  while (/*frontLeft > LEFT_FRONT_THRESH && frontRight > RIGHT_FRONT_THRESH
           && sideLeft < LEFT_SIDE_THRESH && sideRight < RIGHT_SIDE_THRESH*/
         1) {

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
  walls[1] = (frontLeft > LEFT_FRONT_THRESH && frontRight > RIGHT_FRONT_THRESH)
                 ? 0
                 : 1;
}
