#ifndef SMART_UP_SENSORS_STORE__H
#define SMART_UP_SENSORS_STORE__H

#include <zephyr.h>

#define BLOCK_SIZE 512

const char MAGIC[4] = {0x10,0x12,0xe,0x11};
enum file_version { 
    DATA_CAPTURE_0_1 = 1,
};

enum payload_type {
    ACC_XYZ = (u16_t)1,
    GYRO_XYZ
};

struct data_t {
    u64_t time;
    enum payload_type type;
    struct sensor_value value[6];
};


// size of the units in each block
#define DATA_BLOCK_SIZE (BLOCK_SIZE-2) 
#define DATA_DIM (DATA_BLOCK_SIZE / sizeof(struct data_t))
#define DATA_DIM_FILL (DATA_BLOCK_SIZE -  (DATA_DIM * sizeof(struct data_t)))

struct block_t {
    u16_t count;
    struct data_t payload[DATA_DIM];
    u8_t fill[DATA_DIM_FILL]
};


struct header_payload{
    char magic[4];
    enum file_version version;
    char token[50];
};

#define HEADER_DIM_FILL (BLOCK_SIZE - sizeof(struct header_payload))
struct header_payload_block{
    struct header_payload payload;
    u8_t fill[HEADER_DIM_FILL];
};


struct header_payload* getHeader();
void init();
void start_sessions(char token[50]);
void push_payload(struct sensor_value* value);


#endif