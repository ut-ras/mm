#include "pid.h"
#include <stdlib.h>

#define MAX_SPEED (.4)
#define MAX_SUM (1000)

PID *initPID(double p, double i, double d, char *logName) {
  PID *pid = (PID *)malloc(sizeof(PID));
  pid->kP = p;
  pid->kI = i;
  pid->kD = d;
  pid->fp = fopen(logName, "w+");
  set(pid, 0);
  return pid;
}

double getErr(PID *pid) { return pid->last; }

void set(PID *pid, double set) {
  pid->goal = set;
  pid->sum = 0;
  pid->last = 0;
  if (pid->fp) {
    fprintf(pid->fp, "\nSet: %f P: %f I: %f D: %f\n", set, pid->kP, pid->kI,
            pid->kD);
  }
}

double update(PID *pid, double current, double dt) {
  double err = pid->goal - current;
  double d = (err - pid->last) / dt;
  pid->sum += err * dt;
  // sum = std::min(std::max(controller->sum, -MAX_SUM), MAX_SUM);
  pid->last = err;
  double result = pid->kP * err + pid->kI * pid->sum + pid->kD * d;
  if (pid->fp) {
    fprintf(pid->fp, "%f %f %f %f %f\n", dt, pid->kP * err, pid->kI * pid->sum,
            pid->kD * d, result);
  }
  return result;
}

void pidClose(PID *pid) {
  if (pid->fp) {
    fclose(pid->fp);
  }
}
