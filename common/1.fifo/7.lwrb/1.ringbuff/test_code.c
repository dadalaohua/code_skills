#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "ringbuff.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/


/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    /* Buffer */
    ringbuff_t buff;
    uint8_t buff_data[8];

    /* Working data */
    uint8_t data[2];
    size_t len;
    uint8_t i;

    /* Initialize buffer */
    ringbuff_init(&buff, buff_data, sizeof(buff_data));

    /* Write 4 bytes of data */
    ringbuff_write(&buff, "0123", 4);

    /* Try to fully read buffer */
    /* len holds number of bytes read */
    while ((len = ringbuff_read(&buff, data, sizeof(data)))) {
        printf("Read successful of %d bytes\r\n", (int)len);
        for(i = 0; i < len; i++) {
            printf("id %d data %c\r\n", i, data[i]);
        }
    }
    return 0;
}