#ifndef SDHELPER_H
#define SDHELPER_H

#include <FS.h>
#include <SD.h>
#include <SPI.h>

class SDHelper {
public:
  SDHelper(int mosi, int miso, int sclk, int cs);
  bool begin();
  bool writeToFile(const char* path, const String& message);

private:
  int _mosi;
  int _miso;
  int _sclk;
  int _cs;
};

extern SDHelper sdHelper; 

#endif 
