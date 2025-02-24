#ifndef PZEMMONITOR_H
#define PZEMMONITOR_H

#include <Arduino.h>
#include <PZEM004Tv30.h>
#include <Wire.h>
#include <SDHelper.h>
#include <RTClib.h>

class PZEMMonitor {
public:
    PZEMMonitor(HardwareSerial &serial, uint8_t txPin, uint8_t rxPin);
    void begin();                            
    void update();                        
    void printData();
    bool reset();                    
    bool PZEM_SD(String currentDate, String currentTime);

    float getVoltage();                  
    float getCurrent();                  
    float getPower();                      
    float getEnergy();                   
    float getFrequency();                 
    float getPowerFactor();                
    float getApparentPower();                
    float getReactivePower();          


private:
    RTC_DS3231 rtc;
    PZEM004Tv30 pzem;                       
    float voltage, current, power, energy;
    float frequency, powerFactor, apparentPower, reactivePower;
    
    float zeroIfNan(float value);            
};

#endif
