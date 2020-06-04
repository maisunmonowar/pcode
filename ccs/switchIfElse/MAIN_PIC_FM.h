#ifndef MAIN_PIC_FM_H
#define MAIN_PIC_FM_H

#include <18F67J94.h>

#include<PIC18F67J94_registers.h>
#FUSES NOWDT, NOBROWNOUT, NOPROTECT
#use delay(crystal=16Mhz, clock=16Mhz)
#build(reset=0x2:0x9, interrupt=0xa:0xa+9)

//#include<HAMING_CORRECT.h>
    
#device HIGH_INTS=TRUE

//-------------UART and SPI Setting--------------------------------------------

#pin_select TX1=PIN_C6                                                           //TX PIN EXT +/- 6v
#pin_select RX1=PIN_C7                                                           //RX PIN EXT +/- 6V
#use rs232(baud=115200,parity=N,UART1,bits=8,stream=pc)                          // MAIN to Ext +/- 6v
//#use rs232(baud=9600,parity=N,xmit=PIN_B6,rcv=PIN_B7,bits=8,stream=pc)           //UART MAIN to ICSP, PGC and PGD pins
#pin_select TX2=PIN_D3
#pin_select RX2=PIN_D2
#use rs232(baud=9600,parity=N,UART2,bits=8,stream=com)                           //UART Main to COM PIC

#pin_select TX3=PIN_E5  
#pin_select RX3=PIN_E4
#use rs232(baud=9600,parity=N,UART3,bits=8,stream=fab)                           //UART MAIN to FAB PIC

#pin_select TX4=PIN_E3  
#pin_select RX4=PIN_F2
#use rs232(baud=9600,parity=N,UART4,bits=8,stream=reset)                         //UART MAIN to RESET PIC

#use rs232(baud=9600,parity=N,xmit=pin_F7,rcv=pin_F6,bits=8,stream=ADCS)         //UART MAIN to ADCS
#use rs232(baud=9600,parity=N,xmit=pin_G2,rcv=pin_G3,bits=8,stream=CAM)          //UART MAIN to CAM
#use rs232(baud=9600,parity=N,xmit=pin_G0,rcv=pin_G1,bits=8,stream=DC)          //UART MAIN to MB DCM

#use spi(MASTER, CLK=PIN_E1, DI=PIN_E0, DO=PIN_E6,  BAUD=1000000, BITS=8, STREAM=MAIN_FM, MODE=0)        //MAIN flash memory port
#use spi(MASTER, CLK=PIN_B2, DI=PIN_B5, DO=PIN_B4,  BAUD=1000000, BITS=8, STREAM=COM_FM, MODE=0)         //COM flash memory port
#use spi(MASTER, CLK=PIN_A3, DI=PIN_A0, DO=PIN_A1,  BAUD=1000000, BITS=8, STREAM=MISSION_FM, MODE=0)     //MISSION flash memory port

#ORG 0x0000C800, 0x0000EFFF {}
#ORG 0x0000F000, 0x000117FF {}
#ORG 0x00011800, 0x00013FFF {}
#ORG 0x00014000, 0x000167FF {}
#ORG 0x00016800, 0x00018FFF {}
#ORG 0x00019000, 0x0001B7FF {}
#ORG 0x0001B800, 0x0001DFFF {}
#ORG 0x0001E000, 0x0001FFEF {}
#endif
