#include <stdint.h>
#include <stdlib.h>
#include "ring1.h"
#include "main.h"


void RINGBUF_Init(RINGBUF *ring, SensorData *buf_sensor_data, uint32_t max_size)
{
    ring->write = 0;
    ring->read = 0;
    ring->buf_sensor_data = buf_sensor_data;
    ring->size = max_size;
}

uint8_t RINGBUF_Put ( RINGBUF *ring, SensorData data)
{
    if(ring == NULL || ring->buf_sensor_data == NULL || ring->size == 0) return RING_FAIL;
    uint16_t temp = ring->write;
    temp++;

    if(temp >= ring->size ) //quay dau lai ve 0
    {
        temp = 0;
    }
    if(temp == ring->read) //bo dem day
    {
        return RING_FAIL;
    }
    ring->buf_sensor_data[ring->write] = data;
    ring->write = temp;
    return RING_OK;
}

uint8_t RINGBUF_Get (RINGBUF *ring, SensorData *data)
{
    if(ring == NULL || data == NULL || ring->buf_sensor_data == 0) return RING_FAIL ;
    if (ring->write == ring->read) // bo dem rong
    {
        return RING_FAIL;
    }
    *data = ring->buf_sensor_data[ring->read];
    ring->read++;
    if(ring->read >= ring->size)
    {
        ring->read=0;  //quay dau lai ve 0
    }
    return RING_OK;
}
