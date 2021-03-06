#byte INDF0 = 0x000
#byte INDF1 = 0x001
#byte PCL = 0x002
#byte STATUS = 0x003
#bit    C  = STATUS.0
#bit    DC = STATUS.1
#bit    Z  = STATUS.2
#bit    PD = STATUS.3
#bit    TO = STATUS.4

#word FSR0 = 0x004
#word FSR1 = 0x006
#byte BSR = 0x008
#byte WREG = 0x009
#byte PCLATH = 0x00A

#byte INTCON = 0x00B
#bit    IOCIF  = INTCON.0
#bit    INTF   = INTCON.1
#bit    TMR0IF = INTCON.2
#bit    IOCIE  = INTCON.3
#bit    INTE   = INTCON.4
#bit    TMR0IE = INTCON.5
#bit    PEIE   = INTCON.6
#bit    GIE    = INTCON.7

#byte PORTA = 0x00C
#bit    RA0 = PORTA.0
#bit    RA1 = PORTA.1
#bit    RA2 = PORTA.2
#bit    RA3 = PORTA.3
#bit    RA4 = PORTA.4
#bit    RA5 = PORTA.5
#bit    RA6 = PORTA.6
#bit    RA7 = PORTA.7

#byte PORTB = 0x00D
#bit    RB0 = PORTB.0
#bit    RB1 = PORTB.1
#bit    RB2 = PORTB.2
#bit    RB3 = PORTB.3
#bit    RB4 = PORTB.4
#bit    RB5 = PORTB.5
#bit    RB6 = PORTB.6
#bit    RB7 = PORTB.7

#byte PORTC = 0x00E
#bit    RC0 = PORTC.0
#bit    RC1 = PORTC.1
#bit    RC2 = PORTC.2
#bit    RC3 = PORTC.3
#bit    RC4 = PORTC.4
#bit    RC5 = PORTC.5
#bit    RC6 = PORTC.6
#bit    RC7 = PORTC.7

#byte PORTD = 0x00F
#bit    RD0 = PORTD.0
#bit    RD1 = PORTD.1
#bit    RD2 = PORTD.2
#bit    RD3 = PORTD.3
#bit    RD4 = PORTD.4
#bit    RD5 = PORTD.5
#bit    RD6 = PORTD.6
#bit    RD7 = PORTD.7

#byte PORTE = 0x010
#byte PIR1 = 0x011
#bit    TMR1IF = PIR1.0
#bit    TMR2IF = PIR1.1
#bit    CCP1IF = PIR1.2
#bit    SSP1IF = PIR1.3
#bit    TXIF = PIR1.4
#bit    RCIF = PIR1.5
#bit    ADIF = PIR1.6
#bit    TMR1GIF = PIR1.7

#byte PIR2 = 0x012
#bit    CCP2IF = PIR2.0
#bit    C3IF = PIR2.1
#bit    C4IF = PIR2.2
#bit    BCL1IF = PIR2.3
#bit    EEIF = PIR2.4
#bit    C1IF = PIR2.5
#bit    C2IF = PIR2.6
#bit    OSFIF = PIR2.7

#byte PIR3 = 0x013
#bit    CCP3IF = PIR3.4
#byte PIR4 = 0x014
#bit    PSMC1SIF = PIR4.0
#bit    PSMC2SIF = PIR4.1
#bit    PSMC3SIF = PIR4.2
#bit    PSMC1TIF = PIR4.4
#bit    PSMC2TIF = PIR4.5
#bit    PSMC3TIF = PIR4.6
#byte TMR0 = 0x015
#word TMR1 = 0x016
#byte T1CON = 0x018
#bit    TMR1ON = T1CON.0
#bit    T1SYNC = T1CON.2
#bit    T1OSCEN = T1CON.3
#bit    T1CKPS0 = T1CON.4
#bit    T1CKPS1 = T1CON.5
#bit    TMR1CS0 = T1CON.6
#bit    TMR1CS1 = T1CON.7
#byte T1GCON = 0x019
#bit    T1GSS0 = T1GCON.0
#bit    T1GSS1 = T1GCON.1
#bit    T1GVAL = T1GCON.2
#bit    T1GGO = T1GCON.3
#bit    T1GSPM = T1GCON.4
#bit    T1GTM = T1GCON.5
#bit    T1GPOL = T1GCON.6
#bit    TMR1GE = T1GCON.7
#byte TMR2 = 0x01A
#byte PR2 = 0x01B
#byte T2CON = 0x01C
#bit    T2CKPS0 = T2CON.0
#bit    T2CKPS1 = T2CON.1
#bit    TMR2ON = T2CON.2
#bit    T2OUTPS0 = T2CON.3
#bit    T2OUTPS1 = T2CON.4
#bit    T2OUTPS2 = T2CON.5
#bit    T2OUTPS3 = T2CON.6
#byte TRISA = 0x08C
#bit    TRISA0 = TRISA.0
#bit    TRISA1 = TRISA.1
#bit    TRISA2 = TRISA.2
#bit    TRISA3 = TRISA.3
#bit    TRISA4 = TRISA.4
#bit    TRISA5 = TRISA.5
#bit    TRISA6 = TRISA.6
#bit    TRISA7 = TRISA.7
#byte TRISB = 0x08D
#bit    TRISB0 = TRISB.0
#bit    TRISB1 = TRISB.1
#bit    TRISB2 = TRISB.2
#bit    TRISB3 = TRISB.3
#bit    TRISB4 = TRISB.4
#bit    TRISB5 = TRISB.5
#bit    TRISB6 = TRISB.6
#bit    TRISB7 = TRISB.7
#byte TRISC = 0x08E
#bit    TRISC0 = TRISC.0
#bit    TRISC1 = TRISC.1
#bit    TRISC2 = TRISC.2
#bit    TRISC3 = TRISC.3
#bit    TRISC4 = TRISC.4
#bit    TRISC5 = TRISC.5
#bit    TRISC6 = TRISC.6
#bit    TRISC7 = TRISC.7
#byte TRISD = 0x08F
#bit    TRISD0 = TRISD.0
#bit    TRISD1 = TRISD.1
#bit    TRISD2 = TRISD.2
#bit    TRISD3 = TRISD.3
#bit    TRISD4 = TRISD.4
#bit    TRISD5 = TRISD.5
#bit    TRISD6 = TRISD.6
#bit    TRISD7 = TRISD.7
#byte TRISE = 0x090
#byte PIE1 = 0x091
#bit    TMR1IE = PIE1.0
#bit    TMR2IE = PIE1.1
#bit    CCP1IE = PIE1.2
#bit    SSP1IE = PIE1.3
#bit    TXIE = PIE1.4
#bit    RCIE = PIE1.5
#bit    ADIE = PIE1.6
#bit    TMR1GIE = PIE1.7
#byte PIE2 = 0x092
#bit    CCP2IE = PIE2.0
#bit    C3IE = PIE2.1
#bit    C4IE = PIE2.2
#bit    BCL1IE = PIE2.3
#bit    EEIE = PIE2.4
#bit    C1IE = PIE2.5
#bit    C2IE = PIE2.6
#bit    OSFIE = PIE2.7
#byte PIE3 = 0x093
#bit    CCP3IE = PIE3.4
#byte PIE4 = 0x094
#bit    PSMC1SIE = PIE4.0
#bit    PSMC2SIE = PIE4.1
#bit    PSMC3SIE = PIE4.2
#bit    PSMC1TIE = PIE4.4
#bit    PSMC2TIE = PIE4.5
#bit    PSMC3TIE = PIE4.6

#byte OPTION_REG = 0x095
#bit    PS0 = OPTION_REG.0
#bit    PS1 = OPTION_REG.1
#bit    PS2 = OPTION_REG.2
#bit    PSA = OPTION_REG.3
#bit    TMR0SE = OPTION_REG.4
#bit    TMR0CS = OPTION_REG.5
#bit    INTEDG = OPTION_REG.6
#bit    WPUEN = OPTION_REG.7

#byte PCON = 0x096
#bit    BOR = PCON.0
#bit    POR = PCON.1
#bit    RI = PCON.2
#bit    RMCLR = PCON.3
#bit    RWDT = PCON.4
#bit    STKUNF = PCON.6
#bit    STKOVF = PCON.7
#byte WDTCON = 0x097
#bit    SWDTEN = WDTCON.0
#bit    WDTPS0 = WDTCON.1
#bit    WDTPS1 = WDTCON.2
#bit    WDTPS2 = WDTCON.3
#bit    WDTPS3 = WDTCON.4
#bit    WDTPS4 = WDTCON.5
#byte OSCTUNE = 0x098
#byte OSCCON = 0x099
#bit    SCS0 = OSCCON.0
#bit    SCS1 = OSCCON.1
#bit    IRCF0 = OSCCON.3
#bit    IRCF1 = OSCCON.4
#bit    IRCF2 = OSCCON.5
#bit    IRCF3 = OSCCON.6
#bit    SPLLEN = OSCCON.7
#byte OSCSTAT = 0x09A
#bit    HFIOFS = OSCSTAT.0
#bit    LFIOFR = OSCSTAT.1
#bit    MFIOFR = OSCSTAT.2
#bit    HFIOFL = OSCSTAT.3
#bit    HFIOFR = OSCSTAT.4
#bit    OSTS = OSCSTAT.5
#bit    PLLR = OSCSTAT.6
#bit    T1OSCR = OSCSTAT.7
#word ADRES = 0x09B
#byte ADCON0 = 0x09D
#bit    ADON = ADCON0.0
#bit    GO = ADCON0.1
#bit    CHS0 = ADCON0.2
#bit    CHS1 = ADCON0.3
#bit    CHS2 = ADCON0.4
#bit    CHS3 = ADCON0.5
#bit    CHS4 = ADCON0.6
#bit    ADRMD = ADCON0.7


#byte ADCON1 = 0x09E
#bit    ADPREF0 = ADCON1.0
#bit    ADPREF1 = ADCON1.1
#bit    ADNREF  = ADCON1.2
#bit    ADCS0   = ADCON1.4
#bit    ADCS1   = ADCON1.5
#bit    ADCS2   = ADCON1.6
#bit    ADFM    = ADCON1.7
#byte ADCON2 = 0x09F
#bit    CHSN0 = ADCON2.0
#bit    CHSN1 = ADCON2.1
#bit    CHSN2 = ADCON2.2
#bit    CHSN3 = ADCON2.3
#bit    TRIGSEL0 = ADCON2.4
#bit    TRIGSEL1 = ADCON2.5
#bit    TRIGSEL2 = ADCON2.6
#bit    TRIGSEL3 = ADCON2.7
#byte LATA = 0x10C
#bit    LATA0 = LATA.0
#bit    LATA1 = LATA.1
#bit    LATA2 = LATA.2
#bit    LATA3 = LATA.3
#bit    LATA4 = LATA.4
#bit    LATA5 = LATA.5
#bit    LATA6 = LATA.6
#bit    LATA7 = LATA.7
#byte LATB = 0x10D
#bit    LATB0 = LATB.0
#bit    LATB1 = LATB.1
#bit    LATB2 = LATB.2
#bit    LATB3 = LATB.3
#bit    LATB4 = LATB.4
#bit    LATB5 = LATB.5
#bit    LATB6 = LATB.6
#bit    LATB7 = LATB.7
#byte LATC = 0x10E
#bit    LATC0 = LATC.0
#bit    LATC1 = LATC.1
#bit    LATC2 = LATC.2
#bit    LATC3 = LATC.3
#bit    LATC4 = LATC.4
#bit    LATC5 = LATC.5
#bit    LATC6 = LATC.6
#bit    LATC7 = LATC.7
#byte LATD = 0x10F
#bit    LATD0 = LATD.0
#bit    LATD1 = LATD.1
#bit    LATD2 = LATD.2
#bit    LATD3 = LATD.3
#bit    LATD4 = LATD.4
#bit    LATD5 = LATD.5
#bit    LATD6 = LATD.6
#bit    LATD7 = LATD.7

