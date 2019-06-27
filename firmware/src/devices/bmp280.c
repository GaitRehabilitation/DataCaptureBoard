#include "bmp280.h"

static struct device* bmp280_dev;
int init_bmp280(){
    icm20948_dev = device_get_binding(ICM_20948_DEVICE);
    if(icm20948_dev == NULL){
        printk("could not init ICM20948 device");
        return -EINVAL;
    }
    printk("dev %p name %s\n", icm20948_dev, icm20948_dev->config->name);
    return 0;
}
