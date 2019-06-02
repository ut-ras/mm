#include "movement.h"
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include "battery.h"
#include "distance.h"
#include "enc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "motorController.h"
#include "pid.h"

#define LEFT_FRONT_PIN 37
#define LEFT_SIDE_PIN 38
#define LEFT_EMITTER 15

#define RIGHT_FRONT_PIN 34
#define RIGHT_SIDE_PIN 35
#define RIGHT_EMITTER 2

#define TURN_TICKS 90
#define ENC_DIFF 0

#define MOVE_DELAY 200

int LEFT_SIDE_ZERO = 510;
int LEFT_SIDE_THRESH = 200;
int RIGHT_SIDE_ZERO = 590;
int RIGHT_SIDE_THRESH = 5;

int LEFT_FRONT_ZERO = 300;
int LEFT_FRONT_THRESH = 400;
int RIGHT_FRONT_ZERO = 300;
int RIGHT_FRONT_THRESH = 300;

distance left;
distance right;

PID* movePID;
PID* turn90PID;
PID* turn180PID;
PID* moveEncPID;
PID* turnDegreePID;

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

  movePID = initPID(0.002, 0.0002, 0.0, "log");

  turn90PID = initPID(0.8, 0.1, 0.0, "log");

  turn180PID = initPID(0.00416, 0.0035, 0.0, "log");

  moveEncPID = initPID(0.04, 0, 0, "log");

  turnDegreePID = initPID(0.1, 0.05, 0.00, "log");

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

struct movement_info getWalls(int* lsensor, int* rsensor) {
  int leftDists[2];
  int rightDists[2];

  read_distance(&left, leftDists);

  read_distance(&right, rightDists);

  struct movement_info info;
  info.left = leftDists[1] > LEFT_SIDE_THRESH;
  info.right = rightDists[1] > RIGHT_SIDE_THRESH;

  /*info.front = false;
  if (info.left)
    info.front |= leftDists[0] > LEFT_FRONT_THRESH;
  if (info.right)
      info.front |= rightDists[0] > RIGHT_FRONT_THRESH;
  if (!info.left && !info.right)
    info.front = leftDists[0] > LEFT_FRONT_THRESH || rightDists[0] >
  RIGHT_FRONT_THRESH;*/

  info.front = (leftDists[0] > LEFT_FRONT_THRESH && leftDists[1] < 1000) ||
               (rightDists[0] > RIGHT_FRONT_THRESH && rightDists[1] < 1500);

  if (lsensor) *lsensor = leftDists[1];
  if (rsensor) *rsensor = rightDists[1];

  return info;
}

static int calcIRError(int sideLeft, int sideRight) {
  return (LEFT_SIDE_ZERO - sideLeft) + (sideRight - RIGHT_SIDE_ZERO);
}

struct movement_info moveIR(float speed) {
  double lastTime = esp_timer_get_time() / 1000000.0;
  double currentTime;

  int sideLeft;
  int sideRight;

  set(movePID, 0);

  int startEnc = getAbsAvgTicks();
  int leftStart = abs(getTicks(left_enc));
  int rightStart = abs(getTicks(right_enc));

  struct movement_info info = getWalls(&sideLeft, &sideRight);
  calcIRError(sideLeft, sideRight);

  while (!info.front && info.left && info.right) {
    currentTime = esp_timer_get_time() / 1000000.0;
    double diffTime = currentTime - lastTime;
    lastTime = currentTime;

    double curr = update(movePID, calcIRError(sideLeft, sideRight), diffTime);
    // printf("sens %d %d\n", frontLeft, frontRight);
    // printf("curr %f %d \n", curr, readIRError(&frontLeft, &sideLeft,
    // &frontRight, &sideRight));
    setMotors(speed + curr, speed - curr);
    info = getWalls(&sideLeft, &sideRight);
  }
  stopMotors();

  vTaskDelay(MOVE_DELAY / portTICK_RATE_MS);

  info = getWalls(NULL, NULL);

  info.ticksTraveled = (getAbsAvgTicks() - startEnc);
  int encDiff = (abs(getTicks(left_enc)) - leftStart) -
                (abs(getTicks(right_enc)) - rightStart);

  // turnDegrees(encDiff > 0 ? -8.5 : 8.5, abs(encDiff));

  return info;
}

static int turnProg(int start) { return abs(getAvgTicks() - start); }

static double pid_get_time() { return esp_timer_get_time() / 1000000.0; }

inline static double signum(double num) { return num < 0.0 ? -1.0 : 1.0; }

struct movement_info turn90(float speed) {
  assert(speed != 0);

  double sign = signum(speed);

  double lastTime = pid_get_time();
  double currentTime = pid_get_time();
  double diffTime = currentTime - lastTime;

  double target = TURN_TICKS;
  set(turn90PID, target);

  int start = getAvgTicks();
  int current = start;

  double timeReachedAt = currentTime;

  while (true) {
    // Update the times:
    currentTime = pid_get_time();
    diffTime = currentTime - lastTime;
    lastTime = currentTime;

    // Once we get close to our setpoint, let timeReachedAt indicate when it
    // happened.
    if (fabs(target - current) > 1) timeReachedAt = currentTime;

    // Once we've been close to our setpoint for long enough, bail
    if ((currentTime - timeReachedAt) >= 0.05) break;

    // Otherwise, update the motors and keep going:
    current = turnProg(start);
    double distPower = update(turn90PID, current, diffTime);

    setMotors(sign * distPower, -sign * distPower);
  }

  stopMotors();
  vTaskDelay(MOVE_DELAY / portTICK_RATE_MS);

  struct movement_info info = getWalls(NULL, NULL);

  return info;
}

struct movement_info turn180(float speed) {
  double lastTime = esp_timer_get_time() / 1000000.0;
  double currentTime = esp_timer_get_time() / 1000000.0;
  double diffTime = currentTime - lastTime;

  set(turn180PID, TURN_TICKS * 2);

  int start = getAvgTicks();

  while (fabs((double)TURN_TICKS * 2 - turnProg(start) - turn180PID->last) /
                 diffTime >
             1.0 ||
         TURN_TICKS * 2 - turnProg(start) > 1) {
    currentTime = esp_timer_get_time() / 1000000.0;
    diffTime = currentTime - lastTime;
    lastTime = currentTime;

    double distPower = update(turn180PID, turnProg(start), diffTime);
    // printf("turnProg %d distPower %f\n", turnProg(start), distPower);

    setMotors(speed * distPower, -speed * distPower);
  }
  stopMotors();
  vTaskDelay(MOVE_DELAY / portTICK_RATE_MS);

  struct movement_info info = getWalls(NULL, NULL);

  return info;
}

struct movement_info turnDegrees(float speed, float angle) {
  double lastTime = esp_timer_get_time() / 1000000.0;
  double currentTime = esp_timer_get_time() / 1000000.0;
  double diffTime = currentTime - lastTime;

  int goal = (TURN_TICKS * angle) / 90;
  set(turnDegreePID, goal);

  int start = getAvgTicks();

  while (fabs((double)goal - turnProg(start) - turnDegreePID->last) / diffTime >
             1.0 ||
         goal - turnProg(start) > 1) {
    currentTime = esp_timer_get_time() / 1000000.0;
    diffTime = currentTime - lastTime;
    lastTime = currentTime;

    double distPower = update(turnDegreePID, turnProg(start), diffTime);
    // printf("turnProg %d distPower %f\n", turnProg(start), distPower);

    setMotors(speed * distPower, -speed * distPower);
  }
  stopMotors();
  vTaskDelay(MOVE_DELAY / portTICK_RATE_MS);

  struct movement_info info = getWalls(NULL, NULL);

  return info;
}
struct movement_info moveEnc(float speed, int32_t encoderTicks) {
  double lastTime = esp_timer_get_time() / 1000000.0;
  double currentTime = esp_timer_get_time() / 1000000.0;
  double diffTime = currentTime - lastTime;

  int start = getAbsAvgTicks();
  int startLeft = abs(getTicks(left_enc));
  int startRight = abs(getTicks(right_enc));

  set(moveEncPID, ENC_DIFF);
  struct movement_info info;

  int leftDiff = 0;
  int rightDiff = 0;

  while (getAbsAvgTicks() - start < encoderTicks && !info.front) {
    currentTime = esp_timer_get_time() / 1000000.0;
    diffTime = currentTime - lastTime;
    lastTime = currentTime;

    leftDiff = abs(getTicks(left_enc)) - startLeft;
    rightDiff = abs(getTicks(right_enc)) - startRight;

    double correction = update(moveEncPID, leftDiff - rightDiff, diffTime);
    /*printf("corr %f\n", correction);
    printf("leftDiff %d rightDiff %d\n", leftDiff, rightDiff);
    printf("current %d", abs(getAvgTicks() - start));*/

    setMotors(speed + correction, speed - correction);
    info = getWalls(NULL, NULL);
  }
  stopMotors();
  vTaskDelay(MOVE_DELAY / portTICK_RATE_MS);

  int encDiff = leftDiff - rightDiff;
  // turnDegrees(encDiff > 0 ? -8.5 : 8.5, abs(encDiff));

  info = getWalls(NULL, NULL);

  info.ticksTraveled = (getAbsAvgTicks() - start);

  return info;
}

struct movement_info moveEncU(float speed) {
  double lastTime = esp_timer_get_time() / 1000000.0;
  double currentTime = esp_timer_get_time() / 1000000.0;
  double diffTime = currentTime - lastTime;

  int start = getAbsAvgTicks();

  int startLeft = abs(getTicks(left_enc));
  int startRight = abs(getTicks(right_enc));

  set(moveEncPID, ENC_DIFF);

  struct movement_info info = getWalls(NULL, NULL);

  while (!info.front && info.left && info.right) {
    currentTime = esp_timer_get_time() / 1000000.0;
    diffTime = currentTime - lastTime;
    lastTime = currentTime;

    int leftDiff = abs(getTicks(left_enc)) - startLeft;
    int rightDiff = abs(getTicks(right_enc)) - startRight;

    double correction = update(moveEncPID, leftDiff - rightDiff, diffTime);
    /*printf("corr %f\n", correction);
    printf("leftDiff %d rightDiff %d\n", leftDiff, rightDiff);
    printf("current %d", abs(getAvgTicks() - start));*/

    setMotors(speed + correction, speed - correction);

    info = getWalls(NULL, NULL);
  }
  stopMotors();
  vTaskDelay(MOVE_DELAY / portTICK_RATE_MS);

  info = getWalls(NULL, NULL);

  info.ticksTraveled = (getAbsAvgTicks() - start);

  return info;
}
