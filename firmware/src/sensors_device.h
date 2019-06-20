#ifndef SMART_UP_SENSORS_DEVICE__H
#define SMART_UP_SENSORS_DEVICE__H

#include <zephyr.h>
#include <device.h>

#include <misc/util.h>

#define BME280_DEVICE DT_BOSCH_BME280_0_LABEL
#define ICM20948_DEVICE DT_TDK_ICM20948_0_LABEL

#define PWM_PERIOD (USEC_PER_SEC / 50U)
#define PWM_DRIVER DT_NORDIC_NRF_PWM_BUZZER_LABEL
#define PWM_CHANNEL DT_NORDIC_NRF_PWM_BUZZER_CH0_PIN

#if defined(CONFIG_WS2812_STRIP)
	#define NEO_STRIP_DEVICE DT_WORLDSEMI_WS2812_0_LABEL
#else
	#define NEO_STRIP_DEVICE CONFIG_WS2812B_SW_NAME
#endif

struct sensor_configuration
{
    struct device* icm20948;
    struct device* bme280;
    struct device* neo_pixel;
    struct device* buzzer;
    int buzzer_pin;
};

struct sensor_configuration* configure_sensors();

#endif