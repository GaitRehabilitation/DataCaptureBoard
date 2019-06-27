#include "neo_pixel.h"

static struct device* neo_pixel_dev;
void neo_pixel_init(){
    neo_pixel_dev = device_get_binding(NEO_STRIP_DEVICE);
    if(neo_pixel_dev){
        printk("could not get neo_pixel device\n");
		return -EINVAL;    
	}
    return 0;
}

void set_pixel_color(uint8_t r,uint8_t g, uint8_t b){
	
    static struct led_rgb neo_pixel_color[1];
	neo_pixel_color[0].r = r;
	neo_pixel_color[0].g = g;
	neo_pixel_color[0].b = b;
	led_strip_update_rgb(neo_pixel_dev, neo_pixel_color, 1);
}
