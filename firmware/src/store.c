
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

// static const char *disk_mount_pt = "/SD:";
static struct header_payload_block m_header_block;

// data blocks saved
static struct block_t m_blocks[BLOCK_QUEUE_SIZE];
static u16_t m_block_first = 0;
static u16_t m_block_end = 0;
// 

char m_file_name[100];
bool m_start_session = false;

struct header_payload* getHeader(){
    return &_header_block;
}

void start_sessions(char token[50], char file_name[100]){
    struct header_payload* header = &m_header_block.payload;

    strncpy(m_file_name,file_name,100);
    strncpy(header->token,token,50);
    
    header->magic[0] = 0x10;
    header->magic[1] = 0x12;
    header->magic[2] = 0xe;
    header->magic[3] = 0x15;

    header->version = DATA_CAPTURE_0_1;
}


void write_blocks(){
    static const char *disk_pdrv = "SD";
    if (disk_access_init(disk_pdrv) != 0) {
			LOG_ERR("Storage init ERROR!");
        return;
    }
    struct fs_file_t* file;
    if(fs_open(file,m_file_name)){
        LOG_ERR("Failed to Open file!");
        return;
    }


    struct block_t* blk = NULL;
    while(true)
    {
        u16_t current = m_block_first;
        if(current >= BLOCK_QUEUE_SIZE)
            current = 0;
        if(current != m_block_end){
            struct block_t* current_block = &m_blocks[current];
            fs_write(file,current, sizeof(struct block_t));
            //use memset to clear the block
            memset(current_block,0,sizeof(struct block_t));
            m_block_first = current;
        }
        else {
            break;
        }
        current++;
    }
}

inline bool is_block_full(struct block_t* block){
    if(block->count >= DATA_DIM){
        return true;
    }
    return false;
}

struct block_t* get_block(){
    struct block_t* result = &m_blocks[m_block_end];
    if(is_block_full(result)){
        u16_t next = m_block_end;
        next++;
        if(next >= BLOCK_QUEUE_SIZE)
            next = 0;
        if(next == m_block_first){
            return -EINVAL;
        }
        m_block_end = next;
        result = &m_blocks[m_block_end];
    }
    return result;
}

void push_payload(struct sensor_value* value, enum payload_type type){
    struct block_t* block = &m_blocks[m_block_first];
    switch (type)
    {
        case ACC_XYZ:
            struct data_t* data = &block->payload[block->count];
            data->value[0] = value[0];
            data->value[1] = value[1];
            data->value[2] = value[2];
            data->type = ACC_XYZ;
            block->count++;
            break;
        case GYRO_XYZ:
            struct data_t* data = &block->payload[block->count];
            data->value[0] = value[0];
            data->value[1] = value[1];
            data->value[2] = value[2];
            data->type = GYRO_XYZ;
            block->count++;
            break;
    default:
        break;
    }

}
