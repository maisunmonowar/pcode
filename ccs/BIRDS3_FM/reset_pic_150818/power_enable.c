void delayloop(int32 seconds)     
{ 
 int32 count = 1; 
  
   while(count <= seconds) 
   { 
    delay_ms(1000); 
    count++; 
   } 
    
 return; 
}



void unreg_first_run(void)
{

 //delayloop(30);

 fprintf(PORT1,"******Initializing antenna deployment first trial *********\n\r");

 RD6 = 1; // Switch enale for COM PIC
 fprintf(PORT1,"******COM PIC ON *********\n\r");
 RD7 = 1; // Switch enale for Main PIC
 fprintf(PORT1,"******Main PIC ON *********\n\r");


 RC4 = 1; // Buckboost enable for 3V3 #1 
 RD1 = 0; // Switch enale for 3V3#1
 
 RD3 = 1; // Buckboost enable for 3V3 #2
 RD0 = 0; // Switch enable for 3V3 #2
  
 RC2 = 1; //Buckboost enable for Unreg #1
 fprintf(PORT1,"******Unreg #2 ON *********\n\r");
 RC5 = 1; //Buckboost enable for Unreg #2
 delayloop(10);
 RC5 = 0; //Buckboost enable for Unreg #2  
 fprintf(PORT1,"******Unreg #2 OFF *********\n\r");
 
//! write_eeprom(check_memory,8);
//! check=8;
//! write_eeprom(memory,5);
//! unreg_flag=5; 
      

}

void unreg_off_forever(void){

 RC5 = 0; //Buckboost enable for Unreg #2  
 fprintf(PORT1,"******Unreg #2 OFF FOREVER *********\n\r");

}

void normal_mode(void)
{

 RD6 = 1; // Switch enable for COM PIC
 RD7 = 1; // Switch enable for Main PIC
 
 RC4 = 1; // Buckboost enable for 3V3 #1 
 RD1 = 1; // Switch enale for 3V3#1
 
 RD3 = 1; // Buckboost enable for 3V3 #2
 RD0 = 1; // Switch enable for 3V3 #2
  
 RC2 = 1; //Buckboost enable for Unreg #1
 
 RC5 = 1; //Buckboost enable for Unreg #2
 
}

void reset_mode(void)
{
 fprintf(PORT1,"******Reset mode ON *********\n\r"); 
 RD6 = 0; // Switch disable for COM PIC
 RD7 = 0; // Switch disable for Main PIC
 RD1 = 0; // Switch disable  for 3V3#1
 RD0 = 0; // Switch disable for 3V3 #2
 RC2 = 0; //Buckboost disable for Unreg #1
 fprintf(PORT1,"******OFF *********\n\r"); 
 delay_ms(1000);
 fprintf(PORT1,"******ON *********\n\r"); 
 RD6 = 1; // Switch enable for COM PIC
 RD7 = 1; // Switch enable for Main PIC
 
 RC4 = 1; // Buckboost enable for 3V3 #1 
 RD1 = 1; // Switch enale for 3V3#1
 
 RD3 = 1; // Buckboost enable for 3V3 #2
 RD0 = 1; // Switch enable for 3V3 #2
  
 RC2 = 1; //Buckboost enable for Unreg #1
 
 RC5 = 0; //Buckboost enable for Unreg #2
 
}


