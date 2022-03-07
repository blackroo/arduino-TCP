#include "Sensor.h"

Sensor::Sensor()
{

}

Sensor::~Sensor()
{

}

float Sensor::Dust_sensor()
{
        
    digitalWrite(ledP,LOW); // power on the LED  
    delayMicroseconds(280);  
    voMeasured = analogRead(dustPin); // read the dust value  
    delayMicroseconds(40);  
    digitalWrite(ledP,HIGH); // turn the LED off  
    delayMicroseconds(9680);  
    // 0 - 5V mapped to 0 - 1023 integer values
    Serial.println(voMeasured);
    calcVoltage = (0.17 * (voMeasured*(5.0/1024)) - 0.1) *1000;
    calcVoltage+=95;
    Serial.println(calcVoltage);  
    smoothDensity = calcVoltage * 0.10 + smoothDensity * 0.90;  

    Serial.println(smoothDensity);
    Serial.println("-------------");
    return smoothDensity; 
}