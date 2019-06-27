
#include <zephyr.h>
#include <device.h>
#include <disk_access.h>
#include <logging/log.h>
#include <fs.h>
#include <ff.h>
#include <stdio.h>

#include "store.h"

LOG_MODULE_REGISTER(DATA_STORE);

static FATFS fat_fs;
/* mounting info */
static struct fs_mount_t mp = {
    .type = FS_FATFS,
    .fs_data = &fat_fs,
};

// static const char *disk_mount_pt = "/SD:";
static struct header_t m_header;
static struct fs_file_t *m_file;
//

bool m_start_session = false;


int file_store_init(){
    static const char *disk_pdrv = "SD";
    if (disk_access_init(disk_pdrv) != 0)
    {
        LOG_ERR("Storage init ERROR!");
        return -EINVAL;
    }
    return 0;
}


int start_session(const char* name,const char* token)
{
    struct header_t *header = &m_header;
    strncpy(header->token,token,strlen(token));

    header->magic[0] = 0x10;
    header->magic[1] = 0x12;
    header->magic[2] = 0xe;
    header->magic[3] = 0x15;

    header->version = DATA_CAPTURE_0_1;
    header->size = sizeof(struct header_t) - sizeof(u16_t);

    char file[250];
    sprintf(file,"%s.cap");
    if (fs_open(m_file, file))
    {
        LOG_ERR("Failed to Open file!");
        return -EINVAL;
    }
    fs_write(m_file,header,sizeof(struct header_t));
    m_start_session = true;
    return 0;
}


void close_session()
{
    m_start_session = false;
    fs_close(m_file);
}

void push_payload(struct sensor_value *value, enum payload_type type)
{
    u16_t llength = 0;
    switch (type)
    {
    case ACC_XYZ:
    case GYRO_XYZ:
        llength = sizeof(struct sensor_value) * 3 + sizeof(enum payload_type);
        fs_write(m_file,&llength,sizeof(u16_t));
        fs_write(m_file,&type,sizeof(enum payload_type));
        fs_write(m_file,&value[0],sizeof(struct sensor_value));
        fs_write(m_file,&value[1],sizeof(struct sensor_value));
        fs_write(m_file,&value[2],sizeof(struct sensor_value));
        break;
    default:
        break;
    }
}
