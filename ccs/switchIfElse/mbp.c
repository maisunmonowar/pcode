#ifndef MBP_C
#define MBP_C

#include "MEMORY_OPERATION.c"
#include "SATELLITE_LOG.c"

int8 MBP_DATA[83] = {};
int8 DC_ACK = 0;

#ORG 0x00011800
void Turn_On_MBP()
{
   output_high(PIN_F5);
   return;
}

#ORG 0x00011800
void Turn_Off_MBP()
{
   output_low(PIN_F5);
   return;
}

#ORG 0x00011800
void DELETE_MBP_DATA()                                                           //Clear MBP array to receive data
{
   for(int8 i = 0; i < 81; i++)
   {
      MBP_DATA[i] = 0;
   }
   return;
}

#ORG 0x00011800
void CHECK_ACK_FROM_DC_10k()                                                     //Wait ACK from DC for 10s
{
   for(int32 num = 0; num < 1000000; num++) 
   {
      if(kbhit(DC))                                                              //kbhit(PC)
      {
         DC_ACK = fgetc(DC);                                                     //PC   
         break;
      }                                                                          //delay_ms(1);
   }
   return;
}

#ORG 0x00011800
void GET_MBP_DATA(int16 transf_size)
{
   int16 n = 0;
   int8 input = 0;
   for(int32 i = 0; i < 99000000; i++)                                            //1000000
   {                                                                              //99000000 es tiempo suficiente para transferir un sector
      if(kbhit(DC))
      {
         input = fgetc(DC);                                                      //get data from MBP
         WRITE_DATA_BYTE_OF(DC_STATUS_ADDRESS,input);                            //Save data on OF, SCF, SMF
         WRITE_DATA_BYTE_SCF(DC_STATUS_ADDRESS,input);
         WRITE_DATA_BYTE_SMF(DC_STATUS_ADDRESS,input);
         n++;
         DC_STATUS_ADDRESS = DC_STATUS_ADDRESS + 1;
         if(n==transf_size)                                                      //sale del for cuando se completa la cantidad de bytes
         {
         break;
         }
      }
   }

   DC_STATUS_ADDRESS=0x06660000;
  
   fprintf(PC,"Transferred %ld Bytes",n);
   n=0;
   output_high(PIN_C4);                                                          //COM_MUX COM side
   return;
}

#ORG 0x00011800
void DATACOLLECTION_TEST_OPERATION(int8 cmd1,int8 cmd2,int8 cmd3,int8 cmd4,int8 cmd5,int8 cmd6,int8 cmd7)
{
   DELETE_MBP_DATA();                                                            //Clear MBP array to receive data
   // LOOP_DC_STATUS_ADDRESS();                                                   //realiza un loop verificando si se esta por alcanzar el limite de espacio asignado
   REFRESH_SECTOR_OF(0x06,0x66,0x00,0x00);                                       //clear 1 sector OBC flash DC part
   REFRESH_SECTOR_SCF(0x06,0x66,0x00,0x00);                                      //clear 1 sector COM flash DC part 
   REFRESH_SECTOR_SMF(0x06,0x66,0x00,0x00);                                      //clear 1 sector MISSION flash DC part
   
   int16 data_pckts = make16(cmd6,cmd7);
   int16 data_size = data_pckts*81;
   
   fprintf(PC,"sending commands to MBP\r\n");
   Turn_On_MBP();                                                                 //RF5=HIGH
   delay_ms(30);

   fputc(cmd1,DC);
   delay_ms(100);
   fputc(cmd2,DC);
   delay_ms(100);
   fputc(cmd3,DC);
   delay_ms(100);
   fputc(cmd4,DC);
   delay_ms(100);
   fputc(cmd5,DC);
   delay_ms(100);
   fputc(cmd6,DC);
   delay_ms(100);
   fputc(cmd7,DC);

   CHECK_ACK_FROM_DC_10k();                                                      //Wait ACK from MBP for 10s
   if(DC_ACK == 0x20)                                                            //Success ACK
   {
      fprintf(PC,"Received ACK From MBP\r\n");
      //delay_ms(1000);
      DC_ACK = 0;
      output_low(PIN_C4);                                                        //SCF main side
      output_low(PIN_A5);                                                        //SMF main side
      fprintf(PC,"TRANSFERRING %lx PACKETS\r\n",data_pckts);
      
      GET_MBP_DATA(data_size);

   }else{
      DC_ACK = 0;
      fprintf(PC,"FAILURED GETTING ACK From MBP\r\n");
   }

   output_high(PIN_C4);                                                          //COM_MUX COM side
   
   return;
}

#ORG 0x00011800
void MISSION_TEST_OPERATION(int8 cmd1,int8 cmd2,int8 cmd3,int8 cmd4,int8 cmd5,int8 cmd6,int8 cmd7)                                                    //send array of commnands to MBP
{
   fprintf(PC,"sending commands to MBP\r\n");
   Turn_On_MBP();                                                                 //RF5=HIGH
   delay_ms(30);

      fputc(cmd1,DC);
      delay_ms(100);
      fputc(cmd2,DC);
      delay_ms(100);
      fputc(cmd3,DC);
      delay_ms(100);
      fputc(cmd4,DC);
      delay_ms(100);
      fputc(cmd5,DC);
      delay_ms(100);
      fputc(cmd6,DC);
      delay_ms(100);
      fputc(cmd7,DC);

   CHECK_ACK_FROM_DC_10k();                                                      //Wait ACK from DC for 10s
   if(DC_ACK == 0x20)                                                            //Success ACK
   {
      fprintf(PC,"Received ACK From MBP\r\n");
      DC_ACK = 0;
      
   }
   else
   {
      DC_ACK = 0;
      fprintf(PC,"FAILURED GETTING ACK From MBP\r\n");
      fprintf(PC,"PWR cycle and sending commands again\r\n");
      Turn_Off_MBP();
      delay_ms(1000);
      Turn_On_MBP();                                                              //RF5=HIGH
      delay_ms(1000);

      fputc(cmd1,DC);
      delay_ms(100);
      fputc(cmd2,DC);
      delay_ms(100);
      fputc(cmd3,DC);
      delay_ms(100);
      fputc(cmd4,DC);
      delay_ms(100);
      fputc(cmd5,DC);
      delay_ms(100);
      fputc(cmd6,DC);
      delay_ms(100);
      fputc(cmd7,DC);   
   }
   return;
}

#ORG 0x00011800
void MBP_SYNC()
{
   fprintf(PC,"\r\nsending SYNC time to MBP\r\n");
   Turn_On_MBP();                                                                 //RF5=HIGH
   delay_ms(30);
   COLLECT_RESET_DATA();
      if(RESET_bffr[0] == 0x8e)
   {
      fprintf(PC,"Time received from RESET\r\n");

   }
   else
   {
      fprintf(PC,"NO RESET time\r\n");
   }
      
      fputc(0XAA,DC);
      delay_ms(100);
      fputc(reset_bffr[1],DC);                                                       //sec
      delay_ms(100);
      fputc(reset_bffr[2],DC);                                                       //minutes
      delay_ms(100);
      fputc(reset_bffr[3],DC);                                                       //hours
      delay_ms(100);
      fputc(reset_bffr[4],DC);                                                       //day_H
      delay_ms(100);
      fputc(reset_bffr[5],DC);                                                       //day_L
      delay_ms(100);
      fputc(0XBB,DC);
   fprintf(PC,"%x:%x:%x,%x%x\r\n",reset_bffr[1], reset_bffr[2], reset_bffr[3], reset_bffr[4], reset_bffr[5]);
   CHECK_ACK_FROM_DC_10k();                                                      //Wait ACK from DC for 10s
   if(DC_ACK == 0x20)                                                            //Success ACK
   {
      fprintf(PC,"Time Received for MBP\r\n");
      DC_ACK = 0;
      
   }
   else
   {
      DC_ACK = 0;
      fprintf(PC,"FAILURED GETTING ACK From MBP\r\n");
   }
   return;
}

#endif
