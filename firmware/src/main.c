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
// LOG_MODULE_REGISTER(MAIN_INIT);

void main(void)
{
	printk("start init");
	init_pwm();
	init_bme280();
	init_icm20948();
	init_neo_pixel();
	init_pwm();
	bluetooth_init();
	file_store_init();
	printk("end init");
}
