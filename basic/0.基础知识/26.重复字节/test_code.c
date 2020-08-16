#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/**
 * REPEAT_BYTE - repeat the value @x multiple times as an unsigned long value
 * @x: value to repeat
 *
 * NOTE: @x is not checked for > 0xff; larger values produce odd results.
 */
#define REPEAT_BYTE(x)	((~0ul / 0xff) * (x))

/************************************************************************/
/*                                                                      */
/************************************************************************/

/****************************/

int main(int argc, char* argv[])
{
    unsigned char x;
    
    x = 0x5f;
    printf("0x%x REPEAT_BYTE 0x%lx\n", x, REPEAT_BYTE(x));

    x = 0xf8;
    printf("0x%x REPEAT_BYTE 0x%lx\n", x, REPEAT_BYTE(x));
    
    x = 0x66;
    printf("0x%x REPEAT_BYTE 0x%lx\n", x, REPEAT_BYTE(x));
    
    return 0;
}