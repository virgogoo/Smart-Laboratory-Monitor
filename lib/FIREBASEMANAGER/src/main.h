#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>

typedef struct {
    String id; 
    String ip;
    float current;         // 4 bytes
    float energy;          // 4 bytes
    float power_per_day;
    float temperature;     // 4 bytes
    float humidity;  
    float power;      // 4 bytes
    uint16_t LPG;          // 2 bytes
    uint16_t CO;           // 2 bytes
    uint16_t smoke;        // 2 bytes
            // 2 bytes
} SensorData;


#endif // MAIN_H
