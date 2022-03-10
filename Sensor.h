#ifndef SENSOR_H
#define SENSOR_H

#pragma once
#include<Arduino.h>
#include <DHT.h>


#define dustPin A0
#define ledP 5  //3번포트
#define vol_setting 0.6

#define DHTPIN 4        // SDA 핀의 설정 4번포트
#define DHTTYPE DHT22   // DHT22 (AM2302) 센서종류 설정



class Sensor
{
protected: 
    float voMeasured = 0;  
    float calcVoltage = 0;
    
    

public:
    float temperature = 0; 
    float humidity = 0;
    float smoothDensity = 0; 
    Sensor();
    ~Sensor();
    float Dust_sensor();
    void dht_sensor();

private:

};

#endif