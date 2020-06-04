#include <16F1789.h>
#fuses NOWDT, NOBROWNOUT, NOPROTECT
#use delay(crystal=16MHz,clock=16MHz)
#include <PIC16F1789_registers.h>

#use rs232(baud=9600,parity=N,xmit=PIN_B6,rcv=PIN_B7,bits=8,stream=PORT1)

#use rs232(baud=9600,parity=N,xmit=PIN_D4,rcv=PIN_D5,bits=8,stream=MPIC)

#use rs232(baud=9600,parity=N,xmit=PIN_c6,rcv=PIN_c7,bits=8,stream=COMPIC)


int8 sec = 0;
int8 min = 0;
int8 hou = 0;
int16 day = 0;
int8 res_flag;
//int8 unreg_flag;
//int8 check=0;
int resetData[11];
BYTE rx_chars[8] = {0};
BYTE rxcom_chars[8] = {0};
int8 CHECK_MAIN_RESPONSE = 0;
int8 CHECK_COM_RESPONSE = 0;
int8 MAIN_ACK = 0;
#define memory 10
#define check_memory 5


#include<power_enable.c>
#include<read_current.c>
//#include<reset_func.c>

//INTERRUPT 
#INT_TIMER1
void TIMER1_isr() {   
      set_timer1(0x8000);
      if (sec < 59){
      sec++;
      }else{
         sec = 0;
         min++;
      }
      if (min == 60){
         min = 0;
         hou++;
         
      }
      if (hou == 24){
         hou = 0;
         day++;
         res_flag = 1;
      }
      
      fprintf(PORT1,"%02ld", day);
      fprintf(PORT1,":%02d", hou);
      fprintf(PORT1,":%02d", min);
      fprintf(PORT1,":%02d\r\n", sec);
      
      if (res_flag == 1){
        
        reset_mode();
        
        res_flag = 0;
        }
}

//!#int_rda
//!void reset_main(){
//! 
//!  rx_chars[0] = fgetc(MPIC);
//!  
//! }
//! 

//!#int_rda2
//!void reset_com(){
//! 
//!  rxcom_chars[0] = fgetc(COMPIC);
//!  
//! }

void Initialize_RTC(void)
{
   setup_timer_1(T1_EXTERNAL | T1_DIV_BY_1);
   
   T1OSCEN = 1; //enabling timer1
     
   enable_interrupts(INT_TIMER1);
   
   //set_timer1(0x8000); //32768 in hex
}


#INT_TIMER0
void watchdog_timer(void){

      if(!get_timer0()){
      RB2 = 1;
      delay_us(5);
      RB2 = 0;       
      }

}

//MAIN
void main() {
 
   fprintf(PORT1,"*********************************************************\n\r");
   fprintf(PORT1,"******     THIS IS RESET PIC EM VERSION         *********\n\r");
   fprintf(PORT1,"*********************************************************\n\r");
   
   delay_ms(100); 
                
   TRISC2 = 0; RC2 = 0;
   TRISC3 = 0; RC3 = 0;
   TRISC4 = 0; RC4 = 0;
   TRISC5 = 0; RC5 = 0;
   
   TRISD0 = 0; RD0 = 0;
   TRISD1 = 0; RD1 = 0;
   TRISD2 = 0; RD2 = 0;
   TRISD3 = 0; RD3 = 0;
   TRISD6 = 0; RD6 = 0;
   TRISD7 = 0; RD7 = 0;
 
   TRISB2 = 0;
   
   SETUP_ADC(ADC_CLOCK_INTERNAL);
   SETUP_ADC_PORTS(sAN0|sAN1|sAN2|sAN3|sAN4|sAN5|sAN6);  //setting all analog ports
   
   
   //clear_interrupt(int_timer1);
   Initialize_RTC(); 
   
   enable_interrupts(GLOBAL);
   enable_interrupts(INT_TIMER0); //interrupts for WDT
   setup_timer_0(RTCC_DIV_256 | RTCC_INTERNAL);   
   set_timer0(0xFF);
   
    delayloop(5);
    unreg_first_run();

    fprintf(PORT1,"******Normal Mode Start *********\n\r");
    
    normal_mode();
    
    while (TRUE){      
        
        resetData[0] = 0x8E;
        resetData[1] = sec;
        resetData[2] = min;
        resetData[3] = hou;
        
        resetData[4] = (day >> 8) & 0xFF;
        resetData[5] = day & 0x00FF;   
        
        adcreading_reset();
         
         for(int32 num = 0; num < 100000; num++)
         {
            if(kbhit(MPIC))
            {
               MAIN_ACK = fgetc(MPIC);   //UART receive from main pic
               fprintf(PORT1,"Got command from MAIN:%x\r\n",MAIN_ACK);
               break;
            }
            //delay_ms(1);
         }
         
             if(MAIN_ACK == 0x28){     //receiving command from main pic
                
                  fprintf(PORT1,"******Sendind data to main *********\n\r");
                  
                  MAIN_ACK=0;
                  
                  //delay_ms(1);
                  
                  for (int i=0;i<10;i++){                       
                  
                        fputc(resetData[i],MPIC);                        
                   }  
                  
                  //fprintf(PORT1,"******Sendind data to main *********\n\r");
               }
               
            else{fprintf(PORT1,"******Correct Command not received *********\n\r");}

      //RESET_MAIN_OPERATION();
      //RESET_COM_OPERATION();
   }


 }

