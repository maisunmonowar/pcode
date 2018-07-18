#include <iostream>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

int main(int argc, char *argv[]){
	cout <<"Test"<<endl;
	system("config-pin -l p9.15");
	system("config-pin p9.15 in");
	system("config-pin p9.15 gpio_pu");
	usleep(1000000);
	system("config-pin -q p9.15");
	system("config-pin p9.15 gpio_pd");
	usleep(1000000);
	system("config-pin -q p9.15");
	usleep(200000);
	return 0;
}
