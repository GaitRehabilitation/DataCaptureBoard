#include <errno.h>
#include <string.h>

#include <zephyr.h>
#include <device.h>
#include <sensor.h>
#include <stdio.h>
#include <misc/util.h>

// #include "neo_pixel.h"
#include "store.h"
#include <logging/log.h>
LOG_MODULE_REGISTER(main);

void main(void)
{
	// set_pixel_color(20,0,0);
	// k_sleep(1000);
	// set_pixel_color(0,0,0);
	
	// struct device *dev = device_get_binding(DT_TDK_ICM20948_0_LABEL);

	// if (dev == NULL) {
	// 	printk("Could not get ICM20948 device\n");
	// 	return;
	// }

	// printf("dev %p name %s\n", dev, dev->config->name);

	// while (1) {
	// 	struct sensor_value acc[3];

	// 	sensor_sample_fetch(dev);
	// 	sensor_channel_get(dev, SENSOR_CHAN_ACCEL_XYZ, &acc);

	// 	printk("x: %d.%06d; y: %d.%06d; z: %d.%06d\n",
	// 	      acc[0].val1, acc[0].val2, acc[1].val1, acc[1].val2,
	// 	      acc[2].val1, acc[2].val2);

	// 	k_sleep(500);

	// }


	// struct device *dev = device_get_binding(DT_BOSCH_BME280_0_LABEL);

	// if (dev == NULL) {
	// 	printk("Could not get BME280 device\n");
	// 	return;
	// }

	// printf("dev %p name %s\n", dev, dev->config->name);

	// while (1) {
	// 	struct sensor_value temp, press, humidity;

	// 	sensor_sample_fetch(dev);
	// 	sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &temp);
	// 	sensor_channel_get(dev, SENSOR_CHAN_PRESS, &press);
	// 	sensor_channel_get(dev, SENSOR_CHAN_HUMIDITY, &humidity);

	// 	printk("temp: %d.%06d; press: %d.%06d; humidity: %d.%06d\n",
	// 	      temp.val1, temp.val2, press.val1, press.val2,
	// 	      humidity.val1, humidity.val2);

	// 	k_sleep(1000);

	// }

	// printk("Startting ICM20948 device\n");
	// int cnt = 0;
	// char out_str[64];
	// struct sensor_value odr_attr;
	// struct device *icm20948_dev = device_get_binding(DT_TDK_ICM20948_0_LABEL);

	// if(icm20948_dev){
	// 	printk("could not get ICM20948 device\n");
	// }

	// struct sensor_value accel[3];
	

	// while (1) {
	// 	if(sensor_sample_fetch(icm20948_dev)){
	// 		printk("Sensor sample update error\n");
	// 		return;
	// 	}

		// sensor_channel_get(icm20948_dev, SENSOR_CHAN_ACCEL_XYZ, &accel);
		// printf("AX=%10.2f AY=%10.2f AZ=%10.2f (m/s^2)\n",
		// 		sensor_value_to_double(&accel[0]),
		// 		sensor_value_to_double(&accel[1]),
		// 		sensor_value_to_double(&accel[2]));
	// }
}
