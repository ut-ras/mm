#include "movement.h"
#include "pid.h"
#include <stdio.h>

#define NUM_MOTORS 2

const int ticksPerUnit = 2200 / 26;
double maxSpeed = .30; // percentage

enum axis { horizontal, vertical };

PID *linearControl[2];
PID *rotationControl;
PID *alignmentControl;

// Run all control loops in series
double gains[NUM_MOTORS];
void controlUpdate(double elapsed) {
  for (int i = 0; i < NUM_MOTORS; ++i) {
    gains[i] = linearControl[i]->update(getTicks(i), elapsed);
  }
  // double angularCorrection = rotationControl->update(mpu input here);
  // double alignmentCorrection = alignmentControl->update(vlx input here);

  // optional velocity pid here to sacrifice positional precision for
  // more easily regulated acceleration
  setMotors(max(min(gains[0], maxSpeed), -maxSpeed),
            max(min(gains[1], maxSpeed), -maxSpeed));
}

// TODO: Micromouse move straight
/*
const int steady = 10;
const int threshold = 35;
void moveStraight(int dist, axis dir) {
  cout << "Starting to move straight for dist: " << dist << endl;
  int s, us;
  gpioTime(0, &s, &us);
  int ready = 0;
  double currentTime, lastTime = (double(s) * 1000 + double(us / 1000)) / 1000;
  for (int i = 0; i < 4; ++i) {
    motors[i]->zero();
    linearControl[i]->set(0);
  }
  if (dir == horizontal) {
    linearControl[0]->set(dist * 1);
    linearControl[1]->set(dist * -1);
  } else if (dir == vertical) {
    linearControl[2]->set(dist * 1);
    linearControl[3]->set(dist * -1);
  }
  // block until you're close enough to the set point for long enough
  while (ready < steady) {
    // cout << "Getting there.. " << ready << "/" << steady << endl;
    // cout << "Top: " << motors[0]->getTicks() <<
    //      "\tBottom: " << motors[1]->getTicks() <<
    //      "\tLeft: " << motors[2]->getTicks() <<
    //      "\tRight: " << motors[3]->getTicks() << endl;
    gpioTime(0, &s, &us);
    currentTime = (double(s) * 1000 + double(us / 1000)) / 1000;
    controlUpdate(currentTime - lastTime);
    time_sleep(.01); // run pid around 20 times per second
    ++ready;
    for (int i = 0; i < NUM_MOTORS; ++i) {
      if (linearControl[i]->getErr() > threshold) {
        // cout << "holdup: " << linearControl[i]->getErr() << endl;
        ready = 0;
        break;
      }
    }
    lastTime = currentTime;
  }
  printf("got there\n");
}
*/

void selfTest() {
  for (int i = 0; i < NUM_MOTORS; ++i) {
    motors[i]->set(.25);
    vTaskDelay(1000);
    motors[i]->stop();
    printf("Motor %d at %d ticks\n", i, getTicks(i));
  }
}

void hardStop() {
  for (int i = 0; i < NUM_MOTORS; ++i) {
    motors[i]->stop();
  }
}

void printEnc() { printf("Left: %d\tRight: %d\n", getTicks(0), getTicks(1)); }

void setSpeed(double speed) { maxSpeed = speed; }

void moveDir(int dist, int dir) {
  printf("moving %d units in direction: %d\n", dist, dir);
  dist *= ticksPerUnit;
  switch (dir) {
  case 0:
    moveStraight(-dist, vertical);
    break;
  case 1:
    moveStraight(dist, vertical);
    break;
  case 2:
    moveStraight(-dist, horizontal);
    break;
  case 3:
    moveStraight(dist, horizontal);
    break;
  default:
    printf("Invalid direction, stopping\n");
    hardStop(self, args);
    break;
  }
  hardStop(self, args);
}

void initRobot(PyObject *self, PyObject *args) {
  // TODO: Initialize Motors
  for (int i = 0; i < NUM_MOTORS; ++i) {
    linearControl[i] = new PID(.01, .01, .0003);
  }
  // rotationControl = new PID(p, i, d);
  // alignmentControl = new PID(p, i, d);
}
