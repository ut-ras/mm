#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#ifdef __cplusplus
extern "C" {
#endif
void mcpwm_initialize();

void set_left_speed(double speed);
void setRightSpeed(double speed);

/* Sets the power of each motor, range for input is from -100.0 to 100.0
 * with negative power meaning backwards movement.*/
void setMotors(float left, float right);

void stopMotors(void);

#ifdef __cplusplus
}
#endif
#endif /* MOTOR_CONTROLLER_H */
