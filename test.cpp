#include <stdio.h>
#include <iostream>
#include <string>
#include <unistd>
#include <stdlib.h>

#include "SimpleGPIO.h"

using namespace std;

unsigned int LEDGPIO = 48;   // GPIO0_0 = (1x32) + 28 = 48


int main(int argc, char *argv[]){
	cout << "Test" << endl;
	system("config-pin p9.15 gpio_pd");
	system("config-pin p9.15 out");
	// Flash the LED 5 times
	for(int i=0; i<10; i++){
		cout << "Setting the LED on" << endl;
        gpio_set_value(LEDGPIO, HIGH);
		sleep(500);         // on for 500ms
		cout << "Setting the LED off" << endl;
        gpio_set_value(LEDGPIO, LOW);
		sleep(500);         // off for 500ms
	}
	return 0;
}
