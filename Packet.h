#ifndef PACKET_H
#define PACKET_H

#pragma once
#include <cstring>	//memset함수
#include <Arduino.h>


enum socket_type
{
    socket_client = 0x01,
    socket_server = 0x02,
};

enum location
{
    my_room=0x11,
};


enum function_type
{
    init_val = 0x20,
    senser = 0x21,
};

void packet_print(char * name,char buffer[],int index);


class Packet
{
public:
    Packet();
    ~Packet();
    void init_packet(char buffer[]);
    int init_packet_response(char buffer[]);

private:

};

#endif