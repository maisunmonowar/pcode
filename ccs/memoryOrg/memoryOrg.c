#include <memoryOrg.h>
//!#include <bootloader.h>
//!#include <loader.c>

#if defined(__PCM__)
 #org 0x500, 0x628//LOADER_END+1,LOADER_END+256
#elif defined(__PCH__)
 #org LOADER_END+2,LOADER_END+4
#endif
void main()
{
   while(TRUE)
   {
      //Example blinking LED program
      output_low(LED);
      delay_ms(DELAY);
      output_high(LED);
      delay_ms(DELAY);

      //TODO: User Code
   }
}

