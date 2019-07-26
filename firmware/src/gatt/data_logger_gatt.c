#include "data_logger_gatt.h"

#include <zephyr/types.h>
#include <stddef.h>
#include <string.h> 
#include <errno.h>
#include <misc/byteorder.h>
#include <data_logger.h>
#include <neo_pixel.h>


#include <logging/log.h>
LOG_MODULE_REGISTER(DATA_LOGGER_GATT);

static struct session_config m_config;
static struct session_device_name m_device_name;


static ssize_t write_logger_config(struct bt_conn *conn,
				const struct bt_gatt_attr *attr,
				const void *buf, u16_t len, u16_t offset,
				u8_t flags){
    struct session_config *value = attr->user_data;
    if(offset + len > sizeof(struct session_config)){
        LOG_INF("exceeded buffer");
        return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
    }
    memcpy(value + offset,buf,len);
    LOG_INF("status: %i", value->status);
    switch(value->status){
        case START_LOGGING:
        {
            struct start_logging_payload* payload = &value->payload.start_logging;
            if(start_logging(payload->unix_time,m_device_name.name,payload->token)){
                return BT_GATT_ERR(BT_ATT_ERR_NOT_SUPPORTED);
            }
        }
            break;
        case STOP_LOGGING:
            if(stop_logging()){
                return BT_GATT_ERR(BT_ATT_ERR_NOT_SUPPORTED);
            }
        break;
        case PING_LOGGING:
            neo_blink(0,30,0,200,4);
        break;
        case SET_DESCRIPTION: 
        {
            // char* payload = value->payload.text_payload;
            // payload[199] = '\0';
        }
            break;
        default:{
            return BT_GATT_ERR(BT_ATT_ERR_NOT_SUPPORTED);
        }
    }
    return len;   
}


static ssize_t write_logger_name_config(struct bt_conn *conn,
				const struct bt_gatt_attr *attr,
				const void *buf, u16_t len, u16_t offset,
				u8_t flags){
    struct session_device_name *value = attr->user_data;
    memset(value,0,sizeof(struct session_device_name));
    if(offset + len - 1 > sizeof(struct session_device_name)){
        return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
    }
    memcpy(value + offset,buf,len);
    // LOG_INF("logging file name: %s", value->name);
    return len;
}

BT_GATT_SERVICE_DEFINE(logger_gatt,
    BT_GATT_PRIMARY_SERVICE(DATA_LOGGER_UUID),
    BT_GATT_CHARACTERISTIC(DATA_LOGGER_CONFIGURE_UUID,
        BT_GATT_CHRC_WRITE_WITHOUT_RESP,
        BT_GATT_PERM_WRITE,
        NULL,write_logger_config,&m_config),
    BT_GATT_CHARACTERISTIC(DATA_LOGGER_TARGET_NAME_UUID,
        BT_GATT_CHRC_WRITE_WITHOUT_RESP,
        BT_GATT_PERM_WRITE,
        NULL,write_logger_name_config,&m_device_name)
        
    // BT_GATT_CHARACTERISTIC(DATA_LOGGER_STREAM_UUID,
    //     BT_GATT_CHRC_NOTIFY | BT_GATT_CHRC_READ,
    //     BT_GATT_PERM_READ,
    //     NULL,NULL,&m_session_start_ptr),

);


void data_logger_gatt_init(void){

}

void data_logger_gatt_notify(void){

}