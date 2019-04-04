#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

void mcpwm_initialize();

void setLeftSpeed(double speed);
void setRightSpeed(double speed);

#endif
