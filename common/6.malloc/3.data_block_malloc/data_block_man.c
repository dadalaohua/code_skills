#include <string.h>
#include "data_block_man.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
//内存管理控制器
data_block_dev_t data_block_dev=
{
    0,          //内存池
    0,          //内存管理状态表
};

//计算分配的数据内存块数量
//ptr:内存首地址 
unsigned int data_block_mem_offset(void *ptr)
{  
    unsigned int offset;
    
    if(ptr == NULL)
        return 0;//地址为0
    
    offset = (unsigned int)ptr - (unsigned int)&data_block_dev.mem_base;
    
    if(offset < DATA_BLOCK_MAX_SIZE)//偏移在内存池内.
    {  
        int index = offset / DATA_BLOCK_SIZE;    //偏移所在内存块号码
        int nmemb = data_block_dev.mem_status[index];   //内存块数量
        
        return nmemb;
    }
    else
        return 0;//偏移超区了
}

//获取剩余数据内存块数量
//返回值:剩余数据内存块数量
unsigned int data_block_mem_remain(void)
{  
    unsigned short remain = 0;
    unsigned int i;
    
    for(i = 0; i < DATA_BLOCK_TABLE_SIZE; i++)
    {  
        if(!data_block_dev.mem_status[i])
            remain++; 
    }
    
    return remain;
}

//数据内存块分配
//size:需要的数据内存块数量
//返回值:分配到的内存首地址.
void *data_block_mem_malloc(unsigned int size)
{  
    long offset = 0;
    unsigned short cmemb = 0;//连续空内存块数
    unsigned int i;
    
    if(size == 0)
        return NULL;//不需要分配
    
    for(offset = DATA_BLOCK_TABLE_SIZE - 1; offset >= 0; offset--)//搜索整个内存控制区
    {
        if(!data_block_dev.mem_status[offset])
            cmemb++;         //连续空内存块数增加
        else
            cmemb = 0;       //连续内存块清零
        
        if(cmemb == size)      //找到了连续nmemb个空内存块
        {
            for(i = 0; i < size; i++)      //标注内存块非空
            {  
                data_block_dev.mem_status[offset + i] = size;
            }
            
            return (void*)((unsigned int)&data_block_dev.mem_base + (offset * DATA_BLOCK_SIZE));//返回偏移地址
        }
    }
    
    return NULL;//未找到符合分配条件的内存块
}

//释放数据内存块
//ptr:内存首地址
void data_block_mem_free(void *ptr)
{  
    unsigned int offset;
    int i;
    
    if(ptr == NULL)
        return;
    
    offset = (unsigned int)ptr - (unsigned int)&data_block_dev.mem_base;
    
    if(offset < DATA_BLOCK_MAX_SIZE)//偏移在内存池内
    {  
        int index = offset / DATA_BLOCK_SIZE;    //偏移所在内存块号码
        int nmemb = data_block_dev.mem_status[index];   //内存块数量
        
        for(i = 0;i < nmemb; i++)     //内存块清零
        {  
            data_block_dev.mem_status[index + i] = 0;
        }
        
        return;
    }
    else
        return;//偏移超区了
}

//数据内存块初始化
void data_block_mem_init(void)
{
    memset(data_block_dev.mem_base, 0, sizeof(data_block_dev.mem_base));
}
