#include "enc.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "movement.h"
#include "pid.h"
#include <stdio.h>

#define NUM_MOTORS 2

PID *linearControl[2];
PID *alignmentControl;

const int ticksPerUnit = 2200 / 26;
double maxSpeed = .30; // percentage

double max(double val1, double val2) { return val1 > val2 ? val1 : val2; }

double min(double val1, double val2) { return val1 < val2 ? val1 : val2; }

// Run all control loops in series
double gains[NUM_MOTORS];
void controlUpdate(double elapsed) {
  for (int i = 0; i < NUM_MOTORS; ++i) {
    gains[i] = update(linearControl[i], getTicks(i), elapsed);
  }
  // double angularCorrection = rotationControl->update(mpu input here);
  // double alignmentCorrection = alignmentControl->update(vlx input here);

  // optional velocity pid here to sacrifice positional precision for
  // more easily regulated acceleration
  setMotors(max(min(gains[0], maxSpeed), -maxSpeed),
            max(min(gains[1], maxSpeed), -maxSpeed));
}

const int steady = 10;
const int threshold = 35;
void moveStraight(int dist) {
  printf("Starting to move straight for dist: %d\n", dist);
  int ready = 0;
  // double currentTime, lastTime =
  // (double(s) * 1000 + double(us / 1000)) / 1000;
  double currentTime, lastTime = esp_timer_get_time() / 1000000;
  setMotors(0, 0);
  for (int i = 0; i < NUM_MOTORS; ++i) {
    set(linearControl[i], 0);
  }
  set(linearControl[0], dist * 1);
  set(linearControl[1], dist * -1);
  // block until you're close enough to the set point for long enough
  while (ready < steady) {
    // cout << "Getting there.. " << ready << "/" << steady << endl;
    // cout << "Top: " << motors[0]->getTicks() <<
    //      "\tBottom: " << motors[1]->getTicks() <<
    //      "\tLeft: " << motors[2]->getTicks() <<
    //      "\tRight: " << motors[3]->getTicks() << endl;
    // currentTime = (double(s) * 1000 + double(us / 1000)) / 1000;
    currentTime = esp_timer_get_time() / 1000000;
    controlUpdate(currentTime - lastTime);
    vTaskDelay(10);
    ++ready;
    for (int i = 0; i < NUM_MOTORS; ++i) {
      if (getErr(linearControl[i]) > threshold) {
        // cout << "holdup: " << linearControl[i]->getErr() << endl;
        ready = 0;
        break;
      }
    }
    lastTime = currentTime;
  }
  printf("got there\n");
}

void selfTest() {
  setMotors(.25, .25);
  vTaskDelay(1000);
  setMotors(0, 0);
  printf("Motor %d at %d ticks\n", 0, getTicks(0));
  printf("Motor %d at %d ticks\n", 1, getTicks(1));
}

void hardStop() { setMotors(0, 0); }

void printEnc() { printf("Left: %d\tRight: %d\n", getTicks(0), getTicks(1)); }

void setSpeed(double speed) { maxSpeed = speed; }

void initRobot() {
  // TODO: Initialize Motors
  for (int i = 0; i < NUM_MOTORS; ++i) {
    linearControl[i] = initPID(.01, .01, .0003, "log");
  }
  // rotationControl = new PID(p, i, d);
  // alignmentControl = new PID(p, i, d);
}
