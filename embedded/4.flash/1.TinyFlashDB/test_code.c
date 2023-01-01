#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "tinyflashdb.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/
const tfdb_index_t test_index = {
    .flash_addr = 0x4000,
    .flash_size = 256,
    .value_length = 2,
    .end_byte = 0x00,
};/* c99写法，如果编译器不支持，可自行改为c89写法 */
tfdb_addr_t addr = 0; /*addr cache*/

uint8_t test_buf[4]; /*aligned_value_size*/

uint16_t test_value = 0x1234;

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    TFDB_Err_Code result;
    result = tfdb_set(&test_index, test_buf, &addr, &test_value);
    if(result == TFDB_NO_ERR)
    {
        printf("set ok, addr:%x\n", addr);
    }

    addr = 0;   /* reset addr cache, to see tfdb_get. */

    result = tfdb_get(&test_index, test_buf, &addr, &test_value);
    if(result == TFDB_NO_ERR)
    {
        printf("get ok, addr:%x, value:%x\n", addr, test_value);
    }
    return 0;
}