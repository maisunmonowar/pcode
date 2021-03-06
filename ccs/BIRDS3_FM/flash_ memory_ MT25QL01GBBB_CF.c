#define SPIPORT_2 COM_FM
#define CS_PIN_2 PIN_B3
#define READ_ID_2           0x9F
#define READ_STATUS_REG_2   0x05 
#define READ_DATA_BYTES_2   0x13  //0x03 for byte
#define ENABLE_WRITE_2      0x06
#define WRITE_PAGE_2        0x12  //0x02 for 3byte
#define ERASE_SECTOR_2      0xDC  //0xD8 for 3byte


void WRITE_ENABLE_CF(){
 output_low(CS_PIN_2);
 
 /////////////////////////////////////////////////////////////
 delay_ms(2);
 spi_xfer(SPIPORT_2,ENABLE_WRITE_2);                //Send 0x06
 /////////////////////////////////////////////////////////////
 
 output_high(CS_PIN_2);  
 return;
}

void sector_erase_CF(unsigned int32 sector_address)
{
   unsigned int8 adsress[4];
   
   adsress[0]  = (unsigned int8)((sector_address>>24) & 0xFF);   // 0x _ _ 00 00 00
   adsress[1]  = (unsigned int8)((sector_address>>16) & 0xFF);   // 0x 00 _ _ 00 00
   adsress[2]  = (unsigned int8)((sector_address>>8) & 0xFF);    // 0x 00 00 _ _ 00
   adsress[3]  = (unsigned int8)((sector_address) & 0xFF);       // 0x 00 00 00 _ _
   
   
   WRITE_ENABLE_CF();
   output_low(CS_PIN_2);             //lower the CS PIN
   delay_us(2);
   
   ///////////////////////////////////////////////////////////////////
   spi_xfer(SPIPORT_2,ERASE_SECTOR_2); //SECTOR ERASE COMAND   (0xDC)
   
   spi_xfer(SPIPORT_2,adsress[0]);   
   spi_xfer(SPIPORT_2,adsress[1]);    
   spi_xfer(SPIPORT_2,adsress[2]);    
   spi_xfer(SPIPORT_2,adsress[3]);
   //////////////////////////////////////////////////////////////////
   
   delay_us(2);
   output_high(CS_PIN_2);           //take CS PIN higher back
   delay_ms(1000);  
   
   return;
}


void WRITE_DATA_BYTE_CF(unsigned int32 page_address, int8 data)
{
   unsigned int8 adsress[4];
   
   //Byte extraction
   adsress[0]  = (unsigned int8)((page_address>>24) & 0xFF);   // 0x _ _ 00 00 00
   adsress[1]  = (unsigned int8)((page_address>>16) & 0xFF);   // 0x 00 _ _ 00 00
   adsress[2]  = (unsigned int8)((page_address>>8) & 0xFF);    // 0x 00 00 _ _ 00
   adsress[3]  = (unsigned int8)((page_address) & 0xFF);       // 0x 00 00 00 _ _
   
   WRITE_ENABLE_CF();
   output_low(CS_PIN_2);           //lower the CS PIN
   delay_us(2);
   
   ////////////////////////////////////////////////////////////////
   spi_xfer(SPIPORT_2,WRITE_PAGE_2); //PAGE WRITE COMAND  (0x12)
  
   spi_xfer(SPIPORT_2,adsress[0]);    
   spi_xfer(SPIPORT_2,adsress[1]);    
   spi_xfer(SPIPORT_2,adsress[2]);    
   spi_xfer(SPIPORT_2,adsress[3]);
   
   spi_xfer(SPIPORT_2,data); 
   ////////////////////////////////////////////////////////////////
   
   output_high(CS_PIN_2);        //take CS PIN higher back

   delay_us(10);  
   
   return;
}

int8 READ_CHIP_ID_CF()
{
 output_low(CS_PIN_2);           //lower the CS PIN
 
 ////////////////////////////////////////////////////////////////
 int8 chip_id;
 spi_xfer(SPIPORT_2,READ_ID_2);    //READ ID COMAND   (0x9F)
 chip_id = spi_xfer(SPIPORT_2);
 ////////////////////////////////////////////////////////////////
 
 output_high(CS_PIN_2);         //take CS PIN higher back
 return chip_id;
}


int8 READ_STATUS_REGISTER_CF()
{
 output_low(CS_PIN_2);           //lower the CS PIN
 
 /////////////////////////////////////////////////////////////////
 int8 status_reg;
 spi_xfer(SPIPORT_2,READ_STATUS_REG_2); //READ STATUS REGISTER COMAND  (0x05)
 status_reg = spi_xfer(SPIPORT_2);
 /////////////////////////////////////////////////////////////////
 
 output_high(CS_PIN_2);         //take CS PIN higher back
 return status_reg;
}
   
int8 READ_DATA_BYTE_CF(unsigned INT32 ADDRESS)
{

 unsigned int8 adsress[4];
   //Byte extraction
   adsress[0]  = (unsigned int8)((ADDRESS>>24) & 0xFF);   // 0x _ _ 00 00 00
   adsress[1]  = (unsigned int8)((ADDRESS>>16) & 0xFF);   // 0x 00 _ _ 00 00
   adsress[2]  = (unsigned int8)((ADDRESS>>8) & 0xFF);    // 0x 00 00 _ _ 00
   adsress[3]  = (unsigned int8)((ADDRESS) & 0xFF);       // 0x 00 00 00 _ _
   
 output_low(CS_PIN_2);                 //lower the CS PIN
 
 //////////////////////////////////////////////////////////////////
 int8 data;
 spi_xfer(SPIPORT_2,READ_DATA_BYTES_2);  //READ DATA COMAND   (0x13)
 
 spi_xfer(SPIPORT_2,adsress[0]);
 spi_xfer(SPIPORT_2,adsress[1]);
 spi_xfer(SPIPORT_2,adsress[2]);
 spi_xfer(SPIPORT_2,adsress[3]);
 //spi_xfer(0x00);
 data = spi_xfer(SPIPORT_2);
 //////////////////////////////////////////////////////////////////
 
 output_high(CS_PIN_2);               //take CS PIN higher back
 return data;
 
}



void TRANSFER_DATA_256byte_CF(unsigned INT32 ADRESS, int PORT_NUM) //read and send the specified data
{
   unsigned long int i;
   
   switch(PORT_NUM)
   {
      case 1:
         for (i=0 ; i < 256 ; i++)
         {
            fputc(READ_DATA_BYTE_CF(ADRESS),PC);
            ADRESS++;
         }
         break;
      case 2:
         for (i=0 ; i < 256 ; i++)
         {
            fputc(READ_DATA_BYTE_CF(ADRESS),reset);
            ADRESS++;
         }
         break;
      case 3:
         for (i=0 ; i < 256 ; i++)
         {
            fputc(READ_DATA_BYTE_CF(ADRESS),com);
            ADRESS++;
         }
         break;
   }
    return;  
}

void WRITE_DATA_NBYTE_CF(unsigned INT32 ADDRES,int32 data_byte) //read and send the specified data
{
   for (int32 i=0 ; i < data_byte ; i++)
   {
      WRITE_DATA_BYTE_CF(ADDRES,0x55);
      ADDRES++;
   }
   return;
}

void TRANSFER_DATA_NBYTE_TOPC_CF(unsigned INT32 ADRESS,int32 data_byte) //read and send the specified data
{
   for (int32 i=0 ; i < data_byte ; i++)
   {
      fputc(READ_DATA_BYTE_CF(ADRESS),PC);
      ADRESS++;
   }
   return;
}


