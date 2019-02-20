#ifndef ENC_H
#define ENC_H

typedef struct{
    int encA;
    int encB;
    int levA;
    int levB;
    int lastGpio;
    long pos;
}Enc;

Enc enc;

void enc_init();

#endif
