#ifndef FIREBASEs_H
#define FIREBASEs_H

#include <Firebase_ESP_Client.h>
#include <main.h>

class FirebaseManager {
public:
    void FIREBASE_setup();
    void FIREBASE_sendDataToFirestore(const SensorData& data, String docID);
    bool FIREBASE_sendData_tem(const SensorData& data);
    bool FIREBASE_sendData_hum(const SensorData& data);
    bool FIREBASE_sendData_lpg(const SensorData& data);
    bool FIREBASE_sendData_co(const SensorData& data);
    bool FIREBASE_sendData_smoke(const SensorData& data);
    bool FIREBASE_sendData_current(const SensorData& data, const String& id);
    bool FIREBASE_sendData_power(const SensorData& data, const String& id);
    bool FIREBASE_sendData_energy(const SensorData& data, const String& id);
    bool FIREBASE_sendData_power_per_day(const SensorData& data, const String& id);
    bool FIREBASE_sendData_ip(const SensorData& data);
   

private:
    FirebaseData fbdo;
    FirebaseJson json;
    FirebaseAuth auth;
    FirebaseConfig config;
    
    bool signupOK = false;

    #define API_KEY "AIzaSyCSmoLobtX3VS4NTjzNKkPcCHzTJFWiVH8"
    #define DATABASE_URL "https://production-monitoring-sy-db8e1-default-rtdb.asia-southeast1.firebasedatabase.app/"  
    #define DATABASE_SECRET "fkm478rLnWVybIGhWeGg6yqqE0FYKxGieOjUyShG"
    #define FIREBASE_PROJECT_ID  "production-monitoring-sy-db8e1"
};

#endif 
