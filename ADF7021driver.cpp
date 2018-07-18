#include <iostream>
 #include <stdio.h>
 #include <unistd.h>
 using namespace std;

//definition 

CE = P9_15
SLE
SDATA
SREAD
SCLK

//variables
boolean isOn;
boolean txMode;
array db; //32 element long
//set
byte T = 24; //time period of register clock in ms

//-------------------
//Algorithm

powerUp(){
	CE = 1;
	wait(100); // in mS. 
	isOn = true;
}

powerDown(){
	CE = 0;
	isOn = false;
}
Initialize(){
	//turn on the ADF7021
	if(!isOn){
		pwerUp();
	}

	//necessary reg operation
}

regClock(){
	SCLK = 0;
	wait(T/2); //generate low half of the clk
	SCLK = 1; //generate high part of clk
	wait(T/4); //but not in full

}
clearDB(){
	for(i = 0; i<32; i++){
		db[i] = 0;
	}
}
readReg(){
	clearDB();
	SLE = 1;
	for(i = 17; i>=0; i--){//not sure how many bits are supposed to come in
		regClock();
		db[i] = SREAD;
	}
	SLE = 0;
}
readSiliconRevision(){
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
		SDATA = db[i];
		regClock();
	}
	wait(40); //in mS
	//read the Revision code
	readReg();
	
	//calculate the value
	revisionCode = ((2^3)*db[4])+((2^2)*db[3])+((2^1)*db[2])+((2^0)*db[1])
	productCode = 	(100*	(((2^3)*db[16])+((2^2)*db[15])+((2^1)*db[14])+((2^0)*db[13]))) +
					(10*	(((2^3)*db[12])+((2^2)*db[11])+((2^1)*db[10])+((2^0)*db[09]))) +
					(1*		(((2^3)*db[08])+((2^2)*db[07])+((2^1)*db[06])+((2^0)*db[05])))
	//show the user the value
	print revisionCode
	print productCode				
}

int main(){
	readSiliconRevision();
}