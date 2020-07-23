#ifndef __DATA_BLOCK_MAN_H
#define __DATA_BLOCK_MAN_H

/************************************************************************/
/*                                                                      */
/************************************************************************/

#ifndef NULL
#define NULL 0
#endif

#define DATA_BLOCK_SIZE         48                                      //数据内存块大小为48字节
#define DATA_BLOCK_TABLE_SIZE   60                                      //数据内存表大小
#define DATA_BLOCK_MAX_SIZE     (DATA_BLOCK_TABLE_SIZE*DATA_BLOCK_SIZE) //数据内存块最大管理内存

//数据内存块管理控制器
typedef struct 
{
    unsigned char  mem_base[DATA_BLOCK_MAX_SIZE];       //数据内存块内存池
    unsigned short mem_status[DATA_BLOCK_TABLE_SIZE];   //数据内存块内存管理状态表
} data_block_dev_t;

/************************************************************************/
/*                                                                      */
/************************************************************************/
void data_block_mem_init(void);                     //数据内存块初始化
void *data_block_mem_malloc(unsigned int size);     //数据内存块分配
void data_block_mem_free(void *ptr);                //释放数据内存块
unsigned int data_block_mem_remain(void);           //获取剩余数据内存块数量
unsigned int data_block_mem_offset(void *ptr);      //获取分配的数据内存块数量
   
#endif