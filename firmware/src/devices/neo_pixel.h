#ifndef SMART_UP_NEO_PIXEL__h
#define SMART_UP_NEO_PIXEL__h
#include <zephyr.h>
#include <device.h>


#if defined(CONFIG_WS2812_STRIP)
	#define NEO_STRIP_DEVICE DT_WORLDSEMI_WS2812_0_LABEL
#else
	#define NEO_STRIP_DEVICE CONFIG_WS2812B_SW_NAME
#endif

void neo_pixel_init();
void set_pixel_color(uint8_t r,uint8_t g, uint8_t b);
#endif