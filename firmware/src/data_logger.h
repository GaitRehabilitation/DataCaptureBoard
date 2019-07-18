#ifndef SMART_UP_DATA_LOGGER__h
#define SMART_UP_DATA_LOGGER__h
#include <zephyr.h>

int start_logging(const char* name, const char* token);
int stop_logging();
void set_capture_rate(u32_t hz);
#endif