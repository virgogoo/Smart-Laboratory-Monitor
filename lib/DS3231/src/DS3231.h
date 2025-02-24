#ifndef DS3231_H
#define DS3231_H

#include <RTClib.h>

class DS3231{
public:
    DS3231(int sda, int scl);
    void begin();
    void print_date();
    void print_time();
    bool checkTime();
    String convert();
    String getDate();
    String getTime();
private:
    int _sda;
    int _scl;
    RTC_DS3231 rtc;
};
#endif 