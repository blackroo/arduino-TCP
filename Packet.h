#ifndef PACKET_H
#define PACKET_H

#pragma once
#include <cstring>	//memset함수
#include <Arduino.h>

enum location
{
    my_room=0x11,
};

enum packet_type
{
    request = 0x21,
    response = 0x22,
};

enum function_type
{
    connect = 0x21,
    light_switch,
    senser,
};

class Packet
{
public:
    Packet();
    ~Packet();
    void init_packet(char buffer[]);

private:

};

#endif