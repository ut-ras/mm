#include "movement.h"
#include <math.h>
#include <stdlib.h>
#include "battery.h"
#include "distance.h"
#include "enc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "motorController.h"
#include "pid.h"

#define MAZE_UNIT_SIZE 200

#define LEFT_FRONT_PIN 37
#define LEFT_SIDE_PIN 38
#define LEFT_EMITTER 15

#define RIGHT_FRONT_PIN 34
#define RIGHT_SIDE_PIN 35
#define RIGHT_EMITTER 2

#define TURN_TICKS 90

#define MOVE_DELAY 200

int LEFT_SIDE_ZERO = 100;
int LEFT_SIDE_THRESH = 10;
int RIGHT_SIDE_ZERO = 100;
int RIGHT_SIDE_THRESH = 10;

int LEFT_FRONT_ZERO = 250;
int LEFT_FRONT_THRESH = 750;
int RIGHT_FRONT_ZERO = 250;
int RIGHT_FRONT_THRESH = 550;

distance left;
distance right;

PID* movePID;
PID* turn90PID;
PID* turn180PID;

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

  movePID = initPID(0.002, 0.0003, 0.0, "log");

  turn90PID = initPID(0.0111, 0.0061, 0.0, "log");

  turn180PID = initPID(0.004, 0.0041, 0.0, "log");

  initBattery();

  printf("Battery: %d\n", getBatteryVal());

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

  read_distance(&right, rightDists);

  struct movement_info info;
  info.left = leftDists[1] > LEFT_SIDE_THRESH;
  info.right = rightDists[1] > RIGHT_SIDE_THRESH;
  info.front =
      leftDists[0] > LEFT_FRONT_THRESH || rightDists[0] > RIGHT_FRONT_THRESH;

  return info;
}

static int readIRError(int* frontLeft, int* sideLeft, int* frontRight,
                       int* sideRight) {
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

  set(movePID, 0);

  int startEnc = getAvgTicks();

  readIRError(&frontLeft, &sideLeft, &frontRight, &sideRight);

  while ((frontLeft < LEFT_FRONT_THRESH || frontRight < RIGHT_FRONT_THRESH) &&
         sideLeft > LEFT_SIDE_THRESH && sideRight > RIGHT_SIDE_THRESH) {
    currentTime = esp_timer_get_time() / 1000000.0;
    double diffTime = currentTime - lastTime;
    lastTime = currentTime;

    double curr = update(
        movePID, readIRError(&frontLeft, &sideLeft, &frontRight, &sideRight),
        diffTime);
    // printf("sens %d %d\n", frontLeft, frontRight);
    // printf("curr %f %d \n", curr, readIRError(&frontLeft, &sideLeft,
    // &frontRight, &sideRight));
    setMotors(speed + curr, speed - curr);
  }
  stopMotors();
  vTaskDelay(MOVE_DELAY / portTICK_RATE_MS);

  struct movement_info info = getWalls();

  info.unitsTraveled = (getAvgTicks() - startEnc) / MAZE_UNIT_SIZE;

  return info;
}

static int turnProg(int start) { return abs(getAvgTicks() - start); }

struct movement_info turn90(float speed) {
  double lastTime = esp_timer_get_time() / 1000000.0;
  double currentTime = esp_timer_get_time() / 1000000.0;
  double diffTime = currentTime - lastTime;

  set(turn90PID, TURN_TICKS);

  int start = getAvgTicks();

  while (fabs((double)TURN_TICKS - turnProg(start) - turn90PID->last) /
                 diffTime >
             1.0 ||
         TURN_TICKS - turnProg(start) > 1) {
    currentTime = esp_timer_get_time() / 1000000.0;
    diffTime = currentTime - lastTime;
    lastTime = currentTime;

    double distPower = update(turn90PID, turnProg(start), diffTime);
    // printf("turnProg %d distPower %f\n", turnProg(start), distPower);

    setMotors(speed * distPower, -speed * distPower);
  }
  stopMotors();
  vTaskDelay(MOVE_DELAY / portTICK_RATE_MS);

  struct movement_info info = getWalls();

  return info;
}

struct movement_info turn180(float speed) {
  double lastTime = esp_timer_get_time() / 1000000.0;
  double currentTime = esp_timer_get_time() / 1000000.0;
  double diffTime = currentTime - lastTime;

  set(turn180PID, TURN_TICKS * 2 + 1);

  int start = getAvgTicks();

  while (fabs((double)TURN_TICKS * 2 + 1 - turnProg(start) - turn180PID->last) /
                 diffTime >
             1.0 ||
         TURN_TICKS * 2 + 1 - turnProg(start) > 1) {
    currentTime = esp_timer_get_time() / 1000000.0;
    diffTime = currentTime - lastTime;
    lastTime = currentTime;

    double distPower = update(turn180PID, turnProg(start), diffTime);
    // printf("turnProg %d distPower %f\n", turnProg(start), distPower);

    setMotors(speed * distPower, -speed * distPower);
  }
  stopMotors();
  vTaskDelay(MOVE_DELAY / portTICK_RATE_MS);

  struct movement_info info = getWalls();

  return info;
}
