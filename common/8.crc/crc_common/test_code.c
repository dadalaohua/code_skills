#include <stdio.h>
#include "crc.h"

unsigned char test_arr[]={
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f, 
    0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 
    0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f, 
    0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 
    0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f, 
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 
    0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f, 
    0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 
    0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf, 
    0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 
    0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf, 
    0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef, 
    0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff
};

unsigned char test_arr2[258];

void display_menu(void)
{
    printf("/*************************/\n");
    printf("/*********CRC TEST********/\n");
    printf("/*************************/\n");
    printf("1.  CRC-8\n");
    printf("2.  CRC-8/ITU\n");
    printf("3.  CRC-8/ROHC\n");
    printf("4.  CRC-8/MAXIM\n");
    printf("\n");
    printf("5.  CRC-16/IBM\n");
    printf("6.  CRC-16/MAXIM\n");
    printf("7.  CRC-16/USB\n");
    printf("8.  CRC-16/MODBUS\n");
    printf("9.  CRC-16/CCITT\n");
    printf("10. CRC-16/CCITT-FALSE\n");
    printf("11. CRC-16/X25\n");
    printf("12. CRC-16/XMODEM\n");
    printf("13. CRC-16/DNP\n"); 
    printf("\n");
    printf("14.  CRC-32\n");
    printf("15.  CRC-32/MPEG2\n");
    printf("\n");
    printf("/*************************/\n");
}

CRC_8 crc8_switch(int index)
{
    switch(index)
    {
        case 1:
        {
            return crc_8;
        }
        break;
        
        case 2:
        {
            return crc_8_ITU;
        }
        break;
        
        case 3:
        {
            return crc_8_ROHC;
        }
        break;
        
        case 4:
        {
            return crc_8_MAXIM;
        }
        break;
    }
    
    return crc_8;
}

CRC_16 crc16_switch(int index)
{
    switch(index)
    {
        case 5:
        {
            return crc_16_IBM;
        }
        break;
        
        case 6:
        {
            return crc_16_MAXIM;
        }
        break;
        
        case 7:
        {
            return crc_16_USB;
        }
        break;
        
        case 8:
        {
            return crc_16_MODBUS;
        }
        break;
        
        case 9:
        {
            return crc_16_CCITT;
        }
        break;
        
        case 10:
        {
            return crc_16_CCITT_FALSE;
        }
        break;
        
        case 11:
        {
            return crc_16_X25;
        }
        break;
        
        case 12:
        {
            return crc_16_XMODEM;
        }
        break;
        
        case 13:
        {
            return crc_16_DNP;
        }
        break;
    }
    
    return crc_16_IBM;
}

CRC_32 crc32_switch(int index)
{
    switch(index)
    {
        case 14:
        {
            return crc_32;
        }
        break;
        
        case 15:
        {
            return crc_32_MPEG2;
        }
        break;
    }
    
    return crc_32;
}

void menu_switch(int index)
{
    int i;
    printf("index %d\n",index);
    
    if(index >= 1 && index <= 4)
    {
        CRC_8 CRC_8_temp;
        //计算crc
        unsigned char crc;
        
        CRC_8_temp = crc8_switch(index);
        crc = crc8(test_arr, sizeof(test_arr), CRC_8_temp);
        
        printf("crc : 0x%x\n", crc);
        
        //生成表格
        CRC_8_temp.InitValue = 0x00;
        CRC_8_temp.xor       = 0x00;
    
        for(i = 0; i < sizeof(test_arr); i++)
        {
            if(i%8 == 0)
                printf("\n");
            
            printf("0x%.2x, ", crc8(&test_arr[i], 1, CRC_8_temp));
        }
        printf("\n");
    }
    else if(index >= 5 && index <= 13)
    {
        CRC_16 CRC_16_temp;
        //计算crc
        unsigned short crc;
        
        CRC_16_temp = crc16_switch(index);
        crc = crc16(test_arr, sizeof(test_arr), CRC_16_temp);
        
        printf("crc : 0x%x\n", crc);
        
        //生成表格
        CRC_16_temp.InitValue = 0x00;
        CRC_16_temp.xor       = 0x00;
        
        for(i = 0; i < sizeof(test_arr); i++)
        {
            if(i%8 == 0)
                printf("\n");
            
            printf("0x%.4x, ", crc16(&test_arr[i], 1, CRC_16_temp));
        }
        printf("\n");
    }
    else if(index >= 14 && index <= 15)
    {
        CRC_32 CRC_32_temp;
        unsigned int crc;
        
        CRC_32_temp = crc32_switch(index);
        crc = crc32(test_arr, sizeof(test_arr), CRC_32_temp);
        
        printf("crc : 0x%x\n", crc);
        
        //生成表格
        CRC_32_temp.InitValue = 0x00;
        CRC_32_temp.xor       = 0x00;
        
        for(i = 0; i < sizeof(test_arr); i++)
        {
            if(i%8 == 0)
                printf("\n");
            
            printf("0x%.8x, ", crc32(&test_arr[i], 1, CRC_32_temp));
        }
        printf("\n");
    }
}

int main(int argc, char* argv[])
{ 
    int index;

    display_menu();
    scanf("%d", &index);
    menu_switch(index);
    
    return 0;
}