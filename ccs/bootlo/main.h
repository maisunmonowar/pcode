//#DEVICE ADC=16
#include <18F67J94.h>
#FUSES NOWDT NOBROWNOUT
#use delay(clock=16000000, crystal=16000000)
//#DEVICE ADC=16

#use rs232(baud=9600, xmit=PIN_E5, rcv=PIN_E4)//#use rs232(baud=9600, xmit=PIN_E5, rcv=PIN_E4)

#define PUSH_BUTTON PIN_B7
