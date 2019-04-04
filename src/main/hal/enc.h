#ifndef ENC_H
#define ENC_H

enum Direction{
  forward = 0,
  backward = 1,
  stop = 2
};

enum enc_locs{
  right_enc = 0,
  left_enc = 1
};

typedef struct{
  int count;
  int sum;
  int pcnt;
  int direction;
}Enc;

Enc *encoders[2];

void enc_init();
void readEncoders();
int getTicks(int enc_num);

#endif
