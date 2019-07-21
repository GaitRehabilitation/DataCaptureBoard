#ifndef SMART_UP_NEO_PIXEL__h
#define SMART_UP_NEO_PIXEL__h

#include <zephyr.h>
#include <device.h>
#include <sensor.h>

void neo_blink(u8_t r,u8_t g,u8_t b,s32_t ms_delay, u8_t times);

#endif