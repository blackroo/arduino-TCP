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
	int send_timer = 170 ;
	int recv_fail = 0;
	int recv_try=0;
	char buffer[128] = {0x00,};
	char data[128] = {0x00,};

	while (!client.connect(host, port)) {
		Serial.println("connection failed");
		delay(5000);
		return ;
  	}

  // This will send a string to the server
	Serial.println("sending data to server");
	if (client.connected()) {
		
		packet.init_packet();
		client.print(packet.send_data);

		while(recv_try<=3)
		{
			if(client.available() != 0){

				Serial.println("[init] receiving from remote server");
				client.read(packet.recv_data,PACKSIZE);
				

				if(packet.init_packet_response()==0)
				{
					recv_try=0;
					break;
				}
			}
			recv_try ++;
			if(recv_try>=3){
				Serial.println("[init] error reconnect");
				return;
			}

			delay(1000);
		}
		// client.print("hello from ESP8266");
	}

  // wait for data to be available
  	while(1)
	{
		
		if(client.available() != 0){

			Serial.println("[period] receiving from remote server");
			
			while (client.available()) {
				memset(packet.recv_data,0,PACKSIZE);
				client.read(packet.recv_data,PACKSIZE);
				//packet.packet_print("recv_data",packet.recv_data,strlen(packet.recv_data));
				if(packet.period_packet_response()==0)
				{
					recv_fail=0;
				}
			}
		}


		sensor.Dust_sensor();
		sensor.dht_sensor();

		if(send_timer>=180)
		{
			packet.period_packet(sensor.smoothDensity,sensor.temperature,sensor.humidity);
			client.print(packet.send_data);
			//recv_fail++;
			send_timer=0;
		}


		if(!client.connected() || recv_fail>=4)
		{
			client.stop();
			return ;
		}

		send_timer++;
		delay(1000);
  	}
  

}