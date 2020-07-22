#include "malloc.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/ 
//内存管理控制器
struct _m_mallco_dev mallco_dev=
{
    mem_init,   //内存初始化
    mem_perused,//内存使用率
    0,          //内存池
    0,          //内存管理状态表
    0,          //内存管理未就绪
};

//复制内存
//*des:目的地址
//*src:源地址
//n:需要复制的内存长度(字节为单位)
void mymemcpy(void *des, void *src, unsigned int n)  
{  
    unsigned char *xdes = des;
    unsigned char *xsrc = src;
    
    while(n--)
        *xdes++ = *xsrc++;
}

//设置内存
//*s:内存首地址
//c :要设置的值
//count:需要设置的内存大小(字节为单位)
void mymemset(void *s, unsigned char c, unsigned int count)  
{  
    unsigned char *xs = s;
    
    while(count--)
        *xs++ = c;
}

//计算分配的大小
//ptr:内存首地址 
unsigned int mem_offset(void *ptr)
{  
    unsigned int offset;
    
    if(ptr == NULL)
        return 0;//地址为0.
    
    offset = (unsigned int)ptr - (unsigned int)&mallco_dev.membase;  
    
    if(offset < MAX_MEM_SIZE)//偏移在内存池内. 
    {  
        int index = offset / MEM_BLOCK_SIZE;    //偏移所在内存块号码
        int nmemb = mallco_dev.memmap[index];   //内存块数量
        
        return nmemb * MEM_BLOCK_SIZE;  
    }
    else
        return 0;//偏移超区了.    
}

//内存管理初始化  
void mem_init(void)  
{  
    mymemset(mallco_dev.membase, 0, sizeof(mallco_dev.membase));//内存池素有数据清零  
    mallco_dev.memrdy = 1;//内存管理初始化OK  
}

//获取内存使用率
//返回值:使用率(0~100)
unsigned char mem_perused(void)  
{  
    unsigned short used=0;
    unsigned int i;
    
    for(i = 0; i < MEM_ALLOC_TABLE_SIZE; i++)  
    {  
        if(mallco_dev.memmap[i])
            used++; 
    }
    
    return (used * 100 / (MEM_ALLOC_TABLE_SIZE));  
}

//内存分配(内部调用)
//size:要分配的内存大小(字节)
//返回值:0XFFFFFFFF,代表错误;其他,内存偏移地址 
unsigned int mem_malloc(unsigned int size)  
{  
    signed long offset = 0;
    unsigned short nmemb; //需要的内存块数  
    unsigned short cmemb = 0;//连续空内存块数
    unsigned int i;
    
    if(!mallco_dev.memrdy)
        mallco_dev.init();//未初始化,先执行初始化 
    
    if(size == 0)
        return 0XFFFFFFFF;//不需要分配
    
    nmemb = size/MEM_BLOCK_SIZE;   //获取需要分配的连续内存块数
    if(size % MEM_BLOCK_SIZE)
        nmemb++;
    
    for(offset = MEM_ALLOC_TABLE_SIZE - 1; offset >= 0; offset--)//搜索整个内存控制区  
    {     
        if(!mallco_dev.memmap[offset])
            cmemb++; //连续空内存块数增加
        else
            cmemb = 0;       //连续内存块清零
        
        if(cmemb == nmemb)      //找到了连续nmemb个空内存块
        {
            for(i = 0; i < nmemb; i++)      //标注内存块非空 
            {  
                mallco_dev.memmap[offset + i] = nmemb;  
            }
            
            return (offset * MEM_BLOCK_SIZE);//返回偏移地址  
        }
    }
    
    return 0XFFFFFFFF;//未找到符合分配条件的内存块  
}

//释放内存(内部调用) 
//offset:内存地址偏移
//返回值:0,释放成功;1,释放失败;  
unsigned char mem_free(unsigned int offset)
{  
    int i;
    
    if(!mallco_dev.memrdy)//未初始化,先执行初始化
    {
        mallco_dev.init();
        return 1;//未初始化
    }
    
    if(offset < MAX_MEM_SIZE)//偏移在内存池内. 
    {  
        int index = offset / MEM_BLOCK_SIZE;    //偏移所在内存块号码
        int nmemb = mallco_dev.memmap[index];   //内存块数量
        
        for(i = 0;i < nmemb; i++)     //内存块清零
        {  
            mallco_dev.memmap[index+i] = 0;  
        }
        
        return 0;  
    }
    else
        return 2;//偏移超区了.
}

//释放内存(外部调用) 
//ptr:内存首地址 
void myfree(void *ptr)  
{  
    unsigned int offset;
    
    if(ptr == NULL)
        return;//地址为0.
    
    offset = (unsigned int)ptr - (unsigned int)&mallco_dev.membase;  
    mem_free(offset);//释放内存     
}

//分配内存(外部调用)
//size:内存大小(字节)
//返回值:分配到的内存首地址.
void *mymalloc(unsigned int size)  
{  
    unsigned int offset;
    
    offset = mem_malloc(size);
    
    if(offset == 0XFFFFFFFF)
        return NULL;  
    else
        return (void*)((unsigned int)&mallco_dev.membase + offset);  
}

//重新分配内存(外部调用)
//*ptr:旧内存首地址
//size:要分配的内存大小(字节)
//返回值:新分配到的内存首地址.
void *myrealloc(void *ptr,unsigned int size)  
{  
    unsigned int offset;
    unsigned int ptr_size;
    
    offset = mem_malloc(size);
    
    if(offset == 0XFFFFFFFF)
    {
        if(size == 0)
            myfree(ptr);

        return NULL;
    }
    else  
    {
        ptr_size = mem_offset(ptr);//原先分配的大小
        
        if(ptr_size < size)//如果原先分配的大小小于新分配大小，则只拷贝原先分配的大小的数据，避免内存越界
            mymemcpy((void*)((unsigned int)&mallco_dev.membase + offset), ptr, ptr_size);//拷贝旧内存内容到新内存   
        else
            mymemcpy((void*)((unsigned int)&mallco_dev.membase + offset), ptr, size);//拷贝旧内存内容到新内存
        
        myfree(ptr);               //释放旧内存
        
        return (void*)((unsigned int)&mallco_dev.membase + offset);          //返回新内存首地址
    }  
} 
