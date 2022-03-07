/*
    This sketch establishes a TCP connection to a "quote of the day" service.
    It sends a "hello" message, and then prints received data.
*/

#include <ESP8266WiFi.h>
#include "Packet.h"
#include "Sensor.h"

#ifndef STASSID
#define STASSID "KT_GiGA_2G_Wave2_05F8"
#define STAPSK  "eza3kz1284"
#endif

const char* ssid     = STASSID;
const char* password = STAPSK;

const char* host = "172.30.1.18";
const uint16_t port = 5000;

WiFiClient client;
Packet packet;
Sensor sensor;


void setup() {
	Serial.begin(115200);

	// We start by connecting to a WiFi network

	Serial.println();
	Serial.println();
	Serial.print("Connecting to ");
	Serial.println(ssid);

	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}

	Serial.println("");
	Serial.println("WiFi connected");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());


	Serial.print("connecting to ");
	Serial.print(host);
	Serial.print(':');
	Serial.println(port);

	
}

void loop() {
	char buffer[128] = {0x00,};
	char data[128] = {0x00,};
	int i=0;

	while (!client.connect(host, port)) {
		Serial.println("connection failed");
		delay(5000);
		return ;
  	}

  // This will send a string to the server
	Serial.println("sending data to server");
	if (client.connected()) {
		
		packet.init_packet(buffer);
		client.print(buffer);
		sensor.smoothDensity=0;
		
		// client.print("hello from ESP8266");
	}

  // wait for data to be available
  	while(1)
	{
		// while (client.available() == 0) {
		
		// }
		if(client.available() != 0){

			Serial.println("receiving from remote server");
			
			while (client.available()) {
				client.read(data,128);
				Serial.println(data);
				if(!strcmp(data,"Dust sensor"))
				{
					client.print(sensor.smoothDensity);
					Serial.print("Send data : ");
					Serial.println(sensor.smoothDensity);
				}
				memset(data,0,128);
			}

			
		}

		if(i>=200){
			sensor.Dust_sensor();
			i=0;
		}


		if(!client.connected())
		{
			client.stop();
			return ;
		}
		i++;
		delay(10);
  	}
  

}