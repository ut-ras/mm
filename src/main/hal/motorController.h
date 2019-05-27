#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

void mcpwm_initialize();

void setLeftSpeed(double speed);
void setRightSpeed(double speed);

/* Sets the power of each motor, range for input is from -100.0 to 100.0
 * with negative power meaning backwards movement.*/
void setMotors(float left, float right);

void stopMotors(void);

#endif
