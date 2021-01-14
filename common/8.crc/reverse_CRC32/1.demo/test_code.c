#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "crc32.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/


/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int i;
    unsigned char num[4] = { 0, 0, 0, 0 };
    unsigned int crc_dst = 0;
    unsigned int crc_src = 0;
 
    printf("crc32: reverse 4 bytes\n");
    printf("crc32: enter 2 CRC value: src dst\n");
    scanf("%08x %08x", &crc_src, &crc_dst);
 
    cyg_crc32_change(crc_dst, crc_src, num);
 
    printf("Add those 4 bytes: ( ");
    for (i = 0; i < 4; i++) {
        printf("%02hhx ", num[i]);
    }
    printf(") to change CRC %08x to %08x\n", crc_src, crc_dst);
 
    printf("change  crc: %08x ==> %08x\n", crc_src,
            cyg_crc32_accumulate(crc_src, num, 4));
 
    printf("reserve crc: %08x ==> %08x\n", crc_dst,
            cyg_crc32_reserve(crc_dst, num, 4));
    
    return 0;
}
