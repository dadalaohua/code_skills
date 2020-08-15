#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/**
 * ARRAY_SIZE - get the number of elements in array @arr
 * @arr: array to be sized
 */
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

/************************************************************************/
/*                                                                      */
/************************************************************************/

/****************************/

int main(int argc, char* argv[])
{
    unsigned char buf1[] = {'1', '2', '3', '4', '5', '6'};
    unsigned int buf2[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int i;
    
    printf("buf1 len %d\n", ARRAY_SIZE(buf1));
    for(i = 0; i < ARRAY_SIZE(buf1); i++)
    {
        printf("%c ", buf1[i]);
    }
    printf("\n");
    
    printf("buf2 len %d\n", ARRAY_SIZE(buf2));
    for(i = 0; i < ARRAY_SIZE(buf2); i++)
    {
        printf("%d ", buf2[i]);
    }
    printf("\n");
    
    return 0;
}