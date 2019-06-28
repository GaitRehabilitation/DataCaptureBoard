#include "data_logger_gatt.h"

#include <zephyr/types.h>
#include <stddef.h>
#include <string.h> 
#include <errno.h>
#include <misc/printk.h>
#include <misc/byteorder.h>
#include <zephyr.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/conn.h>
#include <bluetooth/uuid.h>
#include <bluetooth/gatt.h>

#define DATA_LOGGER_UUID BT_UUID_DECLARE_128({0x08,0xd4,0xce,0xbd,0xb9,0xd4,0x4d,0x22,0xaf,0x96,0x0f,0x1e,0xd2,0x48,0xd4,0xcb})
#define BT_UUID_LOGGER_CONFIGURATION BT_UUID_DECLARE_128({0x0a,0xea,0x63,0xdc,0xaf,0x80,0x45,0x71,0x8d,0x31,0x0c,0x5d,0x01,0x84,0x9e,0x6b})
#define DATA_LOGGER_STOP_SESSION_UUID BT_UUID_DECLARE_128({0x35,0x4f,0x2d,0x00,0x66,0x39,0x46,0x89,0xa3,0x98,0xfb,0x5c,0xec,0xf4,0x9d,0xe0})

static struct session_config m_config;

static struct start_session m_session_start_ptr;

static ssize_t write_start_session(){

}

static ssize_t write_stop_session(struct bt_conn *conn, const struct bt_gatt_attr *attr,
     void *buf, u16_t len, u16_t offset){


}



BT_GATT_SERVICE_DEFINE(logger_gatt,
    BT_GATT_PRIMARY_SERVICE(DATA_LOGGER_UUID),
    BT_GATT_CHARACTERISTIC(BT_UUID_LOGGER_STATUS,
        BT_GATT_CHRC_WRITE_WITHOUT_RESP,
        BT_GATT_PERM_WRITE,
        NULL,write_start_session,&m_session_start_ptr),
    // BT_GATT_CHARACTERISTIC(DATA_LOGGER_STOP_SESSION_UUID,
    //     BT_GATT_CHRC_WRITE_WITHOUT_RESP,
    //     BT_GATT_PERM_WRITE,
    //     NULL,write_stop_session, NULL)
);


void data_logger_gatt_init(void){

}

void data_logger_gatt_notify(void){

}