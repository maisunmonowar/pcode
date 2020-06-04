#ifndef ANALYZE_COMMAND_C
#define ANALYZE_COMMAND_C

#ORG 0x0001E000
void UPLINK_SUCCESS_CHECK()
{
   if(UPLINK_SUCCESS == 0)
   {
      UPLINK_SUCCESS = 1;
      STORE_FLAG_INFO();                                                         //save flag data to flash memory
      WRITE_FLAG_to_EEPROM();                                                    //save flags on EEPROM from address 0x18000 (75%)
   }
   return;
}

#ORG 0x0001E000
void UPLINK_SUCCESS_ADCS()
{
   if(UPLINK_SUCCESS == 0)
   {
      UPLINK_SUCCESS = 1;
      AUTO_ADCS_DONE = 1;
      STORE_FLAG_INFO();
      WRITE_FLAG_to_EEPROM();
   }else if(AUTO_ADCS_DONE == 0){
      AUTO_ADCS_DONE = 1;
      STORE_FLAG_INFO();
      WRITE_FLAG_to_EEPROM();
   }
   return;
}

#ORG 0x0001E000
void UPLINK_SUCCESS_HSSC()
{
   if(UPLINK_SUCCESS == 0)
   {
      UPLINK_SUCCESS = 1;
      FIRST_HSSC_DONE = 1;
      STORE_FLAG_INFO();
      WRITE_FLAG_to_EEPROM();
   }else if(FIRST_HSSC_DONE == 0){
      FIRST_HSSC_DONE = 1;
      STORE_FLAG_INFO();
      WRITE_FLAG_to_EEPROM();
   }
   return;
}

#ORG 0x0001E000
//I actually don't know what this function does. 
//*PURPOSE Something i don't know. 
void UPLINK_SUCCESS_MBP()
{
   if(UPLINK_SUCCESS == 0)
   {
      UPLINK_SUCCESS = 1;
      AUTO_MBP_DONE = 1;
      STORE_FLAG_INFO();                                                         //store flag info on flash
      WRITE_FLAG_to_EEPROM();                                                    //store flag info on EEPROM
   }else if(AUTO_MBP_DONE == 0){
      AUTO_MBP_DONE = 1;
      STORE_FLAG_INFO();                                                         //store flag info on flash
      WRITE_FLAG_to_EEPROM();                                                    //store flag info on EEPROM
   }
   return;
   //I actually don't know what this function does. 
   //*PURPOSE Something i don't know. 
   //*AUTHOR Maisun Ibn Monowar
}

void UPLINK_SUCCESS_CAM()
{
   if(UPLINK_SUCCESS == 0)
   {
      AUTO_CAM_DONE = 1;
      UPLINK_SUCCESS = 1;
      STORE_FLAG_INFO();                                                         //store flag info on flash
      WRITE_FLAG_to_EEPROM();                                                    //store flag info on EEPROM
   }else if(AUTO_CAM_DONE == 0){
      AUTO_CAM_DONE = 1;
      STORE_FLAG_INFO();                                                         //store flag info on flash
      WRITE_FLAG_to_EEPROM();                                                    //store flag info on EEPROM
   }
   return;
}


#ORG 0x0001E000
int8 CHECK_MEMORY_FUNCTION(int8 data)                                            //evita operacion de memoria como comandos reservados
{
   if((data == 0xe0)||(data == 0xe1)||(data == 0xe2))
   {
      data = 0;
   }
   if((data == 0x12)||(data == 0x32)||(data == 0x21))
   {
      data = 0;
   }
   return data;
}

#endif
