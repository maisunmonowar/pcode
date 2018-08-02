#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <unistd.h>

#include "SimpleGPIO.h"

using namespace std;

unsigned int CE		= 48;//P9_15
unsigned int SLE 	= 69;
unsigned int SDATA 	= 44;
unsigned int SREAD 	= 66;
unsigned int SCLK 	= 68;
unsigned int revisionCode;
unsigned int productCode;
unsigned int db[32]; //32 element long
int i;

int main(int argc, char *argv[]){
	cout << "Test" << endl;

	gpio_export(CE);    // The LED
	usleep(250000);         // off for 250ms
	gpio_set_dir(CE, OUTPUT_PIN);   // The LED is an output
	usleep(250000);         // off for 250ms
	
	gpio_export(SLE);    // The LED
	usleep(250000);         // off for 250ms
	gpio_set_dir(SLE, OUTPUT_PIN);   // The LED is an output
	usleep(250000);         // off for 250ms
	
	gpio_export(SDATA);    // The LED
	usleep(250000);         // off for 250ms
	gpio_set_dir(SDATA, OUTPUT_PIN);   // The LED is an output
	usleep(250000);         // off for 250ms
	
	gpio_export(SREAD);    // The LED
	usleep(250000);         // off for 250ms
	gpio_set_dir(SREAD, OUTPUT_PIN);   // The LED is an output
	usleep(250000);         // off for 250ms

	gpio_export(SCLK);    // The LED
	usleep(250000);         // off for 250ms
	gpio_set_dir(SCLK, OUTPUT_PIN);   // The LED is an output
	usleep(250000);         // off for 250ms
	// Flash the LED 10 times
	for(int i=0; i<10; i++){

		cout << "Setting the LED on" << endl;
        gpio_set_value(CE, HIGH);
        gpio_set_value(SLE, HIGH);
        gpio_set_value(SDATA, HIGH);
        gpio_set_value(SREAD, HIGH);
        gpio_set_value(SCLK, HIGH);
		usleep(2000000);         // on for 2s
		cout << "Setting the LED off" << endl;
        gpio_set_value(CE, LOW);
        gpio_set_value(SLE, LOW);
        gpio_set_value(SDATA, LOW);
        gpio_set_value(SREAD, LOW);
        gpio_set_value(SCLK, LOW);
		usleep(2000000);         // off for 2s

	}
	gpio_unexport(CE);     // unexport the LED
	gpio_unexport(SDATA);
	gpio_unexport(SREAD);
	gpio_unexport(SLE);
	gpio_unexport(SCLK);
	cout << "Finished Testing the GPIO Pins" << endl;
	for(i = 0; i<32; i++){
		db[i] = 0;
	}
	db[2] = 1;
	db[16] = 1;
	db[12] = 1;
	db[7] = 1;
	revisionCode = (((2^3)*db[4])+((2^2)*db[3])+((2^1)*db[2])+((2^0)*db[1]))				;
	productCode = 	((100*	(((2^3)*db[16])+((2^2)*db[15])+((2^1)*db[14])+((2^0)*db[13]))) 	+
								(10*	(((2^3)*db[12])+((2^2)*db[11])+((2^1)*db[10])+((2^0)*db[9]))) 	+
								(1*		(((2^3)*db[8])+((2^2)*db[7])+((2^1)*db[6])+((2^0)*db[5]))))		;
	cout <<"Revision code: "<< std::hex << revisionCode << endl;
	cout <<"Product code : "<< std::hex << productCode << endl;
	return 0;
}
