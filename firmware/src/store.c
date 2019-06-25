
#include <zephyr.h>
#include <device.h>
#include <disk_access.h>
#include <logging/log.h>
#include <fs.h>
#include <ff.h>

#include "store.h"

LOG_MODULE_REGISTER(DATA_STORE);

static FATFS fat_fs;
/* mounting info */
static struct fs_mount_t mp = {
	.type = FS_FATFS,
	.fs_data = &fat_fs,
};

static const char *disk_mount_pt = "/SD:";

static struct header_payload_block _header_block;


struct header_payload* getHeader(){
    return &_header_block;
}

void start_sessions(char token[50]){

}

void push_payload(struct sensor_value* value){

}
