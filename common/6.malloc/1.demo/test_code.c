#include <stdio.h>

#include "malloc.h"

int main(int argc, char* argv[])
{ 
    unsigned char  *ptr;
    unsigned short *ptr1;
    unsigned int   *ptr2;
    unsigned int   *ptr3;

    unsigned char i;
      
    ptr=(unsigned char*)mymalloc(100);
    if(*ptr)
        i = 0;
    
    i = mem_perused();//查看使用率
    printf("内存使用率: %d\n", i);
    
    ptr1=(unsigned short*)mymalloc(2*100);
    i = mem_perused();//查看使用率
    printf("内存使用率: %d\n", i);
    
    ptr2=(unsigned int*)mymalloc(4*100);
    i = mem_perused();//查看使用率
    printf("内存使用率: %d\n", i);
    
    myfree(ptr); 
    i = mem_perused();//查看使用率
    printf("内存使用率: %d\n", i);
    
    ptr3=(unsigned int*)mymalloc(4*20);
    i = mem_perused();//查看使用率
    printf("内存使用率: %d\n", i);
    
    myfree(ptr1);
    i = mem_perused();//查看使用率
    printf("内存使用率: %d\n", i);
    
    ptr=(unsigned char*)mymalloc(8*32);
    myfree(ptr2);
    i = mem_perused();//查看使用率
    printf("内存使用率: %d\n", i);
    
    myfree(ptr3);
    i = mem_perused();//查看使用率
    printf("内存使用率: %d\n", i);
    
    if(i)
        i=0;
     
    return 0;
}