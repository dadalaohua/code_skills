#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef unsigned short  u16;
typedef unsigned int    u32;

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define swab16(x) ((u16)(				\
	(((u16)(x) & (u16)0x00ffU) << 8) |			\
	(((u16)(x) & (u16)0xff00U) >> 8)))

#define swab32(x) ((u32)(				\
	(((u32)(x) & (u32)0x000000ffUL) << 24) |		\
	(((u32)(x) & (u32)0x0000ff00UL) <<  8) |		\
	(((u32)(x) & (u32)0x00ff0000UL) >>  8) |		\
	(((u32)(x) & (u32)0xff000000UL) >> 24)))
    
/************************************************************************/
/*                                                                      */
/************************************************************************/
int checkCPUendian(void)  
{  
    int i = 1;
    
    if(*(char *)&i == 1)
        return 1;//Little-endian
    else
        return 0;//Big-endian
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
//网络字节顺序到主机字节顺序 n代表net, h代表host, s代表short
//若本机为小端，网络数据转换成小端再返回
//若本机为大端，与网络字节序同，直接返回
unsigned short int ntohs(unsigned short int netshort)
{
    return checkCPUendian() ? swab16(netshort) : netshort;
}

//主机字节顺序到网络字节顺序 n代表net, h代表host, s代表short
//若本机为小端，转换成大端再返回
//若本机为大端，与网络字节序同，直接返回
unsigned short int htons(unsigned short int netshort)
{
    return checkCPUendian() ? swab16(netshort) : netshort;
}

//网络字节顺序到主机字节顺序 n代表net, h代表host, l代表 long
//若本机为小端，网络数据转换成小端再返回
//若本机为大端，与网络字节序同，直接返回
unsigned long int ntohl(unsigned long int netlong)
{
       return checkCPUendian() ? swab32(netlong) : netlong;
}

//主机字节顺序到网络字节顺序n代表net, h代表host, l代表 long
//若本机为小端，转换成大端再返回
//若本机为大端，与网络字节序同，直接返回
unsigned long int htonl(unsigned long int netlong)
{
    return checkCPUendian() ? swab32(netlong) : netlong;
}

/****************************/

int main(int argc, char* argv[])
{
    u16 u16val = 0x5f3b;
    u32 u32val = 0x5f3b3a61;

    printf("u16val 0x%x\n", u16val);
    printf("ntohs 0x%x\n", ntohs(u16val));
    printf("htons 0x%x\n", htons(u16val)); 

    printf("u32val 0x%x\n", u32val);
    printf("ntohl 0x%lx\n", ntohl(u32val));
    printf("htonl 0x%lx\n", htonl(u32val));
    
    return 0;
}