#include "PZEMMonitor.h"
#include "SDHelper.h"

String lastDate2 = "";
PZEMMonitor::PZEMMonitor(HardwareSerial &serial, uint8_t txPin, uint8_t rxPin) 
    : pzem(serial, txPin, rxPin), voltage(0), current(0), power(0), energy(0), frequency(0), powerFactor(0), apparentPower(0), reactivePower(0) {}

void PZEMMonitor::begin() {
    Serial.begin(115200);
    Serial.println("\nPZEM004T Testing");
}

void PZEMMonitor::update() {
    voltage = zeroIfNan(pzem.voltage());
    current = zeroIfNan(pzem.current());
    power = zeroIfNan(pzem.power());
    energy = zeroIfNan(pzem.energy() / 1000);   // Energy in kWh
    frequency = zeroIfNan(pzem.frequency());
    powerFactor = zeroIfNan(pzem.pf());

    // Calculate apparent and reactive power
    if (powerFactor == 0) {
        apparentPower = 0;
        reactivePower = 0;
    } else {
        apparentPower = power / powerFactor;
        reactivePower = power / powerFactor * sqrt(1 - sq(powerFactor));
    }
}

void PZEMMonitor::printData() {
    //Serial.println("");
    Serial.printf("Voltage        : %.2f V\n", voltage);
    Serial.printf("Current        : %.2f A\n", current);
    Serial.printf("Power Active   : %.2f W\n", power);  // cong suat huu ich
    //Serial.printf("Frequency      : %.2f Hz\n", frequency);
    //Serial.printf("Power Factor   : %.2f PF\n", powerFactor);
    Serial.printf("Energy         : %.5f kWh\n", energy);
    Serial.printf("Apparent Power : %.2f VA\n", apparentPower);  // cong suat bieu kien do nguon cung cap
    Serial.printf("Reactive Power : %.2f VAR\n", reactivePower);  // cong suat phan khang
}
bool PZEMMonitor::PZEM_SD(String currentDate, String currentTime) {
    update();
    if (currentDate != lastDate2) {
    lastDate2 = currentDate;
    String dateData = "\nDate: " + currentDate;
    if (sdHelper.writeToFile("/PZEMData.txt", dateData)) {
      Serial.println("Ngày mới đã được ghi vào thẻ SD !!!");
    } else {
      Serial.println("[ERROR] Không thể ghi ngày vào thẻ SD.");
        }
    }
    String data = currentTime + ":   Voltage: " + String(voltage) + ", Current: " + String(current) + 
                ", Energy: " + String(energy) + ", Active power: " + String(power) + ", Reactive power: " + 
                 String(reactivePower) + ", Apparent power: " + String(apparentPower);
    if (sdHelper.writeToFile("/PZEMData.txt", data)) {
    Serial.println("Dữ liệu PZEM đã được ghi vào thẻ SD !!! \n");
    return true;
    } else {
    Serial.println("[ERROR] Không thể ghi dữ liệu PZEM vào thẻ SD.");
    return false;
    }
}

float PZEMMonitor::getVoltage() {
    return voltage;
}

float PZEMMonitor::getCurrent() {
    return current;
}

float PZEMMonitor::getPower() {
    return power;
}

float PZEMMonitor::getEnergy() {
    return energy;
}

float PZEMMonitor::getFrequency() {
    return frequency;
}

float PZEMMonitor::getPowerFactor() {
    return powerFactor;
}

float PZEMMonitor::getApparentPower() {
    return apparentPower;
}

float PZEMMonitor::getReactivePower() {
    return reactivePower;
}

float PZEMMonitor::zeroIfNan(float value) {
    return isnan(value) ? 0 : value;
}

bool PZEMMonitor::reset(){
    if (pzem.resetEnergy()) {  
        return true; 
    } else {
        return false; 
    }
}
