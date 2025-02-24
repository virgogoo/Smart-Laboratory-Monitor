#include "devicename.h"

// Khởi tạo biến toàn cục (chỉ một lần)
AsyncWebServer server(80);
String DeviceID = "";

// Định nghĩa hàm setupWebServer()
void setupWebServer() {
    server.on("/setDeviceName", HTTP_POST, [](AsyncWebServerRequest *request) {
        if (request->hasParam("id", true)) {
            DeviceID = request->getParam("id", true)->value();

            Serial.print("Device ID received: ");
            Serial.println(DeviceID);

            request->send(200, "text/plain", "Device ID updated");
        } else {
            request->send(400, "text/plain", "Missing deviceName parameter");
        }
    });

    server.begin();
}
