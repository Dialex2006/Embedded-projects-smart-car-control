
///////////////////////////  3.3.2022  KN /////////////////////////////

#include <cstdio>
#include <cstring>
#include <string>
#include <functional>     	// c++11
#include <unistd.h>
#include <iostream>        	// due to: cout

#include <fstream>
#include <time.h>


#include "mqtt.h"

#include "mqtt_receiv.h"
#include "parser.h"
#include "traffic.h"
//#include "interface.h"
using namespace std;

#include <jsoncpp/json/json.h>


//////////////////////////////////////////////////////////////////////////
//////////
//////////    MQTT
//////////
/////////////////////////////////////////////////////////////////////////

mqtt::mqtt(const char *host, int port)						// costructor
{
	
	int keepalive = 600;

//	printf("****   MQTT start connect ****** \n");

	connect(host, port, (int) keepalive);			// connect to mqtt broker

	loop_start();						// stay on mqtt loop
};


////////// ON CONNECT ///////////////////////////////////////////////////

void mqtt::on_connect(int rc)							// on connect callback
{
//	printf("****   MQTT Connected with code= %d  *****\n", rc);
	if(rc == 0)
	{
					// Only attempt to subscribe on a successful connect. 

		subscribe(NULL, in_topic);

//		printf("****   MQTT subscription to topic = ");printf(in_topic);
//		printf("    ****\n");
	}
}

//////////////////////////  ON SUBSCRIBE ///////////////////////////////////////

void mqtt::on_subscribe(int mid, int qos_count, const int *granted_qos)		// on subcribe callback
{

        printf("\33[4;1H");
	fflush(stdout);
	printf("****   MQTT Topic subscription succeeded.   ****\n");
        printf("\33[5;1H");

}


//////////////////////////// Message received //////////////////////////////////

void mqtt::on_message(const struct mosquitto_message *message)			// on message callback

{
	std::string mqtt_message;					// mqtt message string
	int lidar, compass;


        //system("clear");
	//printf("\033c");
	//build_road();
	printf ("\033[0m");
        printf("\33[45;1H");
	printf("\33[2K\r");
        printf("\33[46;1H");
	printf("\33[2K\r");
	printf("\33[47;1H");
	printf("\33[2K\r");
        printf("\33[48;1H");
	printf("\33[2K\r");
        printf("\33[49;1H");
	printf("\33[2K\r");
        printf("\33[45;1H");

        printf("\n ===================  Message received  ================================ \n"); 

	mqtt_message = (char*) message->payload;

	printf("Message is = %s\n",mqtt_message.c_str()) ;

	int mode = parse(mqtt_message.c_str(), lidar, compass);

//	printf("\33[16,10H");
	printf("Value:       ");
//	printf("\33[20,15H");
	printf("%d",mode);
	//printf("\33[10;3H");
	fflush(stdout);

	printf("\033[35;41H");
	printf("\033[5;0m");
	printf("\033[48;5;84m");
	printf("\033[30;30m");


	printf("\033[23;17H");
	printf("                       ");
	printf("\033[23;17H");
	printf("%d",lidar);
	printf(" cm");

	printf("\033[23;67H");
	printf("                       ");
	printf("\033[23;67H");
	printf("%d",compass);
	printf("\u00B0");

	printf("\033[35;41H");

//	printf("Enter your command: ");
//	printf("\33[10;24H");
//	frame();
	fflush(stdout);





//	printf("The mode is %d\n",mode);


/*
	if (mode != 2 && mode != 4)
	{
		tfl1(mode);
		tfl2(4-mode);
        	printf("\33[20,20H");
		printf("Value is ");

	}
	else {
		if (mode == 2) {
			tfl1(2);
			tfl2(3);
		}
		else {
			tfl1(3);
			tfl2(2);

		}
	}
	
*/


}  ////////////////////////////         end message received ////////////////////////



bool mqtt::send_message(std::string message)
{
	message = "{" + message + "}";
	int ret = publish(NULL,out_topic,message.length(),message.c_str(),1,false);
	printf ("\033[0m");
	printf("\33[7;0H");
        printf("===================  Message sent  ================================ \n"); 
	printf("Result = %d\n",ret);
	printf("Topic = %s\n",out_topic);
	printf("Message =                                ");
	printf("\33[10;11H");
	printf("%s\n",message.c_str());

	printf("\33[35;41H");
	printf("\033[48;5;84m");
	printf("\033[30;30m");
	printf("                               ");

	printf("\033[37;47H");
	
	printf("%s",message.c_str());
	printf("     ");
	printf("\033[35;41H");

	return (ret == MOSQ_ERR_SUCCESS);

//return 0;

}

