#ifndef SMART_UP_SENSOR_STORE__h
#define SMART_UP_SENSOR_STORE__h

#include <zephyr.h>
#include <sensor.h>

enum file_version { 
    DATA_CAPTURE_0_1 = (u8_t)1,
};

enum payload_type {
    ACC_XYZ = (u16_t)1,
    GYRO_XYZ,
    ACC_GYRO_XYZ
};

struct header_t{
    u16_t size;
    char magic[4];
    enum file_version version;
    u32_t timestamp;
    char token[10];
} __packed;

int file_store_init();
/**
 *  @name name of the file to create
 *  @token hash token to identify data, note token limit is 10 characters
 */
int start_session(u32_t timestamp,const char* name,const char* token);
void close_session();
int push_payload(s64_t timestamp,struct sensor_value* value, enum payload_type type);
int store_sync();
#endif
