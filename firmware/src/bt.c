#include "bt.h"

#include "gatt/battery_gatt.h"
#include "gatt/data_logger_gatt.h"

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



static struct bt_conn *default_conn;


static const struct bt_data ad[] = {
	BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
	BT_DATA_BYTES(BT_DATA_UUID16_ALL, 0x0d, 0x18, 0x0f, 0x18, 0x05, 0x18),
};


static void connected(struct bt_conn *conn, u8_t err)
{
	if (err) {
		printk("Connection failed (err %u)\n", err);
	} else {
		default_conn = bt_conn_ref(conn);
		printk("Connected\n");
	}
}

static void disconnected(struct bt_conn *conn, u8_t reason)
{
	printk("Disconnected (reason %u)\n", reason);

	if (default_conn) {
		bt_conn_unref(default_conn);
		default_conn = NULL;
	}
}

static struct bt_conn_cb conn_callbacks = {
	.connected = connected,
	.disconnected = disconnected,
};


static void bt_ready(int err){
    if(err) {
        printk("Bluetooth init failed (err %d)\n", err);
        return;
    }

    printk("Bluetooth Initialized\n");

    batt_gatt_init();
    data_logger_gatt_init();

    err = bt_le_adv_start(BT_LE_ADV_CONN_NAME,ad,ARRAY_SIZE(ad),NULL,0);
    if(err) {
        printk("Advertizing failed to start (err %d)\n", err);
        return;
    }

    printk("Advertizing successfully started\n");
}

int bluetooth_init(){
    int err = bt_enable(bt_ready);
    if(err){
        printk("Bluetooth init failed (err %d)\n",err);
        return -EINVAL;
    }

	bt_conn_cb_register(&conn_callbacks);
}