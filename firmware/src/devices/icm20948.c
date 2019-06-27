#include "./icm20948.h"
#include <zephyr.h>
#include <sensor.h>

static struct device* icm20948_dev;
int init_icm20948(){
    icm20948_dev = device_get_binding(ICM_20948_DEVICE);
    if(icm20948_dev == NULL){
        printk("could not init ICM20948 device");
        return -EINVAL;
    }
    printk("dev %p name %s\n", icm20948_dev, icm20948_dev->config->name);
    return 0;
}

inline int icm20948_retrieve_acc(struct sensor_value* value){
    if(sensor_channel_get(icm20948_dev, SENSOR_CHAN_ACCEL_XYZ, &value)){
        return -EINVAL;
    }
    return 0;
}
inline int icm20948_retrieve_gyro(struct sensor_value* value){
    if(sensor_channel_get(icm20948_dev, SENSOR_CHAN_GYRO_XYZ, &value)){
        return -EINVAL;
    }
    return 0;
}