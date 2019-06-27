#ifndef SMART_UP_SENSORS_STORE__H
#ifndef SMART_UP_SENSOR_STORE__h
#define SMART_UP_SENSOR_STORE__h

#include <zephyr.h>
#include <sensor.h>

enum file_version { 
    DATA_CAPTURE_0_1 = 1,
};

enum payload_type {
    ACC_XYZ = (u16_t)1,
    GYRO_XYZ
};

struct header_t{
    u16_t size;
    char magic[4];
    enum file_version version;
    char token[10];
};

int file_store_init();
int start_session(const char* name,const char* token);
void close_session();
void push_payload(struct sensor_value* value, enum payload_type type);

#endif
