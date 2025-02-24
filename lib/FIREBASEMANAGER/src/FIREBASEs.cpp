#include "FIREBASEs.h"
#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>
#include <devicename.h>

void FirebaseManager::FIREBASE_setup() {
    config.api_key = API_KEY;
    config.database_url = DATABASE_URL;
    config.signer.tokens.legacy_token = DATABASE_SECRET; 
    config.service_account.data.project_id = FIREBASE_PROJECT_ID;
    config.service_account.data.client_email = "firebase-adminsdk-bttjs@production-monitoring-sy-db8e1.iam.gserviceaccount.com";
    config.service_account.data.private_key = 
    "-----BEGIN PRIVATE KEY-----\n"
    "MIIEvAIBADANBgkqhkiG9w0BAQEFAASCBKYwggSiAgEAAoIBAQDvFZAbvQWw4PUN\nNBBHEgsySabjyL5w4JzMb/wYCKI0QhPEKmv7QBgx//1RfA8CoNeuUozL2nMVyW81\nS0ohb0Ij3lmVniIEY3wO9odbOBdCYIY6imTnahxuHrz8dg0+JzX4Ww5FCoQinjSq\nBv0sdmGTUCJQFMdzuXFeqRt3G6on9fgHHpFDcI1JKVHVfnTc1C8kdtDq00FwaOix\n4a5pwp9u+WvjdnOWWMX4ec/xYpJOwxUUnvS1CIcKTPSAY0S2eHmgqAgz8J9p5aGS\nkaVGstzLM6aqAgU88bmf+NQSsbmcVIKwRHvup7DHbHBQ+ifgy81omHOYRGLheJ3G\nF5vf4nndAgMBAAECggEAWlG1DSWNXtK9AG3osFCatjaou2h8uTvBQGIVxCaO0Fse\nCH9WJ6aA/XKNihjpur50fEBnPCOcUmC0iFeW+6aCP/ahtSn2A95pYWW0oLtB3iuE\nydy6XcnyT4+BKYaXXiGF+/q6G07ruAA4OPtG7WMTXYlqTQJsjsVBlNchrw9eapWA\nX2VBCyR4rJQURHaJNAcSTrW2c1O//YAFKiujLYJNDs3SlbOVaX9zg0rMAWXdHnjf\nNS0p2ndSBBIE4ecvykySVPbTpD3UDTY2Wd+47JCn6vZamJ6/6GXqZJmpelWyv/jS\n3YuQeM3hu4pmy/rKWjPi06FBU4rb2z9QmD9/2fivKQKBgQD3c6Ghs6gotqzUW5Vl\n5Xl7IryVHgxehfZsttOuIurbB4879347bv9uN2xwLfvXIvM2gYz0UdvIRiop30rR\nLyisfi3raaxjZdNu3OzZOgWDkVeoF6h3IkOOxiw++20Xn2Vmv2+O466gPuul5YDy\nSrhv7mbK3hYJap9HRIBWq8ws8wKBgQD3V+7Wc6mp/BeafCKylP8bbjx3JCtWTF4m\nGAo+eIrvOKCKgYGbYwCdRfCdfdrtgNQM1eejSf6veBgxg5WMg/p9MJw6fxl8R3cP\nUyn4HbOG5E14nbXDOEE8lst3AFJVH4lQB8L5sgDLHaWuP9z83vM8+RuAL5Seg6iY\nqqkoXC4x7wKBgHa+ZUysYsCO0Kbi//EyyjXduHMyRStCy7rljPTeSqcqnIBhRpEM\ntcRVElNOrbBSVDXOuy4u7fHQQcFwJn31TGZh8nUqc5ALOAfWOk4Per/lChRerffl\nWFf2HxtmGbahRc6lhMoj1hONvhUQ6ezbEGCeHXOyWQ7RvHc9lvyAWm0jAoGACYmD\ndRNqpFpLErLcp6QlHgqnHDTx0tcI/lEI/BWrzcOSNST/OV2c5XOP7pKuwV+pTYFl\n+B7fSibIUAhx2MQyAWfBbmP+OJOM3LNpN971UCs3bYIvQwLFSS/LUqBZjFy177cM\n5pHdg/d1rv1ZaQqzuFMmo0+yXFZZRuG1ug+r3FMCgYAyvQ9NxQaRqTQIocBVCLd0\ndyIE5Ukj1oTaWvAYMZItymrF2mR8DvtJqIgvfDPeqh60dXqKh6M/JGLaiu2oscNQ\n33ZV/OwVtLFf7s1e9xB/5MY/IyEa4kImN8EEksIYm2uFuhOJwpo5r90OVDZTqsJB\nhPVLkyy1pfSTk8lFiwY4Yw==\n"
    "-----END PRIVATE KEY-----\n";
    config.token_status_callback = tokenStatusCallback;
    Firebase.reconnectNetwork(true);
    fbdo.setBSSLBufferSize(16384, 16384);
    Firebase.begin(&config, &auth);
}

bool FirebaseManager::FIREBASE_sendData_tem(const SensorData& data){
    if (Firebase.ready()) {
        // Send sensor data individually to Firebase
        if (Firebase.RTDB.setFloat(&fbdo, "/sensor/SHT30/temperature", data.temperature)) {
            //Serial.println("Temperature sent to Firebase successfully.");
            return true;
        } else {
            //Serial.println("Failed to send temperature.");
            //Serial.println(fbdo.errorReason());
            return false;
        }
    }
    else return false;
}

bool FirebaseManager::FIREBASE_sendData_hum(const SensorData& data){
    if (Firebase.ready()) {
    if (Firebase.RTDB.setFloat(&fbdo, "/sensor/SHT30/humidity", data.humidity)) {
           // Serial.println("Humidity sent to Firebase successfully.");
           return true;
        } else {
           // Serial.println("Failed to send humidity.");
            //Serial.println(fbdo.errorReason());
            return false;
        }
    }
    else return false;
}

bool FirebaseManager::FIREBASE_sendData_lpg(const SensorData& data){
    if (Firebase.ready()) {
    if (Firebase.RTDB.setFloat(&fbdo, "/sensor/MQ2/LPG", data.LPG)) {
            //Serial.println("LPG sent to Firebase successfully.");
            return true;
        } else {
            //Serial.println("Failed to send LPG.");
            //Serial.println(fbdo.errorReason());
            return false;
        }
    }
    else return false;
}

bool FirebaseManager::FIREBASE_sendData_co(const SensorData& data){
    if (Firebase.ready()) {
    if (Firebase.RTDB.setFloat(&fbdo, "/sensor/MQ2/CO", data.CO)) {
            //Serial.println("CO sent to Firebase successfully.");
            return true;
        } else {
            //Serial.println("Failed to send CO.");
            //Serial.println(fbdo.errorReason());
            return false;
        }
    }
    else return false;
}

bool FirebaseManager::FIREBASE_sendData_smoke(const SensorData& data){
    if (Firebase.ready()) {
    if (Firebase.RTDB.setFloat(&fbdo, "/sensor/MQ2/smoke", data.smoke)) {
           // Serial.println("Smoke sent to Firebase successfully.");
           return true;
        } else {
           // Serial.println("Failed to send smoke.");
            //Serial.println(fbdo.errorReason());
            return false;
        }
    }
    else return false;
}

bool FirebaseManager::FIREBASE_sendData_current(const SensorData& data, const String& id) {
    if (Firebase.ready()) {
        MB_String path = MB_String("/devices/") + MB_String(id) + MB_String("/current");
        if (Firebase.RTDB.setFloat(&fbdo, path.c_str(), data.current)) {
            return true;
        } else {
            return false;
        }
    }
    return false;
}

bool FirebaseManager::FIREBASE_sendData_power(const SensorData& data, const String& id) {
    if (Firebase.ready()) {
        MB_String path = MB_String("/devices/") + MB_String(id) + MB_String("/power");

        if (Firebase.RTDB.setFloat(&fbdo, path.c_str(), data.power)) {
            return true;
        } else {
            return false;
        }
    }
    return false;
}

bool FirebaseManager::FIREBASE_sendData_energy(const SensorData& data, const String& id) {
    if (Firebase.ready()) {
        MB_String path = MB_String("/devices/") + MB_String(id) + MB_String("/energy");

        if (Firebase.RTDB.setFloat(&fbdo, path.c_str(), data.energy)) {
            return true;
        } else {
            return false;
        }
    }
    return false;
}

bool FirebaseManager::FIREBASE_sendData_power_per_day(const SensorData& data, const String& id) {
    if (Firebase.ready()) {
       MB_String path = MB_String("/devices/") + MB_String(id) + MB_String("/powerPerDay");
        if (Firebase.RTDB.setFloat(&fbdo, path.c_str(), data.energy)) {
            return true;
        } else {
            return false;
        }
    }
    return false;
}

bool FirebaseManager::FIREBASE_sendData_ip(const SensorData& data) {
    if (Firebase.ready()) {
        if (Firebase.RTDB.setString(&fbdo, "/devices/ip", data.ip)) {
            return true;
        } else {
            return false;
        }
    }
    return false;
}

void FirebaseManager::FIREBASE_sendDataToFirestore(const SensorData& data, String docID) {
    if(Firebase.ready()){
    FirebaseJson content;

    json.set("fields/powerPerDay/doubleValue", String(data.power_per_day).c_str());

    String documentPath = DeviceID ;
    documentPath += "/";
    documentPath += docID;
    
    if (Firebase.Firestore.createDocument(&fbdo, FIREBASE_PROJECT_ID, "", documentPath.c_str(), json.raw())) {
        Serial.println("Data sent to Firestore successfully.");
    } else {
        Serial.print("Error sending data to Firestore: ");
        Serial.println(fbdo.errorReason());
    }
    }else{
        Serial.println("Authentication failed. Data not sent.");
    }
}



