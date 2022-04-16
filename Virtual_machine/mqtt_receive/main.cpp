


//////////////////////////////////////  3.3.2022 //////////////////////////////
///
///	g++ main.cpp mqtt_receiv.cpp -std=c++0x -pthread -lmosquitto -lmosquittopp -ljsoncpp
///
///////////////////////////////////////////////////////////////////////////////

#include <signal.h>
#include <sys/time.h>
#include <stdio.h>
#include <cstring>
#include <string>
//#include <string.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <unistd.h>
//#include "traffic.h"
#include "interface.h"

using namespace std;


#include "mqtt_receiv.h"

///////////////////////////////////////// conficuration ///////////////////////

#include "mqtt.h"

//////////////////////////////////// main /////////////////


int main(int argc, char *argv[])
{

		
	printf ("Raspberry Pi MQTT receive demo\n") ;

	printf ("****   Subscribed to listen MQTT messages \n");
	mqtt mqtt_obj(host_addr, port_number);			// start mqtt 
	usleep(1000);

	std::string input;
	//build_road();

	frame();
	while(1) {
	  printf("\33[30:30m");
	  printf("\033[48;5;84m");
	//printf("\033c");
	   //frame();
	//printf("\33[10;3H");
	//printf("Enter your command:                                ");
	//printf("\33[10;24H");
	//fflush(stdout);
	   std::cin >> input;
	   printf("\33[35;41H");

	if ( mqtt_obj.send_message(input) ) {
//	   printf("Sent. ");
	}

//	printf("%s",input.c_str());
	};						// keep mqtt send theread running
						
	return 0;
}
