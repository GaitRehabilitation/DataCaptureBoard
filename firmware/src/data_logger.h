#ifndef SMART_UP_DATA_LOGGER__h
#define SMART_UP_DATA_LOGGER__h
#include <zephyr.h>

int start_logging(s32_t timestamp,const char* name, const char* token);
int stop_logging();
bool is_logging();
// void set_capture_rate(u32_t hz);
#endif