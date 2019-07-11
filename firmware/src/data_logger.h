#ifndef SMART_UP_DATA_LOGGER__h
#define SMART_UP_DATA_LOGGER__h
#include <zephyr.h>



int start_logging(const char* name, const char* token);
void set_capture_rate(u32_t hz);
int stop_logging();
#endif