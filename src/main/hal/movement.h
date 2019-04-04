#ifndef MOVEMENT_H
#define MOVEMENT_H

void setMotors(float left, float right);

int init();

void zero();

void setMotorsP(int error, float maxSpeed);

void followPBasic(float maxSpeed, short* walls);

#endif
