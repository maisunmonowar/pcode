
#include "app1.h"
#include "bootloader.h"

void main()
{
   INT8 i;
   delay_ms (100) ;
   
   WHILE (TRUE)
   {
      printf ("\r\nv4 %3u ", ++i);
      //TODO: User Code
      // Enter Bootloader if Pin D0 is low after a RESET
      if(!input(PUSH_BUTTON))
      {
         //load_program();
         reset_cpu(); //Since I can't call load_program() withough loader.c
         //loader.c not to be included in apps
      }
      delay_ms (100) ;
   }
}
