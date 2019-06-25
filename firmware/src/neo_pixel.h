#ifndef SMART_UP_NEO_PIXEL__h
#define SMART_UP_NEO_PIXEL__h
#include <zephyr.h>
#include <device.h>


#if defined(CONFIG_WS2812_STRIP)
	#define NEO_STRIP_DEVICE DT_WORLDSEMI_WS2812_0_LABEL
#else
	#define NEO_STRIP_DEVICE CONFIG_WS2812B_SW_NAME
#endif

void set_pixel_color(uint8_t r,uint8_t g, uint8_t b){
	struct device* neo_pixel = device_get_binding(NEO_STRIP_DEVICE);
    if(neo_pixel){
        printk("could not get neo_pixel device\n");
		return;    
	}
    static struct led_rgb neo_pixel_color[1];
	neo_pixel_color[0].r = r;
	neo_pixel_color[0].g = g;
	neo_pixel_color[0].b = b;
	led_strip_update_rgb(neo_pixel, neo_pixel_color, 1);
}


#endif