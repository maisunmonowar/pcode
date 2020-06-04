#include <18F67J94.h>
//#device ADC=16
#use delay(clock=16000000, crystal=16000000)
#fuses NOWDT NOBROWNOUT


#use rs232(baud=9600, xmit=PIN_E5, rcv=PIN_E4)//#use rs232(baud=9600, xmit=PIN_E5, rcv=PIN_E4)

#define PUSH_BUTTON PIN_B7
