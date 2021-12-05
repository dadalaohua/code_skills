#ifndef __MEMORY_H__
#define __MEMORY_H__

#include "stdio.h"

/*************************/
typedef unsigned char       uint8_t;
typedef unsigned short      uint16_t;
typedef unsigned int        uint32_t;
/*************************/

//用户使用
typedef struct
{
    void    *addr;      //申请到的内存的起始地址
    uint32_t size;      //申请到的内存的大小，按照块大小分配，大于等于申请大小
    uint16_t  tb;        //申请表序号，申请内存时分配，释放内存时使用，用户不使用
}DMEM;
//若返回空，则申请失败
DMEM *DynMemGet(uint32_t size);

void DynMemPut(DMEM *pDmem);

#endif //__MEMORY_H__