#ifndef ADCS_TEST_C
#define ADCS_TEST_C

#include "adcs.c"
#include "adcs_test.h"

#ORG 0x00011800
void ADCS_TEST_OPERATION(unsigned int16 duration, int8 OPERATION_MODE)           //Integration Testing With ADCS
{
   int8 count = 0;
   LOOP_ADCS_SENSOR_ADDRESS();
   ADCS_SETTINGS();
   beginning_of_operation = ADCS_SENSOR_ADDRESS;
   
   /*   GET_INITIAL_TIME(); */
   fprintf(PC,"Turn On ADCS \r\n");
   Turn_On_ADCS();                                                               //Turn on ADCS
   /*delay_ms(8000);*/
   
   fputc(0x21,ADCS);                                                             //ADCS hand shake

   CHECK_ACK_FROM_ADCS_10k();
   if(ADCS_ACK == 0x55)                                                            //Success ACK
   {
      fprintf(PC,"Received ACK From ADCS\r\n");
      //delay_ms(1000);
      ADCS_ACK = 0;
      fputc(OPERATION_MODE,adcs);                                                   //for execute stabilize mission
      fprintf(PC,"Sent OPERATION MODE to ADCS\r\n");
   }else{
      ADCS_ACK = 0;
      fprintf(PC,"FAILURED GETTING ACK From ADCS\r\n");
   }
   


   CMD_FROM_PC[0] = 0;                                                           //prepare to get MAIN command
   PC_DATA = 0;                                                                  //prepare to get MAIN command
   currenttime = 0;                                                              //prepare to measure the operation time
   while(true)
   {
      /*  for(int safe = 0; safe < 100; safe++)
      {
         GET_ADCS_MSN_DATA();
      }*/
      if(currenttime > duration)                                                 //600-->600 seconds (10min)
      {
         fprintf(PC,"done\r\n");
         break;
      }
       /*  for(safe = 0; safe < 100; safe++)
      {
         GET_ADCS_MSN_DATA();
      }*/
      if((currenttime%90)==0)
      {
         COLLECT_RESET_DATA();
      }
      
      /* for(safe = 0; safe < 100; safe++)
      {
         GET_ADCS_MSN_DATA();
      }*/
      
      if(CMD_FROM_PC[0] == 0xab)
      {
         CMD_FROM_PC[0] = 0;
         PC_DATA = 0;
         Turn_off_ADCS();
         fprintf(PC,"Stop ADCS Mission\r\n");
         break;
      }
      /* for(safe = 0; safe < 100; safe++)
      {
         GET_ADCS_MSN_DATA();
      }*/
      RESET_SATELLITE();                                                         //if reset pic send command for resetting the satellite, OBC will response soon
   }  
   Turn_OFF_ADCS();                                                              //turn off ADCS OCP
   fprintf(PC,"\r\n\r\nTurned_OFF_ADCS\r\n\r\n\r\n");                                                       
   fprintf(PC,"%lx",beginning_of_operation);
   delay_ms(1000);
   Turn_On_ADCS();
   fprintf(PC,"\r\n\r\nTurned_ON_ADCS\r\n\r\n\r\n");
   //ADCS debe estar siempre encendido
   /*  SAVE_ADCS_INITIAL_and_FINAL(beginning_of_operation);
   output_low(PIN_C4);
   for(int32 num = 0; num < 81+90; num++)
   {
      fprintf(PC,"%x",READ_DATA_BYTE_SCF(beginning_of_operation + num));
   }
   //TRANSFER_DATA_NBYTE_TOPC_SCF(ADCS_SENSOR_ADDRESS-ATTEMPT_TIME*100, ATTEMPT_TIME*100);
   output_high(PIN_C4);*/
   RESET_SATELLITE();                                                            //if reset pic send command for resetting the satellite, OBC will response soon
   if(count > 89)
   {
      count = 0;
      COLLECT_RESET_DATA();
   }else{
      count++;
   } 
   return;
}

void DISPLAY_ADCS_SENSOR_TO_PC()//for testing
{
   for(int b = 0; b < ADCS_SENSOR_SIZE; b++)//for checking
   {
      fputc(ADCS_SENSOR_DATA[b],PC);
   }
   return;
}

void CHECK_50_and_CW_RESPOND()                                                   //verifica si llego comando 0x50 desde COM PIC y envia CW al COM
{
   if(in_bffr_main[4] == 0x50)
   {
      CW_RESPOND();                                                              //carga el array ACK_for_COM[] con el dato del array CW_FORMAT[] y envia a COM PIC
      Delete_Buffer();                                                           //delete in_bffr_main[] (com command buffer)
      COM_DATA = 0;                                                              //flag to cero
   }
   return;
}

void Get_ADCS_MISSION_Data()
{
   
   Delete_ADCS_SENSOR(); //initialize
   CHECK_50_and_CW_RESPOND();
   fputc(0x55,ADCS);
   fputc(0x55,PC);
   int i = 0;
   for(int32 num = 0; num < 1000000 ;num++)
   {
      if(kbhit(ADCS) && fgetc(ADCS) == 0x67)
      {
         for(num = 0; num < 10000; num++)
         {
            if(Kbhit(ADCS))
            {
               ADCS_SENSOR_DATA[i] = fgetc(ADCS);
               i++;
               if(i == 60)
               {
                  break;
               }
            }
         }
         ADCS_ACK = 0x67;
         break;
      }
   }
   if(num == 1000000)
   {
      fprintf(PC,"NO DATA\r\n");
   }
   CHECK_50_and_CW_RESPOND();
   return;
}

#ORG 0x00011800
int8 compare_before_after(int32 beginning, int32 end)
{
   int8 data[12] = {};
   for(int i = 0; i < 6; i++)
   {
      data[i] = READ_DATA_BYTE_OF(beginning+222+10+i);
   }
   for(i = 0; i < 6; i++)
   {
      data[i+6] = READ_DATA_BYTE_OF(end-101+i);
   }
   signed int16 Bx = make16(data[0],data[1]);
   signed int16 By = make16(data[2],data[3]);
   signed int16 Bz = make16(data[4],data[5]);
   
   signed int16 Ax = make16(data[6],data[7]);
   signed int16 Ay = make16(data[8],data[9]);
   signed int16 Az = make16(data[10],data[11]);
   
   signed int16 Total_B = Bx + By + Bz;
   signed int16 Total_A = Ax + Ay + Az;
   Total_B = abs(Total_B);
   Total_A = abs(Total_A);
   fprintf(PC,"%lx,%lx,%lx\r\n",Bx,By,Bz);
   fprintf(PC,"%lx,%lx,%lx\r\n",Ax,Ay,Az);
   fprintf(PC,"%lud,%lud\r\n",Total_B,Total_A);
   if(Total_B >= Total_A)
   {
      return 1;//declease --> continue
   }else{
      return 0;//inclease --> stop
   }
}

#endif
