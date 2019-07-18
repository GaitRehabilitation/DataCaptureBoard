#ifndef SMART_UP_DEVICE_TARGET__h
#define SMART_UP_DEVICE_TARGET__h

#include <zephyr.h>
#include <device.h>
#include <sensor.h>

#if defined(CONFIG_WS2812_STRIP)
	#define NEO_STRIP_DEVICE DT_WORLDSEMI_WS2812_0_LABEL
#else
	#define NEO_STRIP_DEVICE CONFIG_WS2812B_SW_NAME
#endif

#define ICM_20948_DEVICE DT_TDK_ICM20948_0_LABEL

#define BME280_DEVICE DT_BOSCH_BME280_0_LABEL

#if defined(CONFIG_PWM_NRF5_SW)
#define PWM_DEVICE CONFIG_PWM_NRF5_SW_0_DEV_NAME
#else
#define PWM_DEVICE DT_NORDIC_NRF_PWM_PWM_0_LABEL
#endif  /* CONFIG_PWM_NRF5_SW */
#define PWM_PERIOD (USEC_PER_SEC / 50U)
#define PWM_CHANNEL_BUZZER DT_NORDIC_NRF_PWM_BUZZER_CH0_PIN



int init_pwm();
int init_bme280();
int init_icm20948();
int init_neo_pixel();

//bme280
int bme280_retrieve_ambient_temp(struct sensor_value* value);
int bme280_retrieve_pressure(struct sensor_value* value);
int bme280_retrieve_humidity(struct sensor_value* value);

// NEO pixel
int set_pixel_color(u8_t r,u8_t g, u8_t b);

//icm_20948
int icm20948_retrieve_acc(struct sensor_value* value);
int icm20948_retrieve_gyro(struct sensor_value* value);

// buzzer
int set_buzzer_pwm(int pulse_width);

#endif