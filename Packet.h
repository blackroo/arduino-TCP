#ifndef PACKET_H
#define PACKET_H

#pragma once
#include <cstring>	//memset함수
#include <Arduino.h>


#define PACKSIZE 128

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




class Packet
{

public:
    char send_data[PACKSIZE] = {0x00,};
    char recv_data[PACKSIZE] = {0x00,};
    char compare_data[PACKSIZE] = {0x00,};
    int index = 0;
    int check_sum=0;
    
    Packet();
    ~Packet();
    void init_packet();
    int init_packet_response();
    void packet_print(char * name, char data[], int index);
    void checksum(char data[]);

private:

};

#endif