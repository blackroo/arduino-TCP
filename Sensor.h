#ifndef SENSOR_H
#define SENSOR_H

#pragma once
#include<Arduino.h>

class Sensor
{
protected:
    int dustPin = A0;    
    int ledP = 2;   
    float voMeasured = 0;  
    float calcVoltage = 0;   
    

public:
    float smoothDensity = 0; 
    Sensor();
    ~Sensor();
    float Dust_sensor();

private:

};

#endif