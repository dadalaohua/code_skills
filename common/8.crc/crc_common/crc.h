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
    u8 poly;            //����ʽ
    u8 InitValue;       //��ʼֵ
    u8 xor;             //������ֵ
    BOOL InputReverse;
    BOOL OutputReverse;
}CRC_8;

typedef struct
{
    u16 poly;           //����ʽ
    u16 InitValue;      //��ʼֵ
    u16 xor;            //������ֵ
    BOOL InputReverse;
    BOOL OutputReverse;
}CRC_16;

typedef struct
{
    u32 poly;           //����ʽ
    u32 InitValue;      //��ʼֵ
    u32 xor;            //������ֵ
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
