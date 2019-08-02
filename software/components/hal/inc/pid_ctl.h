#ifndef PID_CTL_H
#define PID_CTL_H

void controlUpdate(double elapsed);
void moveStraight(int dist);
void selfTest();
void hardStop();
void printEnc();
void setSpeed(double speed);
void initRobot();

#endif /* PID_CTL_H */
