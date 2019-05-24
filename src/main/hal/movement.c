#include "movement.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "distance.h"
#include "enc.h"
#include "motorController.h"
#include "pid.h"

#define MAZE_UNIT_SIZE 200

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

PID* irPID;

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

  irPID = initPID(0.001, 0.00, 0.000, "log");
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

struct movement_info getWalls(void) {
  int leftDists[2];
  int rightDists[2];

  read_distance(&left, leftDists);
  LEFT_FRONT_ZERO = leftDists[0];
  LEFT_SIDE_ZERO = leftDists[1];

  read_distance(&right, rightDists);
  RIGHT_FRONT_ZERO = rightDists[0];
  RIGHT_SIDE_ZERO = rightDists[1];

  struct movement_info info;
  info.left = leftDists[1] > LEFT_SIDE_THRESH;
  info.right = rightDists[1] > RIGHT_SIDE_THRESH;
  info.front = leftDists[0] > LEFT_FRONT_THRESH || rightDists[0] > RIGHT_FRONT_THRESH;

  return info;
}

static int readIRError(int* frontLeft, int* sideLeft, int* frontRight, int* sideRight) {
  int dists[2];

  read_distance(&left, dists);
  *frontLeft = dists[0];
  *sideLeft = dists[1];

  read_distance(&right, dists);
  *frontRight = dists[0];
  *sideRight = dists[1];

  return (LEFT_SIDE_ZERO - *sideLeft) + (*sideRight - RIGHT_SIDE_ZERO);
}

struct movement_info moveIR(float speed) {

  double lastTime = esp_timer_get_time() / 1000000.0;
  double currentTime;

  int frontLeft;
  int sideLeft;
  int frontRight;
  int sideRight;

  double startEnc = (getTicks(0) + getTicks(1)) / 2;

  while (1/*(frontLeft < LEFT_FRONT_THRESH || frontRight < RIGHT_FRONT_THRESH) && sideLeft > LEFT_SIDE_THRESH && sideRight > RIGHT_SIDE_THRESH*/) {
    
    currentTime = esp_timer_get_time() / 1000000.0;
    double diffTime = currentTime - lastTime;
    lastTime = currentTime;

    double curr = update(irPID, readIRError(&frontLeft, &sideLeft, &frontRight, &sideRight), diffTime);
    printf("curr %f\n", curr);
    setMotors(speed + curr, speed - curr);
  }

  struct movement_info info = getWalls();

  info.unitsTraveled = (((getTicks(0) + getTicks(1)) / 2) - startEnc) / MAZE_UNIT_SIZE;

  return info;
}
