#include "main.h"
 
#define _bootloader

// NOTE - User must include bootloader.h in application program
#include "bootloader.h"
#include "loader.c"

#INT_GLOBAL
void isr(void){
   jump_to_isr(LOADER_END+5*(getenv("BITS_PER_INSTRUCTION")/8));
}

#org LOADER_END+2, LOADER_END+4
void application(void) 
{    
  while(TRUE);
}

void main()
{
    // Enter Bootloader if Pin D0 is low after a RESET
   if(!input(PUSH_BUTTON))
   {
      printf("\r\nBootloader V 1\r\n");
   
      // Let the user know it is ready to accept a download
      printf("\r\ndownloading");
      load_program();
   }
   
   application();
}


