#ifndef MAIN_LIB_H
#define MAIN_LIB_H

#include <Arduino.h>
#include <Wire.h>
#include <Firebase_ESP_Client.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
#include <ui.h>
#include "SHT3x.h"
#include "MQ2.h"
#include "SDHelper.h"
#include "FIREBASEs.h"
#include "PZEMMonitor.h"
#include "WiFiManager.h"  
#include "DS3231.h"
#include "ring1.h"
#include "devicename.h"


#define BUFFER_SIZE  10
#define XPT2046_IRQ 36   // T_IRQ
#define XPT2046_MOSI 32  // T_DIN
#define XPT2046_MISO 39  // T_OUT
#define XPT2046_CLK 25   // T_CLK
#define XPT2046_CS 33    // T_CS
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320
#define DRAW_BUF_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT / 10 * (LV_COLOR_DEPTH / 8))
#define WIFI_AP_NAME "AutoConnectAP"
#define WIFI_RECONNECT_DELAY_MS 5000
#define BUZZER_PIN 27 
#define TEMPERATURE_THRESHOLD 50

#define SD_MOSI 23
#define SD_MISO 19
#define SD_SCLK 18
#define SD_CS 5

#endif