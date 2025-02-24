#ifndef MQ2_H
#define MQ2_H
#include <Arduino.h>

#define RL_VALUE (20)
#define RO_CLEAN_AIR_FACTOR (9.83)

#define CALIBRATION_SAMPLE_TIMES (50)
#define CALIBRATION_SAMPLE_INTERVAL (500)
#define READ_SAMPLE_INTERVAL (50)
#define READ_SAMPLE_TIMES (5)

#define GAS_LPG (0)
#define GAS_CO (1)
#define GAS_SMOKE (2)

#define MQ2_PIN 34
class MQ2 {
public:
  MQ2(int pin);
  void MQ2_begin();  
  void update();
  float getRo();
  int getGasPercentage(int gas_id);
  void MQ2_print();
  bool MQ2_SD(String currentDate, String currentTime);
private:
  int _pin;
  float _Ro;
  float _rsRoRatio; 
  float MQResistanceCalculation(int raw_adc);
  int MQGetPercentage(float rs_ro_ratio, float *pcurve);
  void calibrate();  
  
};

#endif
