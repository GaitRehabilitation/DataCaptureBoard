
#include <zephyr.h>
#include <device.h>
#include <disk_access.h>
#include <logging/log.h>
#include <fs/fs.h>
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
static struct fs_file_t *m_file = NULL;
//

bool m_start_session = false;

static const char *disk_mount_pt = "/SD:";

int file_store_init(){

    do {
		static const char *disk_pdrv = "SD";
		u64_t memory_size_mb;
		u32_t block_count;
		u32_t block_size;
		if (disk_access_init(disk_pdrv) != 0) {
			LOG_ERR("Storage init ERROR!");
			break;
		}

		if (disk_access_ioctl(disk_pdrv,
				DISK_IOCTL_GET_SECTOR_COUNT, &block_count)) {
			LOG_ERR("Unable to get sector count");
			break;
		}
		LOG_INF("Block count %u", block_count);

		if (disk_access_ioctl(disk_pdrv,
				DISK_IOCTL_GET_SECTOR_SIZE, &block_size)) {
			LOG_ERR("Unable to get sector size");
			break;
		}
		printk("Sector size %u\n", block_size);

		memory_size_mb = (u64_t)block_count * block_size;
		printk("Memory Size(MB) %u\n", (u32_t)memory_size_mb>>20);
	} while (0);
    
    mp.mnt_point = disk_mount_pt;
    int res = fs_mount(&mp);
    if(res == FR_OK){
        printk("Disk mounted.\n");
    }
    else
    {
        printk("Error mounting disk.\n");
    }
    

    return 0;
}


int start_session(const char* name,const char* token)
{
    struct header_t *header = &m_header;
    // don't include \0 character 
    strncpy(header->token,token,10);

    header->magic[0] = 0x10;
    header->magic[1] = 0x12;
    header->magic[2] = 0xe;
    header->magic[3] = 0x15;

    header->version = DATA_CAPTURE_0_1;
    header->size = sizeof(struct header_t) - sizeof(u16_t);

    char file[250];
    sprintf(file,"%s.cap",name);
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
    m_file = NULL;
}

void push_payload(struct sensor_value *value, enum payload_type type)
{
    if(!m_file){
        return;
    }
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
    case ACC_GYRO_XYZ:
        llength = sizeof(struct sensor_value) * 6 + sizeof(enum payload_type);
        fs_write(m_file,&llength,sizeof(u16_t));
        fs_write(m_file,&type,sizeof(enum payload_type));
        fs_write(m_file,&value[0],sizeof(struct sensor_value));
        fs_write(m_file,&value[1],sizeof(struct sensor_value));
        fs_write(m_file,&value[2],sizeof(struct sensor_value));
        fs_write(m_file,&value[3],sizeof(struct sensor_value));
        fs_write(m_file,&value[4],sizeof(struct sensor_value));
        fs_write(m_file,&value[5],sizeof(struct sensor_value));
        break;
    default:
        break;
    }

}
