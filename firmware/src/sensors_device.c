#include "sensors_device.h"

#include <zephyr.h>
#include <device.h>

static struct sensor_configuration config;

struct sensor_configuration* configure_sensors(){

    config.bme280 = device_get_binding(BME280_DEVICE);
    if(config.bme280 == NULL){
        printk("Could not get bme280 device\n");
    }
    config.buzzer = device_get_binding(PWM_DRIVER);
    config.buzzer_pin = PWM_CHANNEL;
    if(config.buzzer == NULL){
        printk("Could not get buzzer device\n");
    }

    config.icm20948  = device_get_binding(ICM20948_DEVICE);
    if(config.icm20948 == NULL){
        printk("could not get icm20948 device\n");
    }

    config.neo_pixel = device_get_binding(NEO_STRIP_DEVICE);
    if(config.neo_pixel){
        printk("could not get neo_pixel device\n");    
    }
    return &config;
}
