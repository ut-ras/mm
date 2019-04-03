#include "esp_timer.h"

void setMotors(float left, float right);
int init();

void zero();

void setMotorsP(int error, float maxSpeed);

void followPBasic(float maxSpeed, short* walls);
