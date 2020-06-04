#ifndef FLASH_MEMORY_MT25QL01GBBB_OF_C
#define FLASH_MEMORY_MT25QL01GBBB_OF_C

#define SPIPORT MAIN_FM
#define SPIPORT_2 COM_FM
#define SPIPORT_3 MISSION_FM

#define CS_PIN PIN_E2
#define CS_PIN_2 PIN_B3
#define CS_PIN_3 PIN_A2

#define READ_ID              0x9F
#define READ_STATUS_REG      0x05 
#define READ_DATA_BYTES      0x13  //0x03 for byte
#define ENABLE_WRITE         0x06
#define WRITE_PAGE           0x12  //0x02 for 3byte
#define ERASE_SECTOR         0xDC  //0xD8 for 3byte
#define ERASE_4KB_SUBSECTOR  0x21
#define ERASE_32KB_SUBSECTOR 0x5C
#define DIE_ERASE            0xC4


#ORG 0x00011800
void WRITE_ENABLE_OF()
{
   output_low(CS_PIN);

   spi_xfer(SPIPORT,ENABLE_WRITE);                //Send 0x06

   output_high(CS_PIN);
   return;
}

#ORG 0x00011800
void WRITE_ENABLE_SCF()
{
   output_low(CS_PIN_2);

   /////////////////////////////////////////////////////////////
   //delay_ms(2);
   spi_xfer(SPIPORT_2,ENABLE_WRITE);                //Send 0x06
   /////////////////////////////////////////////////////////////

   output_high(CS_PIN_2);  
   return;
}

#ORG 0x00011800
void WRITE_ENABLE_SMF()
{
   output_low(CS_PIN_3);

   /////////////////////////////////////////////////////////////
   //delay_ms(2);
   spi_xfer(SPIPORT_3,ENABLE_WRITE);                //Send 0x06
   /////////////////////////////////////////////////////////////

   output_high(CS_PIN_3);
   return;
}

#ORG 0x00011800
void sector_erase_OF(unsigned int32 sector_address)                              //borra un sector de la flash
{
   unsigned int8 adsress[4];
   
   adsress[0]  = (unsigned int8)((sector_address>>24) & 0xFF);                   // 0x _ _ 00 00 00
   adsress[1]  = (unsigned int8)((sector_address>>16) & 0xFF);                   // 0x 00 _ _ 00 00
   adsress[2]  = (unsigned int8)((sector_address>>8) & 0xFF);                    // 0x 00 00 _ _ 00
   adsress[3]  = (unsigned int8)((sector_address) & 0xFF);                       // 0x 00 00 00 _ _
   
   
   WRITE_ENABLE_OF();
   output_low(CS_PIN);                                                           //lower the CS PIN
   delay_us(2);
   
   ///////////////////////////////////////////////////////////////////
   spi_xfer(SPIPORT,ERASE_SECTOR);                                               //SECTOR ERASE COMAND   (0xDC)
   
   spi_xfer(SPIPORT,adsress[0]);   
   spi_xfer(SPIPORT,adsress[1]);    
   spi_xfer(SPIPORT,adsress[2]);    
   spi_xfer(SPIPORT,adsress[3]);
   //////////////////////////////////////////////////////////////////
   
   delay_us(2);
   output_high(CS_PIN);                                                          //take CS PIN higher back
   //delay_ms(1000);
   delay_ms(750);
   
   return;
}

#ORG 0x00011800
void sector_erase_SCF(unsigned int32 sector_address)
{
   unsigned int8 adsress[4];
   
   adsress[0]  = (unsigned int8)((sector_address>>24) & 0xFF);                   // 0x _ _ 00 00 00
   adsress[1]  = (unsigned int8)((sector_address>>16) & 0xFF);                   // 0x 00 _ _ 00 00
   adsress[2]  = (unsigned int8)((sector_address>>8) & 0xFF);                    // 0x 00 00 _ _ 00
   adsress[3]  = (unsigned int8)((sector_address) & 0xFF);                       // 0x 00 00 00 _ _
   
   
   WRITE_ENABLE_SCF();
   output_low(CS_PIN_2);                                                         //lower the CS PIN
   delay_us(2);
   
   ///////////////////////////////////////////////////////////////////
   spi_xfer(SPIPORT_2,ERASE_SECTOR);                                             //SECTOR ERASE COMAND   (0xDC)
   
   spi_xfer(SPIPORT_2,adsress[0]);   
   spi_xfer(SPIPORT_2,adsress[1]);    
   spi_xfer(SPIPORT_2,adsress[2]);    
   spi_xfer(SPIPORT_2,adsress[3]);
   //////////////////////////////////////////////////////////////////
   
   delay_us(2);
   output_high(CS_PIN_2);                                                        //take CS PIN higher back
   //delay_ms(1000);
   delay_ms(750);
   
   return;
}

#ORG 0x00011800
void sector_erase_SMF(unsigned int32 sector_address)
{
   unsigned int8 adsress[4];
   
   adsress[0]  = (unsigned int8)((sector_address>>24) & 0xFF);   // 0x _ _ 00 00 00
   adsress[1]  = (unsigned int8)((sector_address>>16) & 0xFF);   // 0x 00 _ _ 00 00
   adsress[2]  = (unsigned int8)((sector_address>>8) & 0xFF);    // 0x 00 00 _ _ 00
   adsress[3]  = (unsigned int8)((sector_address) & 0xFF);       // 0x 00 00 00 _ _
   
   
   WRITE_ENABLE_SMF();
   output_low(CS_PIN_3);             //lower the CS PIN
   delay_us(2);
   
   ///////////////////////////////////////////////////////////////////
   spi_xfer(SPIPORT_3,ERASE_SECTOR); //SECTOR ERASE COMAND   (0xDC)
   
   spi_xfer(SPIPORT_3,adsress[0]);   
   spi_xfer(SPIPORT_3,adsress[1]);    
   spi_xfer(SPIPORT_3,adsress[2]);    
   spi_xfer(SPIPORT_3,adsress[3]);
   //////////////////////////////////////////////////////////////////
   
   delay_us(2);
   output_high(CS_PIN_3);           //take CS PIN higher back
   //delay_ms(1000);  
   delay_ms(750);
   return;
}

#ORG 0x00011800
void SUBSECTOR_4KB_ERASE_OF(unsigned int32 sector_address)                       //Funcion que borra un sector de 4KB de la Main Flash
{                                                                                //Recibe la direccion del sector que se quiere borrar
   unsigned int8 adsress[4];
   
   adsress[0]  = (unsigned int8)((sector_address>>24) & 0xFF);                   // 0x _ _ 00 00 00
   adsress[1]  = (unsigned int8)((sector_address>>16) & 0xFF);                   // 0x 00 _ _ 00 00
   adsress[2]  = (unsigned int8)((sector_address>>8) & 0xFF);                    // 0x 00 00 _ _ 00
   adsress[3]  = (unsigned int8)((sector_address) & 0xFF);                       // 0x 00 00 00 _ _
   
   
   WRITE_ENABLE_OF();                                                            //Funcion que habilita escritura en Own Flash
   output_low(CS_PIN);                                                           //lower the CS PIN
   delay_us(2);
   
   ///////////////////////////////////////////////////////////////////
   spi_xfer(SPIPORT,ERASE_4KB_SUBSECTOR);                                        //SECTOR ERASE COMAND   (0xDC)
   
   spi_xfer(SPIPORT,adsress[0]);                                                 //Se le pasa la direccion del sector a borrar
   spi_xfer(SPIPORT,adsress[1]);    
   spi_xfer(SPIPORT,adsress[2]);    
   spi_xfer(SPIPORT,adsress[3]);
   //////////////////////////////////////////////////////////////////
   
   delay_us(2);
   output_high(CS_PIN);                                                          //take CS PIN higher back
   delay_ms(100);  
   
   return;
}

#ORG 0x00011800
void SUBSECTOR_4KB_ERASE_SCF(unsigned int32 sector_address)                      //Funcion que borra un sector de 4KB de la COM Flash
{
   unsigned int8 adsress[4];
   
   adsress[0]  = (unsigned int8)((sector_address>>24) & 0xFF);                   // 0x _ _ 00 00 00
   adsress[1]  = (unsigned int8)((sector_address>>16) & 0xFF);                   // 0x 00 _ _ 00 00
   adsress[2]  = (unsigned int8)((sector_address>>8) & 0xFF);                    // 0x 00 00 _ _ 00
   adsress[3]  = (unsigned int8)((sector_address) & 0xFF);                       // 0x 00 00 00 _ _
   
   
   WRITE_ENABLE_SCF();                                                           //Funcion que habilita escritura en COM Flash
   output_low(CS_PIN_2);                                                         //lower the CS PIN
   delay_us(2);
   
   ///////////////////////////////////////////////////////////////////
   spi_xfer(SPIPORT_2,ERASE_4KB_SUBSECTOR); //SECTOR ERASE COMAND   (0xDC)
   
   spi_xfer(SPIPORT_2,adsress[0]);   
   spi_xfer(SPIPORT_2,adsress[1]);    
   spi_xfer(SPIPORT_2,adsress[2]);    
   spi_xfer(SPIPORT_2,adsress[3]);
   //////////////////////////////////////////////////////////////////
   
   delay_us(2);
   output_high(CS_PIN_2);                                                        //take CS PIN higher back
   delay_ms(10);  
   
   return;
}

#ORG 0x00011800
void SUBSECTOR_4KB_ERASE_SMF(unsigned int32 sector_address)                      //Funcion que borra un sector de 4KB de la Mission Flash
{
   unsigned int8 adsress[4];
   
   adsress[0]  = (unsigned int8)((sector_address>>24) & 0xFF);                   // 0x _ _ 00 00 00
   adsress[1]  = (unsigned int8)((sector_address>>16) & 0xFF);                   // 0x 00 _ _ 00 00
   adsress[2]  = (unsigned int8)((sector_address>>8) & 0xFF);                    // 0x 00 00 _ _ 00
   adsress[3]  = (unsigned int8)((sector_address) & 0xFF);                       // 0x 00 00 00 _ _
   
   
   WRITE_ENABLE_SMF();                                                           //Funcion que habilita escritura en Mission Flash
   output_low(CS_PIN_3);                                                         //lower the CS PIN
   delay_us(2);
   
   ///////////////////////////////////////////////////////////////////
   spi_xfer(SPIPORT_3,ERASE_4KB_SUBSECTOR);                                      //SECTOR ERASE COMAND   (0xDC)
   
   spi_xfer(SPIPORT_3,adsress[0]);   
   spi_xfer(SPIPORT_3,adsress[1]);    
   spi_xfer(SPIPORT_3,adsress[2]);    
   spi_xfer(SPIPORT_3,adsress[3]);
   //////////////////////////////////////////////////////////////////
   
   delay_us(2);
   output_high(CS_PIN_3);                                                        //take CS PIN higher back
   delay_ms(1000);  
   
   return;
}

#ORG 0x00011800
void WRITE_DATA_BYTE_OF(unsigned int32 page_address, int8 data)                  //Funcion que escribe un Byte en la Main Flash
{
   unsigned int8 adsress[4];
   
   //Byte extraction
   adsress[0]  = (unsigned int8)((page_address>>24) & 0xFF);                     // 0x _ _ 00 00 00
   adsress[1]  = (unsigned int8)((page_address>>16) & 0xFF);                     // 0x 00 _ _ 00 00
   adsress[2]  = (unsigned int8)((page_address>>8) & 0xFF);                      // 0x 00 00 _ _ 00
   adsress[3]  = (unsigned int8)((page_address) & 0xFF);                         // 0x 00 00 00 _ _
   
   WRITE_ENABLE_OF();
   output_low(CS_PIN);                                                           //lower the CS PIN
   //delay_us(2);
   
   ////////////////////////////////////////////////////////////////
   spi_xfer(SPIPORT,WRITE_PAGE);                                                 //PAGE WRITE COMAND  (0x12)
  
   spi_xfer(SPIPORT,adsress[0]);    
   spi_xfer(SPIPORT,adsress[1]);    
   spi_xfer(SPIPORT,adsress[2]);    
   spi_xfer(SPIPORT,adsress[3]);
   
   spi_xfer(SPIPORT,data); 
   ////////////////////////////////////////////////////////////////
   
   output_high(CS_PIN);                                                          //take CS PIN higher back

   //delay_us(5);  
   
   return;
}

#ORG 0x00011800
void WRITE_DATA_BYTE_SCF(unsigned int32 page_address, int8 data)                 //Funcion que escribe un Byte en la COM Flash
{
   unsigned int8 adsress[4];
   
   //Byte extraction
   adsress[0]  = (unsigned int8)((page_address>>24) & 0xFF);                     // 0x _ _ 00 00 00
   adsress[1]  = (unsigned int8)((page_address>>16) & 0xFF);                     // 0x 00 _ _ 00 00
   adsress[2]  = (unsigned int8)((page_address>>8) & 0xFF);                      // 0x 00 00 _ _ 00
   adsress[3]  = (unsigned int8)((page_address) & 0xFF);                         // 0x 00 00 00 _ _
   
   WRITE_ENABLE_SCF();
   output_low(CS_PIN_2);                                                         //lower the CS PIN
   //delay_us(2);
   
   ////////////////////////////////////////////////////////////////
   spi_xfer(SPIPORT_2,WRITE_PAGE);                                               //PAGE WRITE COMAND  (0x12)
  
   spi_xfer(SPIPORT_2,adsress[0]);    
   spi_xfer(SPIPORT_2,adsress[1]);    
   spi_xfer(SPIPORT_2,adsress[2]);    
   spi_xfer(SPIPORT_2,adsress[3]);
   
   spi_xfer(SPIPORT_2,data); 
   ////////////////////////////////////////////////////////////////
   
   output_high(CS_PIN_2);                                                        //take CS PIN higher back

   //delay_us(5);  
   
   return;
}

#ORG 0x00011800
void WRITE_DATA_BYTE_SMF(unsigned int32 page_address, int8 data)                 //Funcion que escribe un Byte en la Mission Flash
{
   unsigned int8 adsress[4];
   
   //Byte extraction
   adsress[0]  = (unsigned int8)((page_address>>24) & 0xFF);                     // 0x _ _ 00 00 00
   adsress[1]  = (unsigned int8)((page_address>>16) & 0xFF);                     // 0x 00 _ _ 00 00
   adsress[2]  = (unsigned int8)((page_address>>8) & 0xFF);                      // 0x 00 00 _ _ 00
   adsress[3]  = (unsigned int8)((page_address) & 0xFF);                         // 0x 00 00 00 _ _
   
   WRITE_ENABLE_SMF();
   output_low(CS_PIN_3);                                                         //lower the CS PIN
   //delay_us(2);
   
   ////////////////////////////////////////////////////////////////
   spi_xfer(SPIPORT_3,WRITE_PAGE);                                               //PAGE WRITE COMAND  (0x12)
  
   spi_xfer(SPIPORT_3,adsress[0]);    
   spi_xfer(SPIPORT_3,adsress[1]);    
   spi_xfer(SPIPORT_3,adsress[2]);    
   spi_xfer(SPIPORT_3,adsress[3]);
   
   spi_xfer(SPIPORT_3,data); 
   ////////////////////////////////////////////////////////////////
   
   output_high(CS_PIN_3);                                                        //take CS PIN higher back

   //delay_us(10);  
   
   return;
}

#ORG 0x00011800
int8 READ_DATA_BYTE_OF(unsigned INT32 ADDRESS)
{

   unsigned int8 adsress[4];
   //Byte extraction
   adsress[0]  = (unsigned int8)((ADDRESS>>24) & 0xFF);                          // 0x _ _ 00 00 00
   adsress[1]  = (unsigned int8)((ADDRESS>>16) & 0xFF);                          // 0x 00 _ _ 00 00
   adsress[2]  = (unsigned int8)((ADDRESS>>8) & 0xFF);                           // 0x 00 00 _ _ 00
   adsress[3]  = (unsigned int8)((ADDRESS) & 0xFF);                              // 0x 00 00 00 _ _

   output_low(CS_PIN);                                                           //lower the CS PIN

   //////////////////////////////////////////////////////////////////
   int8 data;
   spi_xfer(SPIPORT,READ_DATA_BYTES);                                            //READ DATA COMAND   (0x13)

   spi_xfer(SPIPORT,adsress[0]);
   spi_xfer(SPIPORT,adsress[1]);
   spi_xfer(SPIPORT,adsress[2]);
   spi_xfer(SPIPORT,adsress[3]);
   data = spi_xfer(SPIPORT);
   //////////////////////////////////////////////////////////////////

   output_high(CS_PIN);                                                          //take CS PIN higher back
   return data;

}

#ORG 0x00011800
int8 READ_DATA_BYTE_SCF(unsigned INT32 ADDRESS)
{

   unsigned int8 adsress[4];
   //Byte extraction
   adsress[0]  = (unsigned int8)((ADDRESS>>24) & 0xFF);                          // 0x _ _ 00 00 00
   adsress[1]  = (unsigned int8)((ADDRESS>>16) & 0xFF);                          // 0x 00 _ _ 00 00
   adsress[2]  = (unsigned int8)((ADDRESS>>8) & 0xFF);                           // 0x 00 00 _ _ 00
   adsress[3]  = (unsigned int8)((ADDRESS) & 0xFF);                              // 0x 00 00 00 _ _

   output_low(CS_PIN_2);                                                           //lower the CS PIN

   //////////////////////////////////////////////////////////////////
   int8 data;
   spi_xfer(SPIPORT_2,READ_DATA_BYTES);                                            //READ DATA COMAND   (0x13)

   spi_xfer(SPIPORT_2,adsress[0]);
   spi_xfer(SPIPORT_2,adsress[1]);
   spi_xfer(SPIPORT_2,adsress[2]);
   spi_xfer(SPIPORT_2,adsress[3]);
   data = spi_xfer(SPIPORT_2);
   //////////////////////////////////////////////////////////////////

   output_high(CS_PIN_2);                                                          //take CS PIN higher back
   return data;
 
}

#ORG 0x00011800
int8 READ_DATA_BYTE_SMF(unsigned INT32 ADDRESS)
{
   unsigned int8 adsress[4];
   //Byte extraction
   adsress[0]  = (unsigned int8)((ADDRESS>>24) & 0xFF);                          // 0x _ _ 00 00 00
   adsress[1]  = (unsigned int8)((ADDRESS>>16) & 0xFF);                          // 0x 00 _ _ 00 00
   adsress[2]  = (unsigned int8)((ADDRESS>>8) & 0xFF);                           // 0x 00 00 _ _ 00
   adsress[3]  = (unsigned int8)((ADDRESS) & 0xFF);                              // 0x 00 00 00 _ _
   
   output_low(CS_PIN_3);                                                           //lower the CS PIN
 
   //////////////////////////////////////////////////////////////////
   int8 data;
   spi_xfer(SPIPORT_3,READ_DATA_BYTES);                                            //READ DATA COMAND   (0x13)

   spi_xfer(SPIPORT_3,adsress[0]);
   spi_xfer(SPIPORT_3,adsress[1]);
   spi_xfer(SPIPORT_3,adsress[2]);
   spi_xfer(SPIPORT_3,adsress[3]);
   data = spi_xfer(SPIPORT_3);
   //////////////////////////////////////////////////////////////////

   output_high(CS_PIN_3);                                                          //take CS PIN higher back
   return data;
}

#ORG 0x00011800
void TRANSFER_DATA_NBYTE_TOPC_OF(unsigned INT32 ADRESS,int32 data_byte)          //read and send the specified data
{
   for (int32 i=0 ; i < data_byte ; i++)
   {
      fputc(READ_DATA_BYTE_OF(ADRESS),PC);
      ADRESS++;
   }
   return;
}

#ORG 0x00011800
void TRANSFER_DATA_NBYTE_TOPC_SCF(unsigned INT32 ADRESS,int32 data_byte)         //read and send the specified data
{
   for (int32 i=0 ; i < data_byte ; i++)
   {
      fprintf(PC,"%x",READ_DATA_BYTE_SCF(ADRESS));
      ADRESS++;
   }
   return;
}

#ORG 0x00011800
void TRANSFER_DATA_NBYTE_TOPC_SMF(unsigned INT32 ADRESS,int32 data_byte)         //read and send the specified data
{
   for (int32 i=0 ; i < data_byte ; i++)
   {
      fputc(READ_DATA_BYTE_SMF(ADRESS),PC);
      ADRESS++;
   }
   return;
}

#ORG 0x00011800
void TRANSFER_DATA_NBYTE_SMFtoOF(unsigned INT32 FROM_ADRESS,unsigned INT32 TO_ADRESS,int32 data_byte) //transfer data from MISSION FLASH to MAIN FLASH
{
   for (int32 i=0 ; i < data_byte ; i++)
   {
      WRITE_DATA_BYTE_OF(TO_ADRESS,READ_DATA_BYTE_SMF(FROM_ADRESS));
      FROM_ADRESS++;
      TO_ADRESS++;
   }
   return;
}

#ORG 0x00011800
void TRANSFER_DATA_NBYTE_SMFtoSCF(unsigned INT32 FROM_ADRESS,unsigned INT32 TO_ADRESS,int32 data_byte) //transfer data from MISSION FLASH to COM FLASH
{
   for (int32 i=0 ; i < data_byte ; i++)
   {
      WRITE_DATA_BYTE_SCF(TO_ADRESS,READ_DATA_BYTE_SMF(FROM_ADRESS));
      FROM_ADRESS++;
      TO_ADRESS++;
   }
   return;
}

#endif
