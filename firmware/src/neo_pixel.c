#include "neo_pixel.h"
#include <led_strip.h>
#include "device_targets.h"

#define NEO_PIXEL_STACK_SIZE 200
#define DATA_NEO_PIXEL_PRIORITY 5

static k_tid_t thread_id = NULL;
static struct k_thread neo_pixel_thread_data;

K_THREAD_STACK_DEFINE(data_pixel_stack,NEO_PIXEL_STACK_SIZE);

static struct led_rgb color;
static s32_t delay;
static u8_t count;
static void neo_pixel_thread(void * u1, void * u2, void * u3){
    do{
        set_pixel_color(color.r,color.g,color.b);
        k_sleep(delay);
        set_pixel_color(0,0,0);
        k_sleep(delay);
        count--;
    } while(count > 0);
}

void neo_blink(u8_t r,u8_t g,u8_t b,s32_t ms_delay, u8_t times){
    color.r = r;
    color.g = g;
    color.b = b;
    delay = ms_delay;
    count = times;


    thread_id = k_thread_create(&neo_pixel_thread_data,
        data_pixel_stack,
        K_THREAD_STACK_SIZEOF(data_pixel_stack),
        neo_pixel_thread,NULL,NULL,NULL,
        DATA_NEO_PIXEL_PRIORITY,0,K_NO_WAIT);
}
