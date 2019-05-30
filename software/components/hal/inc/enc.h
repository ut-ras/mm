#ifndef ENC_H
#define ENC_H

enum Direction { forward = 0, backward = 1, stop = 2 };

// keep track of which encoder is which
enum enc_locs { right_enc = 0, left_enc = 1 };

typedef struct {
  int count;  // current real tick count
  int sum;    // holds counter value if counter overflows
  int pcnt;
  int direction;
} Enc;

Enc *encoders[2];

void enc_init();
int getTicks(int enc_num);  // get current tick count

int getAvgTicks(void);

#endif
