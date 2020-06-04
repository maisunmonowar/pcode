#ifndef SWITCHCASE_C
#define SWITCHCASE_C

void EXECUTE_MISSION_from_COM(int8 CMD1,int8 CMD2,int8 CMD3,int8 CMD4,int8 CMD5,int8 CMD6,int8 CMD7)
{
   switch(CMD1)
   {
      case 0xC0:
         REPLY_TO_COM(0x66,0);
         SAVE_SAT_LOG(CMD1, 0, CMD2);                                            //save reset data         
         UPLINK_SUCCESS_CAM();                                                   //put uplink succes flag in high and store flags
         ACK_for_COM[14] = 0x00;        
         CAM_TEST_OPERATION(CMD2);                                               //send command to CAM, execute mission and transfer data
         STORE_ADRESS_DATA_TO_FLASH();                                           //store the updated CAM address
         break;
      case 0xA0:
         REPLY_TO_COM(0x66,0);
         SAVE_SAT_LOG(CMD1,CMD2,CMD4);
         unsigned int16 op_duration = (unsigned int16)CMD4*60;         
         UPLINK_SUCCESS_ADCS();
         ACK_for_COM[14] = 0x00;        
         //ADCS_TEST_OPERATION(op_duration,NOMAL_ADCS_MSN);
         ADCS_TEST_OPERATION(op_duration,CMD2);
         STORE_ADRESS_DATA_TO_FLASH();
         break;
      case 0xA1:                                                                 //TLE data reception 
         REPLY_TO_COM(0x66,0);
         UPLINK_SUCCESS_ADCS();
         SAVE_SAT_LOG(CMD1, 0, CMD2);                                            //save reset data and command         
         ACK_for_COM[14] = 0x00;
         ADCS_TLE_JOIN(CMD2,CMD3,CMD4,CMD5,CMD6,CMD7);                           //Receive, assemble and save TLE data in flash
         break;
      case 0xA2:                                                                 //TLE data reception 
         REPLY_TO_COM(0x66,0);
         UPLINK_SUCCESS_ADCS();
         SAVE_SAT_LOG(CMD1, 0, CMD2);                                            //save reset data and command         
         ACK_for_COM[14] = 0x00;
         ADCS_TLE_TRANSFER();                                                    //TRANSFER TLE data to ADCS
         break;    
      case 0xD0:                                                                 //transfer data from Mission BOSS
         REPLY_TO_COM(0x66,0);
         SAVE_SAT_LOG(CMD1, 0, CMD2);                                            //save reset data and command
         UPLINK_SUCCESS_MBP();                                                   //put uplink succes flag in high and store flags
         ACK_for_COM[14] = 0x00;         
         DATACOLLECTION_TEST_OPERATION(CMD1,CMD2,CMD3,CMD4,CMD5,CMD6,CMD7);      //Turn ON MBP, get data, store in flash
         STORE_ADRESS_DATA_TO_FLASH();                                           //store the updated address
         delay_ms(10);
         break; 
      case 0xD1:                                                                 //PSC Mission
         REPLY_TO_COM(0x66,0);
         UPLINK_SUCCESS_MBP();
         ACK_for_COM[14] = 0x00;      
         SAVE_SAT_LOG(CMD1,0,CMD2);                                              //save reset data and command
         MISSION_TEST_OPERATION(CMD1,CMD2,CMD3,CMD4,CMD5,CMD6,CMD7);             //send array of commnands to MBP
         delay_ms(10);
         STORE_ADRESS_DATA_TO_FLASH();                                           //store the updated address
         break;
      case 0xD2:                                                                 //TMCR Mission
         REPLY_TO_COM(0x66,0);
         UPLINK_SUCCESS_MBP();
         ACK_for_COM[14] = 0x00;     
         SAVE_SAT_LOG(CMD1,0,CMD2);                                              //save reset data and command
         MISSION_TEST_OPERATION(CMD1,CMD2,CMD3,CMD4,CMD5,CMD6,CMD7);             //send array of commnands to MBP
         delay_ms(10);
         STORE_ADRESS_DATA_TO_FLASH();                                           //store the updated address
         break;
      case 0xD3:                                                                 //NTU Mission
         REPLY_TO_COM(0x66,0);
         UPLINK_SUCCESS_MBP();
         ACK_for_COM[14] = 0x00;      
         SAVE_SAT_LOG(CMD1,0,CMD2);                                              //save reset data and command
         MISSION_TEST_OPERATION(CMD1,CMD2,CMD3,CMD4,CMD5,CMD6,CMD7);             //send array of commnands to MBP
         delay_ms(10);
         STORE_ADRESS_DATA_TO_FLASH();                                           //store the updated address
         break;
      case 0xD4:                                                                 //SF_WARD Mission
         REPLY_TO_COM(0x66,0);
         UPLINK_SUCCESS_MBP();
         ACK_for_COM[14] = 0x00;     
         SAVE_SAT_LOG(CMD1,0,CMD2);                                              //save reset data and command
         MISSION_TEST_OPERATION(CMD1,CMD2,CMD3,CMD4,CMD5,CMD6,CMD7);             //send array of commnands to MBP
         delay_ms(10);
         STORE_ADRESS_DATA_TO_FLASH();                                           //store the updated address
         break;
      case 0xD5:                                                                 //HNT Mission
         REPLY_TO_COM(0x66,0);
         UPLINK_SUCCESS_MBP();
         ACK_for_COM[14] = 0x00;      
         SAVE_SAT_LOG(CMD1,0,CMD2);                                              //save reset data and command
         MISSION_TEST_OPERATION(CMD1,CMD2,CMD3,CMD4,CMD5,CMD6,CMD7);             //send array of commnands to MBP
         delay_ms(10);
         STORE_ADRESS_DATA_TO_FLASH();                                           //store the updated address
         break;
      case 0xD6:                                                                 //APRS_DP Mission
         REPLY_TO_COM(0x66,0);
         UPLINK_SUCCESS_MBP();
         ACK_for_COM[14] = 0x00;      
         SAVE_SAT_LOG(CMD1,0,CMD2);                                              //save reset data and command
         MISSION_TEST_OPERATION(CMD1,CMD2,CMD3,CMD4,CMD5,CMD6,CMD7);             //send array of commnands to MBP
         delay_ms(10);
         STORE_ADRESS_DATA_TO_FLASH();                                           //store the updated address
         break;
      case 0xD7:                                                                 //dummy data for MBP
         REPLY_TO_COM(0x66,0);
         UPLINK_SUCCESS_MBP();
         ACK_for_COM[14] = 0x00;     
         SAVE_SAT_LOG(CMD1,0,CMD2);                                              //save reset data and command
         MISSION_TEST_OPERATION(CMD1,CMD2,CMD3,CMD4,CMD5,CMD6,CMD7);             //send array of commnands to MBP
         delay_ms(10);
         STORE_ADRESS_DATA_TO_FLASH();                                           //store the updated address
         break;
      case 0xDF:                                                                 //dummy data for MBP
         REPLY_TO_COM(0x66,0);
         UPLINK_SUCCESS_MBP();
         ACK_for_COM[14] = 0x00;      
         SAVE_SAT_LOG(CMD1,0,CMD2);                                              //save reset data and command
         MISSION_TEST_OPERATION(CMD1,CMD2,CMD3,CMD4,CMD5,CMD6,CMD7);             //send array of commnands to MBP
         delay_ms(10);
         STORE_ADRESS_DATA_TO_FLASH();                                           //store the updated address
         break;
      case 0xaa:
         REPLY_TO_COM(0x66,0);
         SAVE_SAT_LOG(CMD1, 0, CMD2);                                            //save reset data and command
         STORE_ADRESS_DATA_TO_FLASH();         
         UPLINK_SUCCESS_CHECK();                                                 //put in high uplink success flag and store flag info on flash
         ACK_for_COM[14] = 0x00;         
         STORE_FLAG_INFO();                                                      //store flag info on flash
         WRITE_FLAG_to_EEPROM();                                                 //store flag info on EEPROM
         break;
      case 0x22:
         UPLINK_SUCCESS_CHECK();                                                 //put in high uplink success flag and store flag info on flash
         ACK_for_COM[14] = 0x00;
         REPLY_TO_COM(0x66,0);                                                   //ACK_for_COM[12] = 0x66 ACK_for_COM[13] = 0         
         SAVE_SAT_LOG(CMD1, 0, CMD2);                                            //save reset data, cmd1 and cmd2 as sat log        
         SEND_CMD_FOR_RESET_SATELLITE();                                         //save flag data, address data and RSV table in flash, send cmd for sat reset
         break;
      case 0xb0:
         REPLY_TO_COM(0x66,0);
         CLEAR_BC_FLAG();                                                        //BC_ATTEMPT_FLAG = 0       
         UPLINK_SUCCESS_CHECK();                                                 //put in high uplink success flag and store flag info on flash
         ACK_for_COM[14] = 0x00;        
         STORE_ADRESS_DATA_TO_FLASH();                                           //save address data to flash memory
         STORE_FLAG_INFO();                                                      //save flag data to flash memory
         WRITE_FLAG_to_EEPROM();                                                 //save flag data to EEPROM
         break;
      case 0xb1:
         REPLY_TO_COM(0x66,0);
         MAKE_BC_FLAG_1();                                                       //BC_ATTEMPT_FLAG = 1         
         UPLINK_SUCCESS_CHECK();                                                 //put in high uplink success flag and store flag info on flash
         ACK_for_COM[14] = 0x00;        
         STORE_ADRESS_DATA_TO_FLASH();                                           //save address data to flash memory
         STORE_FLAG_INFO();                                                      //save flag data to flash memory
         WRITE_FLAG_to_EEPROM();                                                 //save flag data to EEPROM
         break;
      case 0xb2:
         REPLY_TO_COM(0x66,0);
         MAKE_BC_FLAG_2();                                                       //BC_ATTEMPT_FLAG = 2         
         UPLINK_SUCCESS_CHECK();                                                 //put in high uplink success flag and store flag info on flash
         ACK_for_COM[14] = 0x00;         
         STORE_ADRESS_DATA_TO_FLASH();                                           //save address data to flash memory
         STORE_FLAG_INFO();                                                      //save flag data to flash memory
         WRITE_FLAG_to_EEPROM();                                                 //save flag data to EEPROM
         break;
      case 0xb3:
         REPLY_TO_COM(0x66,0);
         MAKE_BC_FLAG_3();                                                       //BC_ATTEMPT_FLAG = 3        
         UPLINK_SUCCESS_CHECK();                                                 //put in high uplink success flag and store flag info on flash
         ACK_for_COM[14] = 0x00;         
         STORE_ADRESS_DATA_TO_FLASH();                                           //save address data to flash memory
         STORE_FLAG_INFO();                                                      //save flag data to flash memory
         WRITE_FLAG_to_EEPROM();                                                 //save flag data to EEPROM
         break;
      case 0xb4:
         REPLY_TO_COM(0x66,0);
         MAKE_BC_FLAG_4();                                                       //BC_ATTEMPT_FLAG = 4         
         UPLINK_SUCCESS_CHECK();                                                 //put in high uplink success flag and store flag info on flash
         ACK_for_COM[14] = 0x00;        
         STORE_ADRESS_DATA_TO_FLASH();                                           //save address data to flash memory
         STORE_FLAG_INFO();                                                      //save flag data to flash memory
         WRITE_FLAG_to_EEPROM();                                                 //save flag data to EEPROM
         break;
      case 0x4b:
         REPLY_TO_COM(0x66,0);
         UPLINK_SUCCESS_CHECK();                                                 //put in high uplink success flag and store flag info on flash
         ACK_for_COM[14] = 0x00;         
         Count_Kill_Flag();                                                      //Enable if Kill_COUNTER > 4
         SAVE_SAT_LOG(CMD1, KILL_COUNTER, CMD2);                                 //save reset data and command
         break;
      case 0xbb:
         REPLY_TO_COM(0x66,0);
         UPLINK_SUCCESS_CHECK();                                                 //put in high uplink success flag and store flag info on flash
         ACK_for_COM[14] = 0x00;      
         Disable_Kill();                                                         //Kill Switch OFF
         SAVE_SAT_LOG(CMD1, KILL_COUNTER, CMD2);                                 //save reset data and command
         break;
      case 0xfa:
         REPLY_TO_COM(0x66,0);
         UPLINK_SUCCESS_HSSC();                                                  //High Sampling Sensor Collect mission
         ACK_for_COM[14] = 0x00;      
         SAVE_SAT_LOG(CMD1, 0, CMD2);         
         unsigned int16 duration = (unsigned int16)CMD2*12;                      //CMD2 is operation time(min), maxima cantidad de lecturas en 2 horas = 1440
         if(duration > 1440){duration = 1440;}                                   // 12 readings in 1 min, every 5 seconds
         HIGHSAMP_SENSOR_COLLECTION(duration);                                   //duration is how many times will be executed
         STORE_ADRESS_DATA_TO_FLASH();
         break;
      case 0x59:      
         //UPLINK_SUCCESS_CHECK();
         //ACK_for_COM[14] = 0x00;      
         REPLY_TO_COM(0x66,0);                                                   //send ACK to COM
         GIVE_ACCESS_SCF_Nsec(CMD2);
         break;
      case 0xee:      
         UPLINK_SUCCESS_CHECK();
         //ACK_for_COM[14] = 0x00;      
         ERASE_EEPROM_INFO();                                                    //erase 512byte(from 0x18000 to 0x181ff)
         MEMORY_ERASE();                                                         //erase OF, SCF, SMF flash memories
         break;
      case 0x88:
      
         //UPLINK_SUCCESS_CHECK();
         //ACK_for_COM[14] = 0x00;
      
         CURRENT_FLAG_STATUS();                                                  //Print on PC port current flag status
         break;
      case 0x9f:
      
         //UPLINK_SUCCESS_CHECK();
         //ACK_for_COM[14] = 0x00;
      
         Disp_RSV();                                                             //show the reserve status (reserve command and reserve table)
         break;
      case 0x50:
         if(UPLINK_SUCCESS == 0){ACK_for_COM[14]=0x77;}
         CW_RESPOND();                                                           //carga el array ACK_for_COM[] con los datos del CW
         break;
      case 0xe0:
         REPLY_TO_COM(0x66,0);
         UPLINK_SUCCESS_CHECK();                                                 //put uplink success flag in HIGH and store flags
         ACK_for_COM[14] = 0x00;      
         REFRESH_SECTOR_OF(CMD2,CMD3,CMD4,CMD5);                                 //Erase 1 sector of OBC flash, also this function contains saving log
         break;
      case 0xe1:
         REPLY_TO_COM(0x66,0);
         UPLINK_SUCCESS_CHECK();                                                 //put uplink success flag in HIGH and store flags
         ACK_for_COM[14] = 0x00;      
         REFRESH_SECTOR_SCF(CMD2,CMD3,CMD4,CMD5);                                //Erase 1 sector of COM flash, also this function contains saving log
         break;
      case 0xe2:
         REPLY_TO_COM(0x66,0);
         UPLINK_SUCCESS_CHECK();                                                 //put uplink success flag in HIGH and store flags
         ACK_for_COM[14] = 0x00;        
         REFRESH_SECTOR_SMF(CMD2,CMD3,CMD4,CMD5);                                //Erase 1 sector of MISION flash, also this function contains saving log
         break;
      case 0x12:
         REPLY_TO_COM(0x66,0);
         UPLINK_SUCCESS_CHECK();                                                 //put uplink success flag in HIGH and store flags
         ACK_for_COM[14] = 0x00;      
         TRANSFER_SECTOR_OF2SCF(CMD2,CMD3,CMD4,CMD5);                            //transfer 1 sector, also this function contains saving log
         break;
      case 0x13:
         REPLY_TO_COM(0x66,0);
         UPLINK_SUCCESS_CHECK();                                                 //put uplink success flag in HIGH and store flags
         ACK_for_COM[14] = 0x00;      
         TRANSFER_SECTOR_OF2SMF(CMD2,CMD3,CMD4,CMD5);                            //transfer 1 sector, also this function contains saving log
         break;
      case 0x21:
         REPLY_TO_COM(0x66,0);
         UPLINK_SUCCESS_CHECK();                                                 //put uplink success flag in HIGH and store flags
         ACK_for_COM[14] = 0x00;         
         TRANSFER_SECTOR_SCF2OF(CMD2,CMD3,CMD4,CMD5);                            //transfer 1 sector, also this function contains saving log
         break;
      case 0x23:
         REPLY_TO_COM(0x66,0);
         UPLINK_SUCCESS_CHECK();                                                 //put uplink success flag in HIGH and store flags
         ACK_for_COM[14] = 0x00;         
         TRANSFER_SECTOR_SCF2SMF(CMD2,CMD3,CMD4,CMD5);                           //transfer 1 sector, this function contains saving log
         break;
      case 0x31:
         REPLY_TO_COM(0x66,0);
         UPLINK_SUCCESS_CHECK();                                                 //put uplink success flag in HIGH and store flags
         ACK_for_COM[14] = 0x00;         
         TRANSFER_SECTOR_SMF2OF(CMD2,CMD3,CMD4,CMD5);                            //transfer 1 sector, also this function contains saving log
         break;
    case 0x32:
         REPLY_TO_COM(0x66,0);
         UPLINK_SUCCESS_CHECK();                                                 //put uplink success flag in HIGH and store flags
         ACK_for_COM[14] = 0x00;      
         TRANSFER_SECTOR_SMF2SCF(CMD2,CMD3,CMD4,CMD5);                          //transfer 1 sector, also this function contains saving log
         break;
    case 0x01:
         REPLY_TO_COM(0x66,0);
         UPLINK_SUCCESS_CHECK();                                                 //put uplink success flag in HIGH and store flags
         ACK_for_COM[14] = 0x00;      
         Send_Command_to_FAB(0x01);                                              //send cmd to FAB to turn ON battery heater
         fprintf(PC,"Sent CMD Heater ON\r\n");
         break;
    case 0x02:
         REPLY_TO_COM(0x66,0);
         UPLINK_SUCCESS_CHECK();                                                 //put uplink success flag in HIGH and store flags
         ACK_for_COM[14] = 0x00;      
         Send_Command_to_FAB(0x02);                                              //send cmd to FAB to turn OFF battery heater
         fprintf(PC,"Sent CMD Heater OFF\r\n");
         break;
    case 0x03:
         REPLY_TO_COM(0x66,0);
         UPLINK_SUCCESS_CHECK();                                                 //put uplink success flag in HIGH and store flags
         ACK_for_COM[14] = 0x00;      
         Send_Command_to_FAB(0x03);                                              //send cmd to FAB to operate Heater in AUTO mode
         fprintf(PC,"Sent CMD Heater AUTO\r\n");
         break;         
//!     case 0x35:
//!         REPLY_TO_COM(0x66,0);
//!         RSV_DATA_DOWNLOAD(CMD1,CMD2,CMD3,CMD4,CMD5,CMD6,CMD7);                  //send array of commnands to COM
//!         fprintf(PC,"Sent CMD to COM for data download\r\n");
//!         break;
      default:
         //bad command. Do nothing.
         break;     
   }
   return;
}

void EXECUTE_MISSION_from_PC(int8 CMD1,int8 CMD2,int8 CMD3,int8 CMD4,int8 CMD5,int8 CMD6,int8 CMD7)
{
   switch(CMD1)
   {
      case 0xC0:
      
         UPLINK_SUCCESS_CAM();                                                   //put uplink succes flag in high and store flags
         ACK_for_COM[14] = 0x00;
      
         SAVE_SAT_LOG(CMD1,0,CMD2);                                              //save reset data
         CAM_TEST_OPERATION(CMD2);                                               //send command to CAM, execute mission and transfer data
         STORE_ADRESS_DATA_TO_FLASH();                                           //store the updated CAM address
         UPLINK_SUCCESS_CHECK();                                                 //put uplink success flag in HIGH and store flags
         break;
      case 0xA0:

         SAVE_SAT_LOG(CMD1,CMD2,CMD4);
         unsigned int16 op_duration = (unsigned int16)CMD4*60;
         
         UPLINK_SUCCESS_ADCS();
         ACK_for_COM[14] = 0x00;
         
         //ADCS_TEST_OPERATION(op_duration,NOMAL_ADCS_MSN);
         ADCS_TEST_OPERATION(op_duration,CMD2);
         STORE_ADRESS_DATA_TO_FLASH();
         break;
      case 0xA1:                                                                 //TLE data reception 
         UPLINK_SUCCESS_ADCS();
         SAVE_SAT_LOG(CMD1, 0, CMD2);                                            //save reset data and command         
         ACK_for_COM[14] = 0x00;
         ADCS_TLE_JOIN(CMD2,CMD3,CMD4,CMD5,CMD6,CMD7);                           //Receive, assemble and save TLE data in flash
         break;
      case 0xA2:                                                                 //TLE data reception 

         UPLINK_SUCCESS_ADCS();
         SAVE_SAT_LOG(CMD1, 0, CMD2);                                            //save reset data and command         
         ACK_for_COM[14] = 0x00;
         ADCS_TLE_TRANSFER();                                                    //TRANSFER TLE data to ADCS
         break;
      case 0xD0:                                                                 //transfer data from Mission BOSS
         REPLY_TO_COM(0x66,0);
         SAVE_SAT_LOG(CMD1, 0, CMD2);                                            //save reset data and command
         
         UPLINK_SUCCESS_MBP();                                                   //put uplink succes flag in high and store flags
         ACK_for_COM[14] = 0x00;
         
         DATACOLLECTION_TEST_OPERATION(CMD1,CMD2,CMD3,CMD4,CMD5,CMD6,CMD7);      //Turn ON MBP, get data, store in flash
         STORE_ADRESS_DATA_TO_FLASH();                                           //store the updated address
         delay_ms(10);
         break; 
      case 0xD1:                                                                 //PSC Mission
      
         UPLINK_SUCCESS_MBP();
         ACK_for_COM[14] = 0x00;
      
         SAVE_SAT_LOG(CMD1,0,CMD2);                                              //save reset data and command
         MISSION_TEST_OPERATION(CMD1,CMD2,CMD3,CMD4,CMD5,CMD6,CMD7);             //send array of commnands to MBP
         delay_ms(10);
         STORE_ADRESS_DATA_TO_FLASH();                                           //store the updated address
         break;
      case 0xD2:                                                                 //TMCR Mission
      
         UPLINK_SUCCESS_MBP();
         ACK_for_COM[14] = 0x00;
      
         SAVE_SAT_LOG(CMD1,0,CMD2);                                              //save reset data and command
         MISSION_TEST_OPERATION(CMD1,CMD2,CMD3,CMD4,CMD5,CMD6,CMD7);             //send array of commnands to MBP
         delay_ms(10);
         STORE_ADRESS_DATA_TO_FLASH();                                           //store the updated address
         break;
      case 0xD3:                                                                 //NTU Mission
      
         UPLINK_SUCCESS_MBP();
         ACK_for_COM[14] = 0x00;
      
         SAVE_SAT_LOG(CMD1,0,CMD2);                                              //save reset data and command
         MISSION_TEST_OPERATION(CMD1,CMD2,CMD3,CMD4,CMD5,CMD6,CMD7);             //send array of commnands to MBP
         delay_ms(10);
         STORE_ADRESS_DATA_TO_FLASH();                                           //store the updated address
         break;
      case 0xD4:                                                                 //SF_WARD Mission
      
         UPLINK_SUCCESS_MBP();
         ACK_for_COM[14] = 0x00;
      
         SAVE_SAT_LOG(CMD1,0,CMD2);                                              //save reset data and command
         MISSION_TEST_OPERATION(CMD1,CMD2,CMD3,CMD4,CMD5,CMD6,CMD7);             //send array of commnands to MBP
         delay_ms(10);
         STORE_ADRESS_DATA_TO_FLASH();                                           //store the updated address
         break;
      case 0xD5:                                                                 //HNT Mission
      
         UPLINK_SUCCESS_MBP();
         ACK_for_COM[14] = 0x00;
      
         SAVE_SAT_LOG(CMD1,0,CMD2);                                              //save reset data and command
         MISSION_TEST_OPERATION(CMD1,CMD2,CMD3,CMD4,CMD5,CMD6,CMD7);             //send array of commnands to MBP
         delay_ms(10);
         STORE_ADRESS_DATA_TO_FLASH();                                           //store the updated address
         break;
      case 0xD6:                                                                 //APRS_DP Mission
      
         UPLINK_SUCCESS_MBP();
         ACK_for_COM[14] = 0x00;
      
         SAVE_SAT_LOG(CMD1,0,CMD2);                                              //save reset data and command
         MISSION_TEST_OPERATION(CMD1,CMD2,CMD3,CMD4,CMD5,CMD6,CMD7);             //send array of commnands to MBP
         delay_ms(10);
         STORE_ADRESS_DATA_TO_FLASH();                                           //store the updated address
         break;
      case 0xD7:                                                                 //dummy data for MBP
      
         UPLINK_SUCCESS_MBP();
         ACK_for_COM[14] = 0x00;
      
         SAVE_SAT_LOG(CMD1,0,CMD2);                                              //save reset data and command
         MISSION_TEST_OPERATION(CMD1,CMD2,CMD3,CMD4,CMD5,CMD6,CMD7);             //send array of commnands to MBP
         delay_ms(10);
         STORE_ADRESS_DATA_TO_FLASH();                                           //store the updated address
         break;
      case 0xDF:                                                                 //dummy data for MBP
         REPLY_TO_COM(0x66,0);
         UPLINK_SUCCESS_MBP();
         ACK_for_COM[14] = 0x00;
      
         SAVE_SAT_LOG(CMD1,0,CMD2);                                              //save reset data and command
         MISSION_TEST_OPERATION(CMD1,CMD2,CMD3,CMD4,CMD5,CMD6,CMD7);             //send array of commnands to MBP
         delay_ms(10);
         STORE_ADRESS_DATA_TO_FLASH();                                           //store the updated address
         break;
      case 0x99:
      
         UPLINK_SUCCESS_CHECK();
         ACK_for_COM[14] = 0x00;
      
         SAVE_SAT_LOG(CMD1,0,CMD2);
         CURRENT_ADDRESS_OF_FLASH();                                             //show address info address on PC
         break;
      case 0xaa:
      
         UPLINK_SUCCESS_CHECK();
         ACK_for_COM[14] = 0x00;
      
         SAVE_SAT_LOG(CMD1,0,CMD2);                                              //save reset data
         STORE_ADRESS_DATA_TO_FLASH();                                           //save address data to flash memory
         STORE_FLAG_INFO();                                                      //store flag info on flash
         WRITE_FLAG_to_EEPROM();                                                 //store flag info on EEPROM
         break;
      case 0x22:
      
         UPLINK_SUCCESS_CHECK();
         //ACK_for_COM[14] = 0x00;
      
         SAVE_SAT_LOG(CMD1,0,CMD2);                                              //save reset data, cmd1 and cmd2 as sat log
         SEND_CMD_FOR_RESET_SATELLITE();                                         //save flag data, address data and RSV table in flash, send cmd for sat reset
         break; 
      case 0xb0:
      
         UPLINK_SUCCESS_CHECK();                                                 //put in high uplink success flag and store flag info on flash
         ACK_for_COM[14] = 0x00;
      
         CLEAR_BC_FLAG();                                                        //BC_ATTEMPT_FLAG = 0
         STORE_ADRESS_DATA_TO_FLASH();                                           //save address data to flash memory
         STORE_FLAG_INFO();                                                      //save flag data to flash memory
         WRITE_FLAG_to_EEPROM();                                                 //save flag data to EEPROM
         break;
      case 0xb1:
      
         UPLINK_SUCCESS_CHECK();                                                 //put in high uplink success flag and store flag info on flash
         ACK_for_COM[14] = 0x00;
      
         MAKE_BC_FLAG_1();                                                       //BC_ATTEMPT_FLAG = 1
         STORE_ADRESS_DATA_TO_FLASH();                                           //save address data to flash memory
         STORE_FLAG_INFO();                                                      //save flag data to flash memory
         WRITE_FLAG_to_EEPROM();                                                 //save flag data to EEPROM
         break;
      case 0xb2:
      
         UPLINK_SUCCESS_CHECK();                                                 //put in high uplink success flag and store flag info on flash
         ACK_for_COM[14] = 0x00;
      
         MAKE_BC_FLAG_2();                                                       //BC_ATTEMPT_FLAG = 2
         STORE_ADRESS_DATA_TO_FLASH();                                           //save address data to flash memory
         STORE_FLAG_INFO();                                                      //save flag data to flash memory
         WRITE_FLAG_to_EEPROM();                                                 //save flag data to EEPROM
         break;               
      case 0xb3:
      
         UPLINK_SUCCESS_CHECK();                                                 //put in high uplink success flag and store flag info on flash
         ACK_for_COM[14] = 0x00;
         
         MAKE_BC_FLAG_3();                                                       //BC_ATTEMPT_FLAG = 3
         STORE_ADRESS_DATA_TO_FLASH();                                           //save address data to flash memory
         STORE_FLAG_INFO();                                                      //save flag data to flash memory
         WRITE_FLAG_to_EEPROM();                                                 //save flag data to EEPROM
         break;
      case 0xb4:
      
         UPLINK_SUCCESS_CHECK();                                                 //put in high uplink success flag and store flag info on flash
         ACK_for_COM[14] = 0x00;
      
         MAKE_BC_FLAG_4();                                                       //BC_ATTEMPT_FLAG = 4
         STORE_ADRESS_DATA_TO_FLASH();                                           //save address data to flash memory
         STORE_FLAG_INFO();                                                      //save flag data to flash memory
         WRITE_FLAG_to_EEPROM();                                                 //save flag data to EEPROM
         break; 
      case 0x4b:
      
         UPLINK_SUCCESS_CHECK();                                                 //put in high uplink success flag and store flag info on flash
         ACK_for_COM[14] = 0x00;
      
         SAVE_SAT_LOG(CMD1,0,CMD2);                                              // save reset data and commands
         Count_Kill_Flag();                                                      //Enable if Kill_COUNTER > 4
         break;
      case 0xbb:
      
         UPLINK_SUCCESS_CHECK();                                                 //put in high uplink success flag and store flag info on flash
         //ACK_for_COM[14] = 0x00;
      
         SAVE_SAT_LOG(CMD1, 0, CMD2);                                            // save reset data and commands
         Disable_Kill();                                                         //kill switch OFF
         break;
      case 0xfa:
      
         UPLINK_SUCCESS_HSSC();                                                  //High Sampling Sensor Collect mission
         ACK_for_COM[14] = 0x00;
      
         SAVE_SAT_LOG(CMD1,0,CMD2);
         
         unsigned int16 duration = (unsigned int16)CMD2*12;                      //CMD2 is operation time(min), maximum duration = 1440
         if(duration > 1440){duration = 1440;}
         HIGHSAMP_SENSOR_COLLECTION(duration);
         //Turn_OFF_ADCS();
         STORE_ADRESS_DATA_TO_FLASH();
         break;
      case 0x59:
      
         UPLINK_SUCCESS_CHECK();
         ACK_for_COM[14] = 0x00;                                                 //send ACK to COM
      
         GIVE_ACCESS_SCF_Nsec(CMD2);
         break; 
      case 0xee:
         UPLINK_SUCCESS_CHECK();
         //ACK_for_COM[14] = 0x00;   
         ERASE_EEPROM_INFO();                                                    //erase 512byte(from 0x18000 to 0x181ff)
         MEMORY_ERASE();                                                         //erase OF, SCF, SMF flash memories
         break; 
      case 0x88:
      
         UPLINK_SUCCESS_CHECK();
         //ACK_for_COM[14] = 0x00;
      
         CURRENT_FLAG_STATUS();                                                  //Print on PC port current flag status
         break;   
      case 0x9f:
      
         UPLINK_SUCCESS_CHECK();
         //ACK_for_COM[14] = 0x00;
      
         Disp_RSV();                                                             //show the reserve status (reserve command and reserve table)
         break; 
      case 0xcf:                                                                 //only for execution from PC
      
         UPLINK_SUCCESS_CHECK();
         //ACK_for_COM[14] = 0x00;
      
         table_refresh();                                                        //table and flags are come back to default
         break;
      case 0x6a:
      
         UPLINK_SUCCESS_CHECK();                                                 //put uplink success flag in HIGH and store flags
         ACK_for_COM[14] = 0x00;
      
         RESET_FLAG_DATA();                                                      //clear all flags and save
         break;
      case 0xe0:
      
         UPLINK_SUCCESS_CHECK();                                                 //put uplink success flag in HIGH and store flags
         ACK_for_COM[14] = 0x00;
      
         REFRESH_SECTOR_OF(CMD2,CMD3,CMD4,CMD5);                                 //Erase 1 sector of OBC flash, also this function contains saving log
         break;
      case 0xe1:
      
         UPLINK_SUCCESS_CHECK();                                                 //put uplink success flag in HIGH and store flags
         ACK_for_COM[14] = 0x00;
      
         REFRESH_SECTOR_SCF(CMD2,CMD3,CMD4,CMD5);                                //Erase 1 sector of COM flash, also this function contains saving log
         break;
      case 0xe2:
      
         UPLINK_SUCCESS_CHECK();                                                 //put uplink success flag in HIGH and store flags
         ACK_for_COM[14] = 0x00;
      
         REFRESH_SECTOR_SMF(CMD2,CMD3,CMD4,CMD5);                                //Erase 1 sector of MISION flash, also this function contains saving log
         break;
      case 0x12:
      
         UPLINK_SUCCESS_CHECK();                                                 //put uplink success flag in HIGH and store flags
         ACK_for_COM[14] = 0x00;
      
         TRANSFER_SECTOR_OF2SCF(CMD2,CMD3,CMD4,CMD5);                            //transfer 1 sector, also this function contains saving log
         break;
      case 0x32:
      
         UPLINK_SUCCESS_CHECK();                                                 //put uplink success flag in HIGH and store flags
         ACK_for_COM[14] = 0x00;
      
         TRANSFER_SECTOR_SMF2SCF(CMD2,CMD3,CMD4,CMD5);                           //transfer 1 sector, also this function contains saving log
         break;
      case 0x21:
      
         UPLINK_SUCCESS_CHECK();                                                 //put uplink success flag in HIGH and store flags
         ACK_for_COM[14] = 0x00;
      
         TRANSFER_SECTOR_SCF2OF(CMD2,CMD3,CMD4,CMD5);                            //transfer 1 sector, also this function contains saving log
         break;
      case 0x01:
      
         UPLINK_SUCCESS_CHECK();                                                 //put uplink success flag in HIGH and store flags
         ACK_for_COM[14] = 0x00;
      
         Send_Command_to_FAB(0x01);                                              //send cmd to FAB to turn ON battery heater
         fprintf(PC,"Sent CMD Heater ON\r\n");
         break;
      case 0x02:
      
         UPLINK_SUCCESS_CHECK();                                                 //put uplink success flag in HIGH and store flags
         ACK_for_COM[14] = 0x00;
      
         Send_Command_to_FAB(0x02);                                              //send cmd to FAB to turn OFF battery heater
         fprintf(PC,"Sent CMD Heater OFF\r\n");
         break;
      case 0x03:

         UPLINK_SUCCESS_CHECK();                                                 //put uplink success flag in HIGH and store flags
         ACK_for_COM[14] = 0x00;
      
         Send_Command_to_FAB(0x03);                                              //send cmd to FAB to operate Heater in AUTO mode
         fprintf(PC,"Sent CMD Heater AUTO\r\n");
         break;         
      /*case 0x35:
         fprintf(PC,"Sent CMD to COM for data download\r\n");
         RSV_DATA_DOWNLOAD(CMD1,CMD2,CMD3,CMD4,CMD5,CMD6,CMD7);                  //send array of commnands to COM
         
         break;*/
   }
   return;
}

#endif
