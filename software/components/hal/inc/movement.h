#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <stdbool.h>

struct movement_info {
  bool left;
  bool right;
  bool front;

  int ticksTraveled;
};

/* Initalize all devices including adc, pwm, and encoders */
int init();

/* Zeros side distance sensors assuming that robot is
 * ceneterd in a unit in the maze. */
void zero(void);

/* Return a struct containing which walls are present */
struct movement_info getWalls(int* lsensor, int*rsensor);

/* Move forward using distance sensors for correction until
 * a gap is detected on the sides or a wall is detected in
 * front. Returns a struct containing which direction walls
 * are present as well as distance traveled in maze units.
 * Travels at a specified speed with a range of 0.0 to 100.0. */
struct movement_info moveIR(float speed);

/* Move forward using encoders for correction until
 * a gap is detected on the sides or a wall is detected in
 * front. Returns a struct containing which direction walls
 * are present as well as distance traveled in maze units.
 * Travels at a specified speed with a range of 0.0 to 100.0.
 * Travels a certain number of encoder ticks based on input */
struct movement_info moveEnc(float speed, int encoderTicks);

struct movement_info moveEncU(float speed);

/* Turn a specified number of degrees*/
struct movement_info turnDegrees(float speed, float degrees);

/* Turn 90 degrees in specified direction at specified speed.
 * Returns a struct containing which direction walls are present */
struct movement_info turn90(float speed);

/* Turn 180 degrees in specified direction at specified speed.
 * Returns a struct containing which direction walls are present */
struct movement_info turn180(float speed);

struct movement_info turnDegrees(float speed, float angle);
#endif /* MOVEMENT_H */
