#include <errno.h>
#include <string.h>

#include <zephyr.h>
#include <device.h>
#include <sensor.h>
#include <stdio.h>
#include <misc/util.h>

// #include "neo_pixel.h"
#include "store.h"
#include "device_targets.h"
#include "bt.h"
#include "store.h"
#include "data_logger.h"
// LOG_MODULE_REGISTER(MAIN_INIT);

void main(void)
{
	printk("start init \n");
	init_neo_pixel();
	set_pixel_color(0,0,20);
	file_store_init();
	init_pwm();
	init_bme280();
	init_icm20948();
	bluetooth_init();
	set_pixel_color(0,0,0);
	printk("end init");

	while (1) {
		k_sleep(MSEC_PER_SEC);
	}
}
