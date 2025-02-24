#include "MQ2.h"
#include <math.h>
#include "SDHelper.h"

String lastDate1 = "";  
float LPGCurve[2] = {1.287090027, -0.4613333465};
float COCurve[2] = {1.493962434, -0.33046030018};
float SmokeCurve[2] = {1.608961312, -0.4434025702};

MQ2::MQ2(int pin) : _pin(pin), _Ro(10), _rsRoRatio(0) {}

void MQ2::MQ2_begin() {
  Serial.begin(115200);  
  Serial.print("Calibrating...\n");
  calibrate(); 
  Serial.print("Calibration is done...\n");
  Serial.print("Ro=");
  Serial.print(getRo());
  Serial.println(" kohm");
}

void MQ2::calibrate() {
  float val = 0;
  for (int i = 0; i < CALIBRATION_SAMPLE_TIMES; i++) {
    val += MQResistanceCalculation(analogRead(_pin));
    delay(CALIBRATION_SAMPLE_INTERVAL);
  }
  val = val / CALIBRATION_SAMPLE_TIMES;
  _Ro = val / RO_CLEAN_AIR_FACTOR;
}

void MQ2::update() {
  float rs = 0;
  for (int i = 0; i < READ_SAMPLE_TIMES; i++) {
    rs += MQResistanceCalculation(analogRead(_pin));
    delay(READ_SAMPLE_INTERVAL);
  }
  _rsRoRatio = rs / READ_SAMPLE_TIMES / _Ro;
}

float MQ2::getRo() {
  return _Ro;
}

int MQ2::getGasPercentage(int gas_id) {
  if (gas_id == GAS_LPG) {
    return MQGetPercentage(_rsRoRatio, LPGCurve);
  } else if (gas_id == GAS_CO) {
    return MQGetPercentage(_rsRoRatio, COCurve);
  } else if (gas_id == GAS_SMOKE) {
    return MQGetPercentage(_rsRoRatio, SmokeCurve);
  }
  return 0;
}

float MQ2::MQResistanceCalculation(int raw_adc) {
  return ((float)RL_VALUE * (4095 - raw_adc) / raw_adc);
}

int MQ2::MQGetPercentage(float rs_ro_ratio, float *pcurve) {
  return (pow(10, (log10(rs_ro_ratio) - pcurve[0]) / pcurve[1]));
}

void MQ2::MQ2_print(){
  Serial.print("LPG: ");
  Serial.print(getGasPercentage(GAS_LPG));
  Serial.print(", CO: ");
  Serial.print(getGasPercentage(GAS_CO));
  Serial.print(", Smoke: ");
  Serial.print(getGasPercentage(GAS_SMOKE));
  Serial.println();
}

bool MQ2::MQ2_SD(String currentDate, String currentTime) {
  update();
  uint16_t lpg = getGasPercentage(GAS_LPG);
  uint16_t co = getGasPercentage(GAS_CO);
  uint16_t smoke = getGasPercentage(GAS_SMOKE);
  if (currentDate != lastDate1) {
    lastDate1 = currentDate;
    String dateData = "\nDate: " + currentDate;
    if (sdHelper.writeToFile("/MQ2Data.txt", dateData)) {
      Serial.println("Ngày mới đã được ghi vào thẻ SD !!!");
    } else {
      Serial.println("[ERROR] Không thể ghi ngày vào thẻ SD.");
    }
  }
  String data = currentTime + ":   LPG: " + String(lpg) + ", CO: " + String(co) + ", Smoke: " + String(smoke);

  if (sdHelper.writeToFile("/MQ2Data.txt", data)) {
    Serial.println("Dữ liệu MQ2 đã được ghi vào thẻ SD !!!");
    return true;
  } else {
    Serial.println("[ERROR] Không thể ghi dữ liệu MQ2 vào thẻ SD.");
    return false;
  }
}
