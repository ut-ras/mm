#ifndef PID_H
#define PID_H

#include <stdio.h>

typedef struct {
  double goal;
  double last;
  double sum;
  double kP;
  double kI;
  double kD;
  FILE *fp;
} PID;

PID* initPID(double p, double i, double d, char* logName);
void set(PID* pid, double setPoint);
double update(PID* pid, double current, double dt); // dt in seconds
double getErr(PID *pid);

#endif
