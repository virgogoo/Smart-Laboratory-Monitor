#include "mainlib.h"
#include "esp_task_wdt.h"
#include "freertos/queue.h"

SensorData buffer[BUFFER_SIZE];
RINGBUF ringBuffer;
SHT3x sht30;
//SDHelper sdHelper(SD_MOSI, SD_MISO, SD_SCLK, SD_CS);
MQ2 mq2(34);
FirebaseManager firebaseManager;
PZEMMonitor pzemMonitor(Serial2, 16, 17);
DS3231 ds3231(21, 22);
//String currentDate, currentTime;
SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);
uint32_t draw_buf[DRAW_BUF_SIZE / 4];
TaskHandle_t Task3Handle;
TaskHandle_t Task2Handle;
TaskHandle_t Task4Handle;
TaskHandle_t Task1Handle;
void autoWifi() {
    WiFi.mode(WIFI_STA);
    Serial.begin(115200);
    WiFiManager wm;
    if (!wm.autoConnect(WIFI_AP_NAME)) {
        Serial.println("Failed to connect to WiFi");
    } else {
        Serial.println("Connected to WiFi");
    }
}

bool sendToFirebase_tem(SensorData &data) {
    if (WiFi.status() == WL_CONNECTED) {
        if (firebaseManager.FIREBASE_sendData_tem(data)){
            Serial.println("temperature sent to Firebase.");
            return true;
        }
        else return false;
    } else {
        Serial.println("WiFi not connected, skipping Firebase send.");
        return false;
    }
}

bool sendToFirebase_hum(SensorData &data) {
    if (WiFi.status() == WL_CONNECTED) {
        if (firebaseManager.FIREBASE_sendData_hum(data)){
            Serial.println("humidity sent to Firebase.");
            return true;
        }
        else return false;
    } else {
        Serial.println("WiFi not connected, skipping Firebase send.");
        return false;
    }
}

bool sendToFirebase_lpg(SensorData &data) {
    if (WiFi.status() == WL_CONNECTED) {
        if (firebaseManager.FIREBASE_sendData_lpg(data)){
            Serial.println("LPG sent to Firebase.");
            return true;
        }
        else return false;
    } else {
        Serial.println("WiFi not connected, skipping Firebase send.");
        return false;
    }
}

bool sendToFirebase_co(SensorData &data) {
    if (WiFi.status() == WL_CONNECTED) {
        if (firebaseManager.FIREBASE_sendData_co(data)){
            Serial.println("CO sent to Firebase.");
            return true;
        }
        else return false;
    } else {
        Serial.println("WiFi not connected, skipping Firebase send.");
        return false;
    }
}

bool sendToFirebase_smoke(SensorData &data) {
    if (WiFi.status() == WL_CONNECTED) {
        if (firebaseManager.FIREBASE_sendData_smoke(data)){
            Serial.println("smoke sent to Firebase.");
            return true;
        }
        else return false;
    } else {
        Serial.println("WiFi not connected, skipping Firebase send.");
        return false;
    }
}

bool sendToFirebase_current(const SensorData& data, const String& id) {
    if (WiFi.status() == WL_CONNECTED) {
        if (firebaseManager.FIREBASE_sendData_current(data, data.id)) {
            return true;
        } else {
            return false;
        }
    } else {
        Serial.println("WiFi not connected, skipping Firebase send.");
        return false;
    }
}

bool sendToFirebase_power(const SensorData& data, const String& id) {
    if (WiFi.status() == WL_CONNECTED) {
        if (firebaseManager.FIREBASE_sendData_power(data, data.id)) {
            return true;
        } else {
            return false;
        }
    } else {
        Serial.println("WiFi not connected, skipping Firebase send.");
        return false;
    }
}

bool sendToFirebase_energy(const SensorData& data, const String& id) {
    if (WiFi.status() == WL_CONNECTED) {
        if (firebaseManager.FIREBASE_sendData_energy(data, data.id)) {
            return true;
        } else {
            return false;
        }
    } else {
        Serial.println("WiFi not connected, skipping Firebase send.");
        return false;
    }
}

bool sendToFirebase_ip(const SensorData& data) {
    if (WiFi.status() == WL_CONNECTED) {
        if (firebaseManager.FIREBASE_sendData_ip(data)) {
            return true;
        } else {
            return false;
        }
    } else {
        Serial.println("WiFi not connected, skipping Firebase send.");
        return false;
    }
}

void SendDataToFirebase(void *arg) {
    SensorData data;
    while (1) {
        bool connected = false;
        if (RINGBUF_Get(&ringBuffer, &data) == RING_OK)  {
            while(connected != true)
        {
            connected = sendToFirebase_tem(data);
            connected = false;
            connected = sendToFirebase_hum(data);
            connected = false;
            connected = sendToFirebase_lpg(data);
            connected = false;
            connected = sendToFirebase_co(data);
            connected = false;
            connected = sendToFirebase_smoke(data);
            connected = false;
            connected = sendToFirebase_current(data, data.id);
            connected = false;
            connected = sendToFirebase_power(data, data.id);
            connected = false;
            connected = sendToFirebase_energy(data, data.id);
            connected = false;
            connected = sendToFirebase_ip(data);
            pzemMonitor.printData();
            sht30.printData();
            mq2.MQ2_print();
            //currentDate = ds3231.getDate();
            //currentTime = ds3231.getTime();
            //sht30.SHT3x_SD(currentDate, currentTime);
            //mq2.MQ2_SD(currentDate, currentTime);
            //pzemMonitor.PZEM_SD(currentDate, currentTime);
        }
        vTaskDelay(pdMS_TO_TICKS(3000)); 
        }
    }
}

char text_buffer[16];
void SendDataToRing(void *arg) {
    while (1) {
        mq2.update();
        sht30.UpdateData();
        pzemMonitor.update();
        SensorData data;
        data.ip = WiFi.localIP().toString();
        data.id = DeviceID;
        data.temperature = sht30.GetTemperature();
        data.humidity = sht30.GetRelHumidity();
        sprintf(text_buffer, "%.2f", data.temperature);
        lv_label_set_text(ui_label15, text_buffer);
        sprintf(text_buffer, "%.2f", data.humidity);
        lv_label_set_text(ui_label16, text_buffer);
        data.LPG =mq2.getGasPercentage(GAS_LPG);
        data.CO =  mq2.getGasPercentage(GAS_CO);
        data.smoke = mq2.getGasPercentage(GAS_SMOKE);
        sprintf(text_buffer, "%d", data.LPG);
        lv_label_set_text(ui_label17, text_buffer);
        sprintf(text_buffer, "%d", data.CO);
        lv_label_set_text(ui_label18, text_buffer);
        sprintf(text_buffer, "%d", data.smoke);
        lv_label_set_text(ui_label19, text_buffer);
        data.current = pzemMonitor.getCurrent(); 
        data.power = pzemMonitor.getPower();
        data.energy = pzemMonitor.getEnergy();
        sprintf(text_buffer, "%.2f", data.current);
        lv_label_set_text(ui_label20, text_buffer);
        sprintf(text_buffer, "%.2f", data.power);
        lv_label_set_text(ui_label21, text_buffer);
        sprintf(text_buffer, "%.5f", data.energy);
        lv_label_set_text(ui_label22, text_buffer);
        if (data.temperature > TEMPERATURE_THRESHOLD) {
            digitalWrite(BUZZER_PIN, HIGH); 
        } else {
            digitalWrite(BUZZER_PIN, LOW); 
        }
        if (RINGBUF_Put(&ringBuffer, data) == RING_FAIL) {
        printf("Ring buffer full! Dropping data.\n");
        } else {
        printf("Data added to ring buffer.\n");
        }
        vTaskDelay(pdMS_TO_TICKS(3000)); 
    }
}

void setupLVGL() {
    lv_init();
    lv_log_register_print_cb([](lv_log_level_t level, const char *buf) {
        Serial.println(buf);
    });
    touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
    touchscreen.begin(touchscreenSPI);
    touchscreen.setRotation(2);

    lv_display_t *disp = lv_tft_espi_create(SCREEN_WIDTH, SCREEN_HEIGHT, draw_buf, sizeof(draw_buf));
    lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_270);


    lv_indev_t *indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev, [](lv_indev_t *indev, lv_indev_data_t *data) {
        if (touchscreen.tirqTouched() && touchscreen.touched()) {
            TS_Point p = touchscreen.getPoint();
            data->point.x = map(p.x, 200, 3700, 0, SCREEN_WIDTH);
            data->point.y = map(p.y, 240, 3800, 0, SCREEN_HEIGHT);
            data->state = LV_INDEV_STATE_PRESSED;
        } else {
            data->state = LV_INDEV_STATE_RELEASED;
        }
    });
    ui_init();
}

void TimeAndDate(void *arg) {
    while (1) {
        lv_task_handler();
        lv_tick_inc(5);
        vTaskDelay(pdMS_TO_TICKS(10)); 

    }
}

void PowerPerDay(void *arg) {
    while (1) {
        SensorData data;
        String id = ds3231.convert();
        if (ds3231.checkTime()) {
        data.power_per_day = pzemMonitor.getEnergy();
        firebaseManager.FIREBASE_sendDataToFirestore(data, id);
        Serial.print("Total Energy: ");
        Serial.printf("%.5f kWh\n",pzemMonitor.getEnergy());
            if(pzemMonitor.reset()){
                Serial.println("Success !!!");
                }
        }
        else 
        {
            Serial.println("Not now !!!");
        }
        // //ds3231.print_date();
        // //ds3231.print_time();
        vTaskDelay(pdMS_TO_TICKS(5000)); 

    }
}

void setup() {
    RINGBUF_Init(&ringBuffer, buffer, BUFFER_SIZE);
    Serial.begin(115200);
    setupLVGL();
    autoWifi();
    ds3231.begin();
    setupWebServer();
    pzemMonitor.begin();
    pinMode(BUZZER_PIN, OUTPUT);
    firebaseManager.FIREBASE_setup();
    //sdHelper.begin();
    sht30.Begin();
    mq2.MQ2_begin();
    xTaskCreatePinnedToCore(TimeAndDate, "TimeAndDate", 16000, NULL, 1, &Task2Handle, 0);
    xTaskCreatePinnedToCore(SendDataToFirebase, "SendDataToFirebase", 16000, NULL, 1, &Task3Handle, 1);
    xTaskCreatePinnedToCore(SendDataToRing, "SendDataToRing", 16000, NULL, 1, &Task4Handle, 0);
    xTaskCreatePinnedToCore(PowerPerDay, "PowerPerDay", 16000, NULL, 1, &Task1Handle, 1);
   //sensorQueue = xQueueCreate(20, sizeof(SensorData));
}


void loop() {
}

