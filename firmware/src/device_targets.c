#include "device_targets.h"
#include <sensor.h>
#include <led_strip.h>
#include <pwm.h>

#include <logging/log.h>
LOG_MODULE_REGISTER(BIND_DEVICE_TARGETS);


static struct device* bmp280_dev;
static struct device* icm20948_dev;
static struct device* neo_pixel_dev;
static struct device* pwm_device;

int init_bme280(){
    bmp280_dev = device_get_binding(BME280_DEVICE);
    if(bmp280_dev == NULL){
        LOG_ERR("could not init ICM20948 device");
        return -EINVAL;
    }
    LOG_INF("dev %p name %s\n", bmp280_dev, bmp280_dev->config->name);
    return 0;
}

int init_icm20948(){
    icm20948_dev = device_get_binding(ICM_20948_DEVICE);
    if(icm20948_dev == NULL){
        LOG_ERR("could not init ICM20948 device");
        return -EINVAL;
    }
    LOG_INF("dev %p name %s", icm20948_dev, icm20948_dev->config->name);
    return 0;
}

int init_neo_pixel(){
    neo_pixel_dev = device_get_binding(NEO_STRIP_DEVICE);
    if(neo_pixel_dev == NULL){
        LOG_ERR("could not get neo_pixel device");
		return -EINVAL;    
	}
    LOG_INF("dev %p name %s\n", neo_pixel_dev, neo_pixel_dev->config->name);
    return 0;
}


int init_pwm(){
    pwm_device = device_get_binding(PWM_DEVICE);
    if(pwm_device == NULL){
        LOG_ERR("Could not get buzzer device");
        return -EINVAL;
    }
    LOG_INF("dev %p name %s\n", pwm_device, pwm_device->config->name);
    return 0;
}

int bme280_retrieve_ambient_temp(struct sensor_value* value){
    if(sensor_channel_get(bmp280_dev, SENSOR_CHAN_AMBIENT_TEMP, value)){
        return -EINVAL;
    }
    return 0;
}

int bme280_retrieve_pressure(struct sensor_value* value){
    if(sensor_channel_get(bmp280_dev, SENSOR_CHAN_PRESS, value)){
        return -EINVAL;
    }
    return 0;
}

int bme280_retrieve_humidity(struct sensor_value* value){
    if(sensor_channel_get(bmp280_dev, SENSOR_CHAN_HUMIDITY, value)){
        return -EINVAL;
    }
    return 0;
}

int set_pixel_color(u8_t r,u8_t g, u8_t b){
    static struct led_rgb neo_pixel_color[1];
	neo_pixel_color[0].r = r;
	neo_pixel_color[0].g = g;
	neo_pixel_color[0].b = b;
	led_strip_update_rgb(neo_pixel_dev, neo_pixel_color, 1);
    return 0;
}

int icm20948_sample_fetch(){
	if(sensor_sample_fetch(icm20948_dev)){
        LOG_ERR("failed to fetch ICM20948");
        return -EINVAL;
    }
    return 0;
}

int icm20948_retrieve_acc(struct sensor_value* value){
    if(sensor_channel_get(icm20948_dev, SENSOR_CHAN_ACCEL_XYZ, value)){
        LOG_ERR("failed to get sensor channel ACC_XYZ");
        return -EINVAL;
    }
    return 0;
}
int icm20948_retrieve_gyro(struct sensor_value* value){
    if(sensor_channel_get(icm20948_dev, SENSOR_CHAN_GYRO_XYZ, value)){
        LOG_ERR("failed to get sensor channel GYRO_XYZ");
        return -EINVAL;
    }
    return 0;
}

int set_buzzer_pwm(int pulse_width){
    if(pwm_pin_set_usec(pwm_device,PWM_CHANNEL_BUZZER,PWM_PERIOD,pulse_width)){
        LOG_ERR("pwm pin set failed");
        return -EINVAL;
    }
    return 0;
}