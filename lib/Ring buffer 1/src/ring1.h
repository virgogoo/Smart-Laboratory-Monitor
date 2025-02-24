#include <stdio.h>
#include <stdlib.h>
#include "main.h"

typedef enum
{
    RING_FAIL = -1,
    RING_OK = 0
} ring_stt_t_1;

typedef struct
{
    uint16_t write;
    uint16_t read;
    uint8_t size;
    SensorData *buf_sensor_data;
} RINGBUF;

void RINGBUF_Init(RINGBUF *ring, SensorData *buf_sensor_data, uint32_t max_size);
uint8_t RINGBUF_Put ( RINGBUF *ring, SensorData data1);
uint8_t RINGBUF_Get (RINGBUF *ring, SensorData *data1);
