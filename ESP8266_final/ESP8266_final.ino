/*

ESP Steering wheel example ref 1.2.2022 KN
Lidar reading
  
*/

// Import required libraries
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <Wire.h>
#include <PubSubClient.h>
#include "ArduinoJson.h"



#define PWMRANGE 255

// Update these with values suitable for your VM.
#define MQTT_ID  "ESP8266_2022_31"
const char* mqtt_server = "172.16.7.101";
#define intopic  "esp_in"
#define outtopic  "esp_out"
#define led3 0
#define led1 5
#define led2 4
#define in_voltage 2

void connect(void);
int print_AD(void);
void setup_wifi(void);
void callback(char* topic, byte* payload, unsigned int length);



            //            network credentials


const char* ssid = "SOURCE";
const char* password = "Pelle!23";

//const char* ssid = "mokkula_925936";
//const char* password = "12345678";


bool    spiffsActive = false;

                                                                        // Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String from_mega="", from_mega2="";                                                    // lidar distance value in String format

int is;

char buf[40];                                                           //  Serial bus buffer   

String lidar="", compass="", lidar_published="", compass_published="";
bool send_callback = false;



WiFiClient espClient;
PubSubClient client(espClient);

DynamicJsonDocument doc(100);


 
void setup()
{
                                                                          // Serial port for transfer data with Mega
  Serial.begin(9600);
  
  Serial.println("");

  Serial.println("----------------");

  Serial.println("----------------");

                                                                          // Start file subsystem
  if (SPIFFS.begin()) {
      Serial.println("SPIFFS Active");
      Serial.println();
      spiffsActive = true;
  } else {
      Serial.println("Unable to activate SPIFFS");
  }



  setup_wifi();                               // init Wifi
  client.setServer(mqtt_server, 1883);        // set server IP and port number
  client.setCallback(callback);               // define receive callback
  
  connect();     


  
                                                                            // Connect to Wi-Fi
//  WiFi.begin(ssid, password);
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(1000);
//    Serial.println("Connecting to WiFi..");
//  }

                                                                            // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());
  

                                                                            // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            {
                request->send(SPIFFS, "/index.html", String(), false, processor);

 //             Serial.println(" HTML GET ");

                int paramsNr = request->params();

 //             Serial.println(" ------ ");
 //             Serial.print("Param qty: ");
 //             Serial.println(paramsNr);
      
                for (byte i=0;i<paramsNr;i++)
                    {

                        AsyncWebParameter* p = request->getParam(0);
 
//                      Serial.print("Param name: ");
//                      Serial.println(p->name());

                        if ((p->name())=="dist"){ Serial.print("Move:");Serial.println(p->value()); };
                        if ((p->name())=="dire"){ Serial.print("Turn:");Serial.println(p->value()); };
      
                   //   Serial.print("Param value: ");
                   //   Serial.println(p->value());
                    };                                                          //    end of for loop
                    
   
              });                                                              // server on END



                                                                              // Route to load style.css file
  server.on("/jquery-1.11.3.min.js", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/jquery-1.11.3.min.js", "text/javascript");

    Serial.println(" JS jquery GET ");
      
  });

                                                                                // Route to load style.css file
  server.on("/roundslider.min.js", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/roundslider.min.js", "text/javascript");

    Serial.println(" min JS GET ");
      
  });
  

  server.on("/compass.jpg", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/compass.jpg", "image/jpg");

    Serial.println(" JPG image ");
      
  });


  server.on("/compass.png", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/compass.png", "image/png");

    Serial.println(" PNG image ");
      
  });



  server.on("/background2.jpeg", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/background2.jpeg", "image/jpeg");

    Serial.println(" JPEG image ");
      
  });



  server.on("/needle.png", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/needle.png", "image/png");

    Serial.println(" PNG image ");
      
  });

  
                                                                                  // Route to load style.css file
  server.on("/roundslider.min.css", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/roundslider.min.css", "text/css");
    
    Serial.println(" min css GET ");
    
  });


                                                                                //  Method GET - query from MEGA to to web page tag is / from_MEGA
  server.on("/from_MEGA", HTTP_GET, [](AsyncWebServerRequest *request)
    {
      request->send_P(200, "text/plain", string_to_JS().c_str());               // return value to web page JS
      
    }); 


                                                                                  // Start server
  server.begin();




  pinMode(led1,OUTPUT);
  digitalWrite(led1,0);
  pinMode(led2,OUTPUT);
  digitalWrite(led2,0);
  pinMode(led3,OUTPUT);
  digitalWrite(led3,0);

}                                                                                 //  END OF setup



                                                                                  // reservation 
String processor(const String& var)
{  }




String string_to_JS()                                                             // funtion to be called with GET from_MEGA tag
  {
    return from_mega;
  }



 
void loop()
{

  if (!client.connected()) {  connect();  }  // reconnect if needed
  int counter = 1;
  client.loop();

  delay(1000);

  if ( ( abs(lidar.toInt()-lidar_published.toInt()) > 5 ) || (abs(compass.toInt()-compass_published.toInt()) > 5) ) {

        String msg="{\"LID\":"+lidar+",\"COM\":"+compass+"}";   
        client.publish(outtopic, msg.c_str());
        lidar_published = lidar;
        compass_published = compass;
  }

/*
  while(1)

    {
      client.loop();

      counter++;
      int sum=analogRead(A0); 
    
      Serial.print(" AD converter= ");  Serial.println(sum);


      if 
      char msg[50]="My Mqtt";
           //   012345678901234567890
           
      Serial.print("Publish message: "); Serial.println(msg);
          
      client.publish(outtopic, msg);
           
      delay(2000);
      
    }  ////         while end


*/
    




  
  if (Serial.available() > 0) 
    {
      serial_read();                                            // read string from Mega
      from_mega=buf;
      //Serial.println(from_mega);

//      Lid=123
//      Com=340



      String buf_tem(buf);
      int pos1 = buf_tem.indexOf("+");                              // parse mega string for check syntax in serial monitor
      int len =buf_tem.length();                                    // remember to ignore in final solution
     
        lidar=buf_tem.substring(0,pos1);
        compass = buf_tem.substring(pos1+1,len);

      from_mega = lidar + "+" + compass;
      //Serial.println(from_mega);



      //Sending data to Virtual Machine
      if (send_callback) {
        String msg="{\"LID\":"+lidar+",\"COM\":"+compass+"}";
        //Serial.print("Publish message: ");
        //Serial.println(msg);     
        client.publish(outtopic, msg.c_str());
        send_callback = false;
      }
      

    
     /*
      COM=buf_tem.substring(0,pos1);
      if (COM == "LID")
        VAL1 = buf_tem.substring(pos1+1,len);
      else if (COM == "COM")
        VAL2 = buf_tem.substring(pos1+1,len);

      from_mega = VAL1 + "+" + VAL2;
      Serial.println(from_mega);
      */
      
      //from_mega2 = VAL2;
                                                                        // print command and value   
      //Serial.print(" COM=<"); Serial.print(COM); Serial.println("> ");  // print command
      //Serial.print(" VAL=<"); Serial.print(VAL); Serial.println("> ");  // print value
     
       
    }  
}





void serial_read()                                    // read serial in string, save received characters to buff[]
{
  boolean done=0; 

  while (done==0)                                     // wait end of message LF
    {
        while(Serial.available() > 0)
        {
          char char_in = Serial.read();
        
          if(char_in>13)                              // is input char above CR
                {   
                 buf[is]=char_in;
                 is++;
                }
  
          if(char_in==10){                            // check if end of message  LF   
                    buf[is]=0;                        // end of string
                    is=0;
                    done=1;
                  }
    
        }                                            // end of while serial available  

        if(done==1) { done=0; break; }

  }                                                 // while END , End of message  LF
   
      // Serial.println(buf);
      
}                                                   // end of serial read





void setup_wifi() 
{

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) 
    {
      delay(500);
      Serial.print(".");
    }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());                       ////////   Print IP number
}///////////////////////////////////////////////////////////////   setup WIFI end




void callback(char* topic, byte* payload, unsigned int length) 
{
   
  //Serial.print("Message arrived :");
  char tp[30];
  snprintf(tp,length,"%s", payload);
  //Serial.println(tp);
  

   parse_msg(payload);  

   send_callback = true;
   


  
}


///////////////////////////////////////////////////////////////////  connect to MQTT broker  
void connect() {        
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(MQTT_ID)) {
      Serial.println("connected to MQTT broker");
      client.subscribe(intopic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}




void parse_msg(uint8_t *data)                                               // parse message
{
    Serial.println("Parsing start: ");
    
    DeserializationError error = deserializeJson(doc, data);                // parse json message
                                              
    if (error) {                                                            // Test if parsing succeeds.
                  Serial.print(F("deserializeJson() failed: "));
                  Serial.println(error.f_str());
                  return;
                }
                
    JsonObject root = doc.as<JsonObject>();                                 // 

    String com, val_str;                                                       // (JSON) name ( =command)
    double val;                                                             // (JSON) value

    for (JsonPair kv : root) 
      {
             com=(kv.key().c_str());
             val_str=kv.value().as<String>();
             val=kv.value().as<double>();
             if (com == "LED")
                change_light_state(com, val);
             
       }
       
    Serial.print(com);Serial.print(":");Serial.println(val_str);

                        

} // end parse message




void change_light_state(String com, double val) {
    if (val == 1) {
     digitalWrite(led1, 1);
     digitalWrite(led2, 0);
     digitalWrite(led3, 0);
    }
    else if (val == 2) {
     digitalWrite(led2, 1);
     digitalWrite(led1, 0);
     digitalWrite(led3, 0); 
    }
    else if (val == 3) {
      digitalWrite(led3, 1);
      digitalWrite(led1, 0);
      digitalWrite(led2, 0); 
    }
}
