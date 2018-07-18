#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "SimpleGPIO.h"

using namespace std;

//definition 

unsigned int CE		= 48;//P9_15
unsigned int SLE 	= 69;
unsigned int SDATA 	= 44;
unsigned int SREAD 	= 66;
unsigned int SCLK 	= 68;

//variables
bool isOn;
bool txMode;
unsigned int db[32]; //32 element long
//set
unsigned int T = 24000; //time period of register clock in us

//-------------------
//Algorithm

void powerUp(){
	CE = 1;
	uwait(100000); // in mS. 
	isOn = true;
}

void powerDown(){
	CE = 0;
	isOn = false;
}
void Initialize(){
	//turn on the ADF7021
	if(!isOn){
		powerUp();
	}

	//necessary reg operation
}

void regClock(){
	gpio_set_value(SCLK, LOW);
	uwait(T/2); //generate low half of the clk
	gpio_set_value(SCLK, HIGH); //generate high part of clk
	uwait(T/4); //but not in full

}
void clearDB(){
	for(i = 0; i<32; i++){
		db[i] = 0;
	}
}
void readReg(){
	clearDB();
	gpio_set_value(SLE, HIGH);
	for(i = 17; i>=0; i--){//not sure how many bits are supposed to come in
		regClock();
		gpio_get_value(SREAD, &db[i]);
	}
	SLE = 0;
}
void readSiliconRevision(){
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
	SLE = 0;
	for(i = 8; i>=0; i--){
		gpio_set_value(SDATA, db[i]);
		regClock();
	}
	uwait(40000); //in mS
	//read the Revision code
	readReg();
	
	//calculate the value
	unsigned int revisionCode = ((2^3)*db[4])+((2^2)*db[3])+((2^1)*db[2])+((2^0)*db[1])
	unsigned int productCode = 	(100*	(((2^3)*db[16])+((2^2)*db[15])+((2^1)*db[14])+((2^0)*db[13]))) +
	


					(10*	(((2^3)*db[12])+((2^2)*db[11])+((2^1)*db[10])+((2^0)*db[9]))) +
					(1*		(((2^3)*db[8])+((2^2)*db[7])+((2^1)*db[6])+((2^0)*db[5])))
	//show the user the value
	cout <<"Revision code: "<< std::hex << revisionCode << endl;
	cout <<"Product code : "<< std::hex << productCode << endl;
}

int main(){
	//pin direction and initial GPIO level
	//CE
	system("config-pin p9.15 gpio_pd");
	system("config-pin p9.15 out");
	//SLE
	system("config-pin p8.09 gpio_pd");
	system("config-pin p8.09 out");
	//SDATA
	system("config-pin p8.12 gpio_pd");
	system("config-pin p8.12 out");
	//SREAD
	system("config-pin p8.07 gpio_pd");
	system("config-pin p8.07 in");
	//SCLK
	system("config-pin p8.10 gpio_pd");
	system("config-pin p8.10 out");
	readSiliconRevision();
	return 0;
}