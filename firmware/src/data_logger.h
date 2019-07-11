#ifndef SMART_UP_DATA_LOGGER__h
#define SMART_UP_DATA_LOGGER__h
#include <zephyr>

int start_logging(const char* name, const char* token);
int stop_logging();
#endif