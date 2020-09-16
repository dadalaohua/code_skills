#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define BITARRAY_SHIFT  3
#define BITARRAY_MASK   0x7
 
#define BITARRAY_SIZE(size)             ((size >> BITARRAY_SHIFT) + 1)
#define BITARRAY_BYTE_INDEX(num)        (num >> BITARRAY_SHIFT)
#define BITARRAY_B_SET(array, num)        (array[BITARRAY_BYTE_INDEX(num)] |= (0x80 >> (num & BITARRAY_MASK)))
#define BITARRAY_B_CLR(array, num)        (array[BITARRAY_BYTE_INDEX(num)] &= ~(0x80 >> (num & BITARRAY_MASK)))
#define BITARRAY_B_IS_IN(array, num)      (array[BITARRAY_BYTE_INDEX(num)] & (0x80 >> (num & BITARRAY_MASK)))
#define BITARRAY_BYTE_BIT_NUM(data)     ({ data = (data & 0x55) + ((data >> 1) & 0x55);\
                                           data = (data & 0x33) + ((data >> 2) & 0x33);\
                                           data = (data & 0x0f) + ((data >> 4) & 0x0f); })
#define BITARRAY_ARRAY_BIT_NUM(array, size)     ({ unsigned int i, count = 0;\
                                                    for(i = 0; i < BITARRAY_SIZE(size); i++)\
                                                        count += BITARRAY_BYTE_BIT_NUM(array[i]);\
                                                        count;\
                                                        })

/************************************************************************/
/*                                                                      */
/************************************************************************/
//图片放大
void picture_conversion(unsigned char* src, unsigned int src_x, unsigned int src_y,
                                    unsigned char* dst, unsigned int dst_x, unsigned int dst_y)
{
    int i, j, k;

    if((dst_x > src_x) && (dst_y > src_y))
    {
        int multiple_x = dst_x/src_x;
        int multiple_y = dst_y/src_y;
        unsigned char* src_tmp = src;
        unsigned char* dst_tmp = dst;
        
        for(i = 0; i < src_y; i++)
        {
            for(j = 0; j < src_x; j++)
            {
                if(BITARRAY_B_IS_IN(src_tmp, j))
                {
                    for(k = 0; k < multiple_x; k++)
                        BITARRAY_B_SET(dst_tmp, (j * multiple_x + k));
                }
            }

            for(k = 0; k < multiple_y; k++)
            {
                memcpy(dst_tmp + (k * (dst_x/8)), dst_tmp, (dst_x/8));
            }
            
            src_tmp += (src_x/8);
            dst_tmp += (multiple_y * (dst_x/8));
        }
    }
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
unsigned char fontdata[] = {
    0x00, /* 00000000*/
    0x00, /* 00000000*/
    0x00, /* 00000000*/
    0x3c, /* 00111100*/
    0x66, /* 01100110*/
    0x42, /* 01000010*/
    0x42, /* 01000010*/
    0x42, /* 01000010*/
    0xc2, /* 01000010*/
    0x42, /* 01000010*/
    0x7a, /* 01111010*/
    0x6a, /* 01101010*/
    0x64, /* 01100100*/
    0x3c, /* 00111100*/
    0x06, /* 00000110*/
    0x00, /* 00000000*/
};

int main(int argc, char* argv[])
{ 
    int i, j, k;
    unsigned char* buff = fontdata;
    unsigned char buff_cov[128] = {0};
    unsigned char* pbuff_cov = buff_cov;
    
    for(i = 0; i < sizeof(fontdata); i++)
    {
        for(j = 0; j < 8; j++)
        {
            if(BITARRAY_B_IS_IN(buff, j))
                printf("o");
            else
                printf(".");
        }
        
        printf("\n");
        
        buff += 1;
    }
    
    buff = fontdata;
    
    picture_conversion(buff, 8, 16, buff_cov, 32, 32);
    
    for(i = 0; i < 32; i++)
    {
        for(j = 0; j < 4; j++)
        {
            for(k = 0; k < 8; k++)
            {
                if(BITARRAY_B_IS_IN(pbuff_cov, k))
                    printf("o");
                else
                    printf(".");
            }
            
            pbuff_cov += 1;
        }
        
        printf("\n");
    }
    
    return 0;
}