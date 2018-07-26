#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <unistd.h>\

#include "SimpleGPIO.h"

using namespace std;

unsigned int LEDGPIO = 44;   // GPIO0_0 = (1x32) + 28 = 48


int main(int argc, char *argv[]){
	cout << "Test" << endl;
	system("config-pin p8.12 gpio_pd");
	system("config-pin p8.12 out");
	// Flash the LED 5 times
	for(int i=0; i<30; i++){
		cout << "Setting the LED on" << endl;
        gpio_set_value(LEDGPIO, HIGH);
		usleep(500000);         // on for 500ms
		cout << "Setting the LED off" << endl;
        gpio_set_value(LEDGPIO, LOW);
		usleep(500000);         // off for 500ms

	}
return 0;
}
