#include <stdio.h>
#include <string.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define __is_print(ch) ((unsigned int)((ch) - ' ') < 127u - ' ')

/**
 * dump_hex
 * 
 * @brief dump data in hex format
 * 
 * @param buf: User buffer
 * @param size: Dump data size
 * @param number: The number of outputs per line
 * 
 * @return void
*/
void dump_hex(const unsigned char *buf, unsigned int size, unsigned int number)
{
    int i, j;

    for (i = 0; i < size; i += number)
    {
        printf("%08x: ", i);

        for (j = 0; j < number; j++)
        {
            if (j % 8 == 0)
            {
                printf(" ");
            }
            if (i + j < size)
                printf("%02x ", buf[i + j]);
            else
                printf("   ");
        }
        printf(" ");

        for (j = 0; j < number; j++)
        {
            if (i + j < size)
            {
                printf("%c", __is_print(buf[i + j]) ? buf[i + j] : '.');
            }
        }
        printf("\n");
    }
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    unsigned char i, buff[128];

    for (i = 0; i < sizeof(buff); i++)
    {
        buff[i] = i;
    }

    dump_hex((const unsigned char *)buff, sizeof(buff), 16);
    
    return 0;
}