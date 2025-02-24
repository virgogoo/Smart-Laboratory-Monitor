#include "SDHelper.h"

SDHelper::SDHelper(int mosi, int miso, int sclk, int cs) 
  : _mosi(mosi), _miso(miso), _sclk(sclk), _cs(cs) {}

bool SDHelper::begin() {
  SPI.begin(_sclk, _miso, _mosi, _cs);
  if (!SD.begin(_cs)) {
    return false; 
  }
  return true; 
}

bool SDHelper::writeToFile(const char* path, const String& message) {
    File file = SD.open(path, FILE_APPEND);  // Mở file với chế độ append
    if (!file) {
        Serial.println("[ERROR] Không thể mở file để ghi.");
        return false;
    }
    file.println(message);  // Thêm dữ liệu vào cuối file
    file.close();
    return true;
}
