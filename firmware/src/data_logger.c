#include "data_logger.h"
#include <store.h>

#define DATA_LOGGER_STACK_SIZE 500
#define DATA_LOGGER_PRIORITY 5

static k_tid_t thread_id = NULL;
static struct k_thread data_logger_thread_data;

K_THREAD_STACK_DEFINE(data_logger_stack,DATA_LOGGER_STACK_SIZE)

static volatile u8_t is_logging = false;


extern void logging_thread(void *, void *, void *){
    is_logging = true;
    while(true){
    } 
    is_logging = false;
}

int start_logging(const char* name, const char* token) {
    
    if(is_logging == false){ 
        start_session(name,token);
           
        k_tid_t = k_thread_create(&data_logger_thread_data,
            data_logger_stack,
            K_THREAD_STACK_SIZEOF(data_logger_stack),
            logging_thread,NULL,NULL,NULL,
            DATA_LOGGER_PRIORITY,0,K_NO_WAIT);
        return 0;
    }
    return -EINVAL;
}

