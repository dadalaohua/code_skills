#include <stdio.h>
#include <string.h>

#include "malloc.h"

void test1(void)
{
    unsigned char  *ptr;
    unsigned short *ptr1;
    unsigned int   *ptr2;
    unsigned int   *ptr3;

    unsigned char i;
      
    ptr = (unsigned char*)mymalloc(100);
    if(*ptr)
        i = 0;
    
    i = mem_perused();//查看使用率
    printf("内存使用率: %d\n", i);
    
    ptr1 = (unsigned short*)mymalloc(2*100);
    i = mem_perused();//查看使用率
    printf("内存使用率: %d\n", i);
    
    ptr2 = (unsigned int*)mymalloc(4*100);
    i = mem_perused();//查看使用率
    printf("内存使用率: %d\n", i);
    
    myfree(ptr); 
    i = mem_perused();//查看使用率
    printf("内存使用率: %d\n", i);
    
    ptr3 = (unsigned int*)mymalloc(4*20);
    i = mem_perused();//查看使用率
    printf("内存使用率: %d\n", i);
    
    myfree(ptr1);
    i = mem_perused();//查看使用率
    printf("内存使用率: %d\n", i);
    
    ptr = (unsigned char*)mymalloc(8*32);
    myfree(ptr2);
    i = mem_perused();//查看使用率
    printf("内存使用率: %d\n", i);
    
    myfree(ptr3);
    i = mem_perused();//查看使用率
    printf("内存使用率: %d\n", i);
    
    ptr = (unsigned char*)myrealloc(ptr, 10*32);
    i = mem_perused();//查看使用率
    printf("内存使用率: %d\n", i);
    
    ptr = (unsigned char*)myrealloc(ptr, 5*32);
    i = mem_perused();//查看使用率
    printf("内存使用率: %d\n", i);
    
    ptr = (unsigned char*)myrealloc(ptr, 0);
    i = mem_perused();//查看使用率
    printf("内存使用率: %d\n", i);
    
    if(i)
        i = 0;
}

void test2(void)
{
    unsigned char  *ptr;
    unsigned char  *ptr1;
    int i;
    
    // ptr1 = (unsigned char*)mymalloc(5*32);
    // memset(ptr1, 5, 5*32);
    // myfree(ptr1);
    
    ptr = (unsigned char*)mymalloc(2*32);
    
    memset(ptr, 1, 2*32);
    
    printf("data1:\n");
    
    for(i = 0; i < 2*32; i++)
    {
        if(i % 16 == 0)
            printf("\n");
            
        printf("%d ", *(ptr + i));
    }
    
    printf("\n");

    ptr = (unsigned char*)myrealloc(ptr, 3*32);
    
    printf("data2:\n");
    
    for(i = 0; i < 3*32; i++)
    {
        if(i % 16 == 0)
            printf("\n");
            
        printf("%d ", *(ptr + i));
    }
    
    printf("\n");

    ptr = (unsigned char*)myrealloc(ptr, 1*32);
    
    printf("data3:\n");
    
    for(i = 0; i < 1*32; i++)
    {
        if(i % 16 == 0)
            printf("\n");
            
        printf("%d ", *(ptr + i));
    }
    
    printf("\n");

    ptr = (unsigned char*)myrealloc(ptr, 0);

    if(ptr == NULL)
        printf("end success\n");
    else
        printf("end failed\n");
}

int main(int argc, char* argv[])
{ 
    test1();
    test2();
     
    return 0;
}