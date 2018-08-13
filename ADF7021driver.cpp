#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "SimpleGPIO.h"

using namespace std;

//definition 
//define full verbose 
#define vv

unsigned int CE		= 48;//P9_15
unsigned int SLE 	= 69;
unsigned int SDATA 	= 44;
unsigned int SREAD 	= 66;
unsigned int SCLK 	= 68;
//unsigned int MUXOUT = 13;

//variables
bool isOn;
bool txMode;
unsigned int db[32]; //32 element long
unsigned int revisionCode;
unsigned int productCode;
unsigned long controlWord;
unsigned char iterationTime;

//set
unsigned int T = 24000; //time period of register clock in us
unsigned int i;

//-------------------
//Algorithm

void powerUp(){
	gpio_set_value(CE, HIGH);//CE = 1
	usleep(100000); // 100 mS. 
	isOn = true;
	cout <<"on"<< endl;
}

void powerDown(){
	gpio_set_value(CE, LOW);//CE = 0
	isOn = false;
	cout << "off"<< endl;
}
void Initialize(){
	//turn on the ADF7021
	if(!isOn){
		powerUp();
		
	}

	//necessary reg operation
	//activate Rx mode
}

void regClock(){
	gpio_set_value(SCLK, LOW);
	usleep(T/2); //generate low half of the clk
	gpio_set_value(SCLK, HIGH); //generate high part of clk
	usleep(T/4); //but not in full

}
void clearDB(){
	cout << "clear db" <<endl;
	for(i = 0; i<32; i++){
		db[i] = 0;
	}
	//Alternate code
	//memset(db, 0, sizeof(db));
}

void readReg(){
	cout << "read reg" << endl;
	clearDB();
	gpio_set_value(SLE, HIGH);
	for(i = 17; i>=0; i--)
	{
		regClock();
		gpio_get_value(SREAD, &db[i]);
	}
	usleep(T/4);
	//SLE = 0;
	gpio_set_value(SLE, LOW);
}
void sendReg()
{
	//make sure everything is on
	if(!isOn){
		powerUp();
	}
	//MUXOUT must be HIGH for Programming to begin
	//while(gpio_get_value(MUXOUT) == LOW))
	//{
		//wait
	//}
	//Programming can now begin
	gpio_set_value(SLE, LOW);//SLE = 0;
	for(i = 31; i>=0; i--){
		gpio_set_value_2(SDATA, db[i]);
		regClock();
	}
	usleep(40000); //40 mS
}
void readSiliconRevision(){
	cout << "readSiliconRevision" << endl;
	//make sure everything is on
	if(!isOn){
		powerUp();
	}
	//set reg value
	clearDB();
	db[8] = 1;
	db[7] = 1;
	db[6] = 1;
	db[5] = 1;
	db[4] = 1;
	db[3] = 0;
	db[2] = 1;
	db[1] = 1;
	db[0] = 1;
	//ask for Revision code
	gpio_set_value(SLE, LOW);//SLE = 0;
	for(i = 8; i>=0; i--){
		gpio_set_value_2(SDATA, db[i]);
		regClock();
	}
	usleep(40000); //40 mS
	//read the Revision code
	readReg();
	
	//calculate the value
	revisionCode = 				8*db[4]+	4*db[3]+	2*db[2]+	db[1]		;
	productCode = 	(100*(		8*db[16]+	4*db[15]+	2*db[14]+	db[13])) 	+
					(10*(		8*db[12]+	4*db[11]+	2*db[10]+	db[9])) 	+
					(1*	(		8*db[8]+	4*db[7]+	2*db[6]+	db[5]))		;
	//show the user the value
	cout <<"Revision code: "<< std::hex << "0x" << revisionCode << "     " << std::dec << revisionCode << endl;
	cout <<"Product code : "<< std::hex << "0x" << productCode  << "   " << std::dec << productCode << endl;
}
void setReg(unsigned long word)
{
	//make sure everything is on
	if(!isOn){
		powerUp();
	}
	//make sure no residual value
	clearDB();
	//load value 
	for (i=0; word> 0; i++)
    {
        db[i] = word % 2;
        word = word / 2;
    }
	//set value
	sendReg();
	usleep(1000); //1 mS
}

void setReg0()
{
	setReg(0x82C1B200);
	usleep(100); //100 uS
}
void setReg1()
{
	setReg(0x479021);
	usleep(1000); //1 mS
}
void setReg2()
{
	setReg(0x22081B02);
	usleep(1000000); //1 S
}
void setReg3()
{
	setReg(0x33133663);
}
void setReg7()
{
	setReg(0x1F7);
}
void gpio_init()
{
	gpio_export(CE);
	gpio_export(SLE);
	gpio_export(SDATA);
	gpio_export(SREAD);
	gpio_export(SCLK);
	//gpio_export(MUXOUT);
	
	gpio_set_dir(CE, OUTPUT_PIN);
	gpio_set_dir(SLE, OUTPUT_PIN); 
	gpio_set_dir(SDATA, OUTPUT_PIN);  
	gpio_set_dir(SCLK, OUTPUT_PIN);   
	gpio_set_dir(SREAD, INPUT_PIN);   
	//gpio_set_dir(MUXOUT, INPUT_PIN);
}

void gpio_release()
{
	//unexport pins
	gpio_unexport(CE);     // unexport the LED
	gpio_unexport(SDATA);
	gpio_unexport(SREAD);
	gpio_unexport(SLE);
	gpio_unexport(SCLK);
	//gpio_unexport(MUXOUT);
}

void rx_mode()
{
	// 1 3 6? 5 11? 12? 0 4 10?
	
	//0
	setReg(0x8AC1B200);
}

void tx_mode() 
{
	//1 3 0 2
	setReg1();
	setReg3();
	setReg0();
	setReg2();

}
int main(){
	//pin direction and initial GPIO level
/*	//CE
	system("config-pin p9.15 gpio_pd");
	system("config-pin p9.15 out");
	system("config-pin -q p9.15");
	//SLE
	system("config-pin p8.09 gpio_pd");
	system("config-pin p8.09 out");
	system("config-pin -q p8.09");
	//SDATA
	system("config-pin p8.12 gpio_pd");
	system("config-pin p8.12 out");
	system("config-pin -q p8.12");
	//SREAD
	system("config-pin p8.07 gpio_pd");
	system("config-pin p8.07 in");
	system("config-pin -q p8.07");
	//SCLK
	system("config-pin p8.10 gpio_pd");
	system("config-pin p8.10 out");
	system("config-pin -q p8.10");
*/
	gpio_export(CE);
	gpio_export(SLE);
	gpio_export(SDATA);
	gpio_export(SREAD);
	gpio_export(SCLK);
	//gpio_export(MUXOUT);
	
	gpio_set_dir(CE, OUTPUT_PIN);
	gpio_set_dir(SLE, OUTPUT_PIN); 
	gpio_set_dir(SDATA, OUTPUT_PIN);   // The LED is an output
	gpio_set_dir(SCLK, OUTPUT_PIN);   // The LED is an output
	gpio_set_dir(SREAD, INPUT_PIN);   // The LED is an output
	//gpio_set_dir(MUXOUT, INPUT_PIN);
	//or
	//gpio_init();

	//do something
	setReg1();
	setReg3();
	setReg0();
	setReg2();
	readSiliconRevision();
	//power down
	powerDown();
	//unexport pins
	gpio_unexport(CE);     // unexport the LED
	gpio_unexport(SDATA);
	gpio_unexport(SREAD);
	gpio_unexport(SLE);
	gpio_unexport(SCLK);
	//gpio_unexport(MUXOUT);
	//or
	//gpio_release();

	cout << "All done" << endl;
	
	//return
	return 0;
}