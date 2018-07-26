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
        gpio_set_value(SDATAE, HIGH);
        gpio_set_value(SREADE, HIGH);
        gpio_set_value(SCLK, HIGH);
		usleep(2000000);         // on for 2s
		cout << "Setting the LED off" << endl;
        gpio_set_value(CE, LOW);
        gpio_set_value(SLE, LOW);
        gpio_set_value(SDATAE, LOW);
        gpio_set_value(SREADE, LOW);
        gpio_set_value(SCLK, LOW);
		usleep(2000000);         // off for 2s

	}
	gpio_unexport(CE);     // unexport the LED
	gpio_unexport(SDATAE);
	gpio_unexport(SREADE);
	gpio_unexport(SLE);
	gpio_unexport(SCLK);
	cout << "Finished Testing the GPIO Pins" << endl;
	
return 0;
}
