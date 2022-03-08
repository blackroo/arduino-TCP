#ifndef SENSOR_H
#define SENSOR_H

#pragma once
#include<Arduino.h>



#define dustPin A0
#define ledP 5  //3번포트
#define vol_setting 1.05


class Sensor
{
protected: 
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