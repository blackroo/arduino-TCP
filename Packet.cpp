#include "Packet.h"

Packet::Packet()
{

}

Packet::~Packet()
{

}

void Packet::init_packet()
{
    index=0;
    check_sum=0;

    memset(send_data,0,PACKSIZE);
    send_data[index]=socket_client;
    index++;
    send_data[index]=init_val;
    index++;
    send_data[index]=my_room;
    index++;

    this->checksum(send_data);


    packet_print("init_packet",send_data,index);
    

}

int Packet::init_packet_response()
{
    index=0;
    check_sum=0;

    memset(compare_data,0,PACKSIZE);    

    compare_data[index]=socket_server;
    index++;
    compare_data[index]=init_val;
    index++;
    compare_data[index]=my_room;
    index++;

    this->checksum(compare_data);

    //packet_print("init compare",compare_data,strlen(compare_data));
    packet_print("init recv",recv_data,strlen(recv_data));

    if(strcmp(compare_data,recv_data))
    {
        return -1;
    }

    return 0;
}


void Packet:: packet_print(char * name, char data[],int index)
{
    int i=0;
    char buf[4] = {0x00,};


    Serial.println(name);
        for(i=0; i<index; i++){
            sprintf(buf,"%x",data[i]);

            Serial.print(buf);
            Serial.print(" ");
        }
    Serial.println();
}

void Packet::checksum(char data[])
{
    int i=0;
    //checksum
    while(i<index){
		check_sum=check_sum^data[i];
		i+=1;     
	}
    data[index]=check_sum;
    index++;
}