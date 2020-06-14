#include <stdio.h>

//共用体的特点是，使用类型最大的那个类型作为共用体的大小
//所以，char b 使用的是 int a的空间大小，判断 b的值，也就是判断低地址的数据值。
int checkCPU(void)  
{  
    union
    {  
        int a;
        char b;
    }c;
    c.a = 1;
    return (c.b == 1);//若是Little_endian则返回1,Big_endian则返回0；
}

//指针类型转换，最后取 char * 指针的值，也就是判断 int 低地址的数据是否为1。
int checkCPU_2(void)  
{  
    int i = 1;
    
    if(*(char *)&i == 1)
        return 1;//Little-endian
    else
        return 0;//Big-endian
}

//直接指针操作，原理也是取 int 低地址判断里面的数据。
int checkCPU_3(void)  
{  
    int a = 0x44332211;
    char *b = (char *)&a;

    if(*b == 0x11)
        return 1;//Little-endian
    else
        return 0;//Big-endian

    return 0;
}

int main(int argc, char* argv[])
{ 
    if(checkCPU())  
        printf("Little endian\n"); 
    else  
        printf("Big endian\n"); 
    
    if(checkCPU_2())  
        printf("Little endian\n"); 
    else  
        printf("Big endian\n");
    
    if(checkCPU_3())  
        printf("Little endian\n"); 
    else  
        printf("Big endian\n"); 
    
    return 0;
}