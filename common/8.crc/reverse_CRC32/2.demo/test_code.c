#include <stdio.h>

/**
 * add 4 bytes num[4] to change crc32 value from crc_src to crc_dst
 * @return: 0 on success, -1 on error.
 */
int crc32_reverse_byte(unsigned int crc_dst, unsigned int crc_src, unsigned char num[4])
{
    int i = 0, j = 0, k = 0;
    unsigned int tx[4];
    unsigned char value_x[4];
    unsigned int crc32_val;

    //crc_dst ==> tx[4] (get previous 4 CRC table codes)
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 256; j++)
        {
            crc32_val = 0;
            crc32_val ^= (j & 0xff);
            for (k = 0; k < 8; k++)
            {
                if (crc32_val & 1)
                    crc32_val = (crc32_val >> 1) ^ 0xEDB88320;
                else
                    crc32_val = (crc32_val >> 1);
            }
            
            if((crc32_val >> 24) == (crc_dst >> 24))
                break;
        }
        
        tx[i] = j;
 
        //previous CRC value
        crc32_val = 0;
        crc32_val ^= (tx[i] & 0xff);
        for (j = 0; j < 8; j++)
        {
            if (crc32_val & 1)
                crc32_val = (crc32_val >> 1) ^ 0xEDB88320;
            else
                crc32_val = (crc32_val >> 1);
        }
        
        crc_dst = (crc_dst ^ crc32_val) << 8;
    }
 
    //calculate last 4 unknown bytes
    for (i = 3; i >= 0; i--) {
        //unknown value x
        value_x[i] = (crc_src & 0xff) ^ tx[i];

        //calculate next CRC32: add byte value_x[i]
        crc_src ^= *(value_x + i);
        for (j = 0; j < 8; ++j)
        {
            if (crc_src & 1)
                crc_src = (crc_src >> 1) ^ 0xEDB88320;
            else
                crc_src = (crc_src >> 1);
        }
    }

    //output 4 bytes
    for (i = 0; i < 4; i++)
    {
        num[i] = value_x[3 - i];
    }
 
    return 0;
}

//直接计算法计算crc
unsigned int do_crc(unsigned char *ptr, int len)
{
    unsigned int i;
    unsigned int crc = 0xFFFFFFFF;
    
    while(len--)
    {
        crc ^= *ptr++;
        for (i = 0; i < 8; ++i)
        {
            if (crc & 1)
                crc = (crc >> 1) ^ 0xEDB88320;
            else
                crc = (crc >> 1);
        }
    }
    
    return crc;
    //return ~crc;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int i;
    unsigned char num[4] = { 0, 0, 0, 0 };
    unsigned int crc_dst = 0x651a65c5;
    unsigned int crc_src = 0xffffffff;

    crc32_reverse_byte(crc_dst, crc_src, num);
 
    printf("Add those 4 bytes: ( ");
    for (i = 0; i < 4; i++) {
        printf("%02hhx ", num[i]);
    }
    printf(") to change CRC %08x to %08x\n", crc_src, crc_dst);
 
    printf("test 0x%08x\n", do_crc(num, 4));
    
    return 0;
}
