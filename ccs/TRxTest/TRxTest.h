#include <16F1787.h>
#device ADC=16
#use delay(crystal=8MHz)
//#use FIXED_IO( B_outputs=PIN_B6 )
//#define LED_PIN   PIN_D0

//#use rs232(baud=9600,parity=N,xmit=PIN_B1,rcv=PIN_B2,bits=8,stream=PORT1)
#use rs232(baud=9600,xmit=PIN_C6,rcv=PIN_C7)
#define LED PIN_D0
#define DELAY 1000


