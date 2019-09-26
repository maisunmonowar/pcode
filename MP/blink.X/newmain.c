/*
 * File:   newmain.c
 * Author: maisun
 *
 * Created on July 26, 2019, 2:21 PM
 */

#include <pic16f1787.h>


#include <xc.h>


#define _XTAL_FREQ 8000000
void main(void) {
    TRISD = 0;
    
    while(1)
    {
        PORTDbits.RD2 = 1;
        __delay_ms(2000);
        PORTDbits.RD2 = 0;
        __delay_ms(2000);
    }
}
