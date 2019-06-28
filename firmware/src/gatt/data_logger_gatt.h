#ifndef SMART_UP_DATA_LOGGER__h
#define SMART_UP_DATA_LOGGER__h

enum session_status{
    START_LOGGING,
    INVALID_SESSION_CONFIG,
    STOPPED_LOGGING
};

enum session_flag{
    
}

struct session_config
{
    char name[50];
    char token[25];
    char description[256];
};


void data_logger_gatt_init(void);
void data_logger_gatt_notify(void);
#endif