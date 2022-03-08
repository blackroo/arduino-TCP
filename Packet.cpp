#include "Packet.h"

Packet::Packet()
{

}

Packet::~Packet()
{

}

void Packet::init_packet(char buffer[])
{
    int index=0;
    int i=0, check_sum=0;

    memset(buffer,0,sizeof(buffer));
    buffer[index]=socket_client;
    index++;
    buffer[index]=init_val;
    index++;
    buffer[index]=my_room;
    index++;

    //checksum
    while(i<index){
		check_sum=check_sum^buffer[i];
		i+=1;     
	}

    buffer[index]=check_sum;
    index++;

    packet_print("init_packet",buffer,index);
    

}

int Packet::init_packet_response(char buffer[])
{
    int index=0;
    int i=0, check_sum=0;
    return 0;
}


void packet_print(char * name,char buffer[],int index)
{
    int i=0;
    char buf[4] = {0x00,};


    Serial.println(name);
        for(i=0; i<index; i++){
            sprintf(buf,"%x",buffer[i]);

            Serial.print(buf);
            Serial.print(" ");
        }
    Serial.println();
}