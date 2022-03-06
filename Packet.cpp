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
    buffer[index]=0x01;
    index++;
    buffer[index]=request;
    index++;
    buffer[index]=connect;
    index++;
    buffer[index]=my_room;
    index++;

    //checksum
    while(i<index){
		check_sum=check_sum^buffer[i];
		i+=1;     
	}
    Serial.println(check_sum);
    buffer[index]=check_sum;
    index++;
}