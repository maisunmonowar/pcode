#include <16F1787.h>
#device ADC=16
#use delay(crystal=8000000)
#fuses NOWDT
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7)
#define PUSH_BUTTON PIN_D0
