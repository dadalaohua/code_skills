#ifndef __CRC_H__
#define __CRC_H__

typedef unsigned char        u8;
typedef unsigned short       u16;
typedef unsigned int         u32;
typedef unsigned long long   u64;

typedef unsigned char        BOOL;
#define FALSE                0
#define TRUE                 1


typedef struct
{
    u8 poly;            //多项式
    u8 InitValue;       //初始值
    u8 xor;             //结果异或值
    BOOL InputReverse;
    BOOL OutputReverse;
}CRC_8;

typedef struct
{
    u16 poly;           //多项式
    u16 InitValue;      //初始值
    u16 xor;            //结果异或值
    BOOL InputReverse;
    BOOL OutputReverse;
}CRC_16;

typedef struct
{
    u32 poly;           //多项式
    u32 InitValue;      //初始值
    u32 xor;            //结果异或值
    BOOL InputReverse;
    BOOL OutputReverse;
}CRC_32;

const CRC_8 crc_8;
const CRC_8 crc_8_ITU;
const CRC_8 crc_8_ROHC;
const CRC_8 crc_8_MAXIM;

const CRC_16 crc_16_IBM;
const CRC_16 crc_16_MAXIM;
const CRC_16 crc_16_USB;
const CRC_16 crc_16_MODBUS;
const CRC_16 crc_16_CCITT;
const CRC_16 crc_16_CCITT_FALSE;
const CRC_16 crc_16_X25;
const CRC_16 crc_16_XMODEM;
const CRC_16 crc_16_DNP;

const CRC_32 crc_32;
const CRC_32 crc_32_MPEG2;

u8 crc8(u8 *addr, int num,CRC_8 type) ;
u16 crc16(u8 *addr, int num,CRC_16 type) ;
u32 crc32(u8 *addr, int num,CRC_32 type) ;

#endif
