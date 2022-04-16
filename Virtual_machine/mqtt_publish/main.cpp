


//////////////////////////////////////  3.3.2022 //////////////////////////////
///
///	g++ main.cpp mqtt_receiv.cpp -std=c++0x -pthread -lmosquitto -lmosquittopp -ljsoncpp
///
///////////////////////////////////////////////////////////////////////////////

#include <signal.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <unistd.h>


using namespace std;


#include "mqtt_receiv.h"

///////////////////////////////////////// conficuration ///////////////////////

#include "mqtt.h"

//////////////////////////////////// main /////////////////




int main(int argc, char *argv[])
{

	
	printf ("Sending a message") ;


	mqtt mqtt_obj(host_addr, port_number);			// start mqtt 

	std::string str="Test";
	mqtt_obj.send_message(str);
	mqtt_obj.send_message("Testing");
						
	return 0;
}
