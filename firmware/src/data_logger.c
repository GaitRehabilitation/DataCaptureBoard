#include "data_logger.h"
#include <store.h>
#include "device_targets.h"
#include <sensor.h>

#include <logging/log.h>
LOG_MODULE_REGISTER(DATA_LOGGER);

#define DATA_LOGGER_STACK_SIZE 10000
#define DATA_LOGGER_PRIORITY 5

static k_tid_t thread_id = NULL;
static struct k_thread data_logger_thread_data;

K_THREAD_STACK_DEFINE(data_logger_stack,DATA_LOGGER_STACK_SIZE);
static volatile bool g_is_logging = false;

static void logging_thread(void * u1, void * u2, void * u3){
    // set pixel to blue to tell that the logger is logging
    set_pixel_color(0,0,20);
    s64_t start_time = k_uptime_get();

    struct sensor_value value[6];
    // LOG_INF("Started logging \n");
    while(g_is_logging == true){
        k_busy_wait((s32_t)((1.0/100.0) * 1000.0));        
        struct sensor_value* pos = value;
        icm20948_sample_fetch();
        icm20948_retrieve_acc(pos);
        pos+=3;
        icm20948_retrieve_gyro(pos);
        if(push_payload(k_uptime_delta(&start_time),value,ACC_GYRO_XYZ) < 0){
            break;
        }
    }
    store_sync();
    close_session();
    // LOG_INF("stopped logging");    
    g_is_logging = false;
    // clear when finished
    set_pixel_color(0,0,0);
}

bool is_logging(){
    return g_is_logging;
}

int stop_logging(){
    g_is_logging = false;
    return 0;
}

int start_logging(s32_t timestamp,const char* name, const char* token) {
    
    if(g_is_logging == true){
        LOG_INF("already logging");
        return -EINVAL;
    }

    if(start_session(timestamp,name,token))
        return -EINVAL;
    g_is_logging = true;
    thread_id = k_thread_create(&data_logger_thread_data,
        data_logger_stack,
        K_THREAD_STACK_SIZEOF(data_logger_stack),
        logging_thread,NULL,NULL,NULL,
        DATA_LOGGER_PRIORITY,0,K_NO_WAIT);
    return 0;
}
