#ifndef SMART_UP_DATA_LOGGER__h
#define SMART_UP_DATA_LOGGER__h


#include <zephyr.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/conn.h>
#include <bluetooth/uuid.h>
#include <bluetooth/gatt.h>


// 7be194b7-585e-c98a-2a4e-00665b2b0c5d
#define DATA_LOGGER_UUID BT_UUID_DECLARE_128(0x5d,0x0c,0x2b,0x5b,0x66,0x00,0x4e,0x2a,0x8a,0xc9,0x5e,0x58,0xb7,0x94,0xe1,0x7b)
// a0ec0f71-c4bb-218a-b344-32c7047bc3a1
#define DATA_LOGGER_CONFIGURE_UUID BT_UUID_DECLARE_128(0xa1,0xc3,0x7b,0x04,0xc7,0x32,0x44,0xb3,0x8a,0x21,0xbb,0xc4,0x71,0x0f,0xec,0xa0)
// 43512ebd-c8da-ccb9-a94e-8ce99a8be26a
#define DATA_LOGGER_TARGET_NAME_UUID BT_UUID_DECLARE_128(0x6a,0xe2,0x8b,0x9a,0xe9,0x8c,0x4e,0xa9,0xb9,0xcc,0xda,0xc8,0xbd,0x2e,0x51,0x43)


// cfa0e625-e6a0-4614-b73b-3a62ce32df2e
#define DATA_LOGGER_STREAM_UUID BT_UUID_DECLARE_128(0xcf,0xa0,0xe6,0x25,0xe6,0xa0,0x46,0x14,0xb7,0x3b,0x3a,0x62,0xce,0x32,0xdf,0x2e)




enum session_status{
    NONE = (u8_t)0,
    START_LOGGING,
    STOP_LOGGING,
    PING_LOGGING,
    SET_DESCRIPTION,
    STOPPED_LOGGING
};

struct session_device_name
{
    char name[60];
};


struct start_logging_payload
{
    u32_t unix_time;
    char token[10];
} __packed;

struct session_config
{
    enum session_status status;
    union payload
    {
        struct start_logging_payload start_logging;
    } payload;
} __packed;


void data_logger_gatt_init(void);
void data_logger_gatt_notify(void);
#endif