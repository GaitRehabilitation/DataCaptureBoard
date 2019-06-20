#include "neo_pixel.h"
#include "sensors_device.h"
#include <led_strip.h>



void set_pixel_color(struct sensor_configuration* config,uint8_t r,uint8_t g, uint8_t b){
    static struct led_rgb neo_pixel_color[1];
	neo_pixel_color[0].r = r;
	neo_pixel_color[0].g = g;
	neo_pixel_color[0].b = b;
	led_strip_update_rgb(config->neo_pixel, neo_pixel_color, 1);
}

