#ifndef PID_H
#define PID_H

#include <stdio.h>

typedef struct {
  double goal;  // goal encoder tick count
  double last;  // previous loop error
  double sum;   // integral value
  // pid constants
  double kP;
  double kI;
  double kD;
  FILE* fp;  // used for logging
} PID;

PID* initPID(double p, double i, double d, char* logName);
// set a goal encoder tick count for the pid loop
void set(PID* pid, double setPoint);
// pid loop, current is current encoder tick count, dt handles variations in the
// rate of the pid loop
double update(PID* pid, double current, double dt);  // dt in seconds
double getErr(PID* pid);

#endif /* PID_H */
