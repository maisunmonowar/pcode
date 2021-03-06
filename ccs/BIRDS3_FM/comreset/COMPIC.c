#include <16F1789.h> //EM: 16f1789
#fuses NOMCLR,NOWDT
#use delay(internal=16Mhz,clock=16mhz)


#use rs232(baud=9600,parity=N,xmit=PIN_B1,rcv=PIN_B2,bits=8,stream=mpic) //PC reading port

//#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8,stream=TR_CP) //UART port from com pic to TRX pic  
//#use rs232(baud=9600,parity=N,xmit=PIN_B3,rcv=PIN_B4,bits=8,stream=RP_CP) //UART port from com pic to reset pic
#use rs232(baud=9600,parity=N,UART1,xmit=PIN_C6,rcv=PIN_C7,bits=8,stream=PC) //UART port from com pic to MAIN PIC   

//#use spi(MASTER, CLK=PIN_D4, DI=PIN_D6, DO=PIN_D7,BAUD=300000,BITS=8,STREAM=CFM, MODE=0) //COM flash memory port
//#use spi(MASTER, CLK=PIN_C3, DI=PIN_C4, DO=PIN_C5,BAUD=960000,BITS=8,STREAM=SFM, MODE=0)

//#include <flash_ memory_ MT25QL01GBBB.c>

unsigned int8 in_bffr_main[16] = {0xAA,0x67,0x67,0x67,0x55,0x67,0x67,0x73,0x67,0x67,0x67,0x67,0x67,0x67,0x67,0xBB};

/*#INT_rda
void UART1_RXD(void)
{
   if(fgetc(mpic)==0x69)
   {
      fputc(0x69,PC);
   }
}*/

void settings()
{
  enable_interrupts(global);  
  enable_interrupts(INT_rda);
  return;
}
/*
Void main()
{ 
   settings();
   int8 k;
   While(true)
   {
   k = fgetc(mpic);
   fputc(0xbb,PC);
      while(k!=0x69)
      {
         fputc(0x69,mpic);
         fputc(0xaa,PC);
         delay_ms(1500);
      }
   fputc(0x87,PC);
   }
 
}
*/

void main()
{
   //while(true)
   //{
   delay_ms(2000);
      for(int i = 0; i < 16; i++)
      {
         fputc(in_bffr_main[i],mpic);
      }
      //fputc(fgetc(mpic),PC);
      delay_ms(1000);
   //}
}
