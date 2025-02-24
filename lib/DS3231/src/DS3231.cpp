#include "DS3231.h"

DS3231::DS3231(int sda, int scl)
  :_sda(sda), _scl(scl) {}

void DS3231::begin(){
  Wire.begin();
  if (!rtc.begin()) {
    Serial.println("Không tìm thấy module DS3231!");
    while (1);
  }
  if (rtc.lostPower()) {
    Serial.println("DS3231 mất nguồn, thiết lập lại thời gian!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void DS3231::print_date(){
  DateTime now = rtc.now();
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" ");
}

void DS3231::print_time(){
  DateTime now = rtc.now();
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.print("\n");
  Serial.print("**********************\n");
}

bool DS3231::checkTime(){
  DateTime now = rtc.now();
  if (now.hour() == 15 && now.minute() == 17 && now.second() == 00) {
        return true;
    }
  else return false;
}

String DS3231::convert() {
  DateTime now = rtc.now();
  char docIdBuffer[16];
  snprintf(docIdBuffer, sizeof(docIdBuffer),
           "%02d-%02d-%04d",
           now.day(),
           now.month(),
           now.year());
  String docID = docIdBuffer;
  return docID;
}

String DS3231::getDate() {
  DateTime now = rtc.now();
  String currentDate = String(now.day()) + "/" + String(now.month()) + "/" + String(now.year());
  return currentDate;
}

String DS3231::getTime() {
  DateTime now = rtc.now();
  String currentTime = String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());
  return currentTime;
}
