#ifndef SMART_UP_ICM20948__h
#define SMART_UP_ICM20948__h

#include <zephyr.h>
#include <device.h>
#include <sensor.h>

#define ICM_20948_DEVICE DT_TDK_ICM20948_0_LABEL

int init_icm20948();
inline int retrieve_acc(struct sensor_value* value);
inline int retrieve_gyro(struct sensor_value* value);
#endif