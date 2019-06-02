#include "pid.h"
#include <stdlib.h>

#define MAX_SPEED (.4)
#define MAX_SUM (200)

PID *initPID(double p, double i, double d, char *logName) {
  printf("inittest\n");
  PID *pid = (PID *)malloc(sizeof(PID));
  pid->kP = p;
  pid->kI = i;
  pid->kD = d;
  //pid->fp = fopen(logName, "w+");
  set(pid, 0);
  printf("inittest2\n");
  return pid;
}

double getErr(PID *pid) { return pid->last; }

void set(PID *pid, double set) {
  printf("tadsfiasdst\n");
  pid->goal = set;
  pid->sum = 0;
  pid->last = 0;
  printf("test\n");
  /*if (pid->fp) {
    fprintf(pid->fp, "\nSet: %f P: %f I: %f D: %f\n", set, pid->kP, pid->kI,
            pid->kD);
  }*/
}

// renamed standard max and min to avoid multiple definition error
double pid_max(double val1, double val2) { return val1 > val2 ? val1 : val2; }

double pid_min(double val1, double val2) { return val1 < val2 ? val1 : val2; }

double update(PID *pid, double current, double dt) {
  // calculate current error, the proportional value
  double err = pid->goal - current;
  // calculate derivative value
  double d = (err - pid->last) / dt;
  // summation of error into sum to calculate the integral value
  pid->sum += err * dt;
  // keep integral value between reasonable bounds
  pid->sum = pid_min(pid_max(pid->sum, -MAX_SUM), MAX_SUM);
  pid->last = err;  // store error for use in next derivative calculation
  // compute pid calculation and log to file
  double result = pid->kP * err + pid->kI * pid->sum + pid->kD * d;
  // printf("%f %f\n",pid->kI * pid->sum, result);
  if (pid->fp) {
    /*fprintf(pid->fp, "%f %f %f %f %f\n", dt, pid->kP * err, pid->kI * pid->sum,
            pid->kD * d, result);*/
  }
  return result;
}

void pidClose(PID *pid) {
  if (pid->fp) { fclose(pid->fp); }
}
