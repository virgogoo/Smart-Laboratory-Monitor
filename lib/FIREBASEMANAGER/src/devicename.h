#ifndef DEVICENAME_H
#define DEVICENAME_H

#include <ESPAsyncWebServer.h>

// Chỉ khai báo biến bằng `extern`, không khởi tạo
extern AsyncWebServer server;
extern String DeviceID;

// Chỉ khai báo hàm setupWebServer(), không định nghĩa
void setupWebServer();

#endif  // DEVICENAME_H
