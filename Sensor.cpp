#include "Sensor.h"

Sensor::Sensor()
{
    pinMode(ledP,OUTPUT);

}

Sensor::~Sensor()
{

}

float Sensor::Dust_sensor()
{
    float dustDensity = 0;
    digitalWrite(ledP,LOW); // power on the LED  
    delayMicroseconds(280);  
    voMeasured = analogRead(dustPin); // read the dust value  
    delayMicroseconds(40);  
    digitalWrite(ledP,HIGH); // turn the LED off  
    delayMicroseconds(9680);  
    // 0 - 5V mapped to 0 - 1023 integer values
    Serial.println(voMeasured);
    calcVoltage = voMeasured*(5.0/1024);
    //dustDensity = (0.17 * calcVoltage - 0.1) *1000;
    dustDensity = (calcVoltage - vol_setting)/0.005;
    Serial.println(dustDensity);


    if(smoothDensity>0 && smoothDensity<200)
        smoothDensity = dustDensity * 0.01 + smoothDensity * 0.99;  
    else
        smoothDensity = 20.0;

    Serial.println(smoothDensity);
    Serial.println("-------------");
    return smoothDensity; 
}