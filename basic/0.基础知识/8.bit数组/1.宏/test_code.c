#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define BITARRAY_SHIFT  3
#define BITARRAY_MASK   0x7
 
#define BITARRAY_SIZE(size)             ((size >> BITARRAY_SHIFT) + 1)
#define BITARRAY_BYTE_INDEX(num)        (num >> BITARRAY_SHIFT)
#define BITARRAY_SET(array, num)        (array[BITARRAY_BYTE_INDEX(num)] |= (1 << (num & BITARRAY_MASK)))
#define BITARRAY_CLR(array, num)        (array[BITARRAY_BYTE_INDEX(num)] &= ~(1 << (num & BITARRAY_MASK)))
#define BITARRAY_IS_IN(array, num)      (array[BITARRAY_BYTE_INDEX(num)] & (1 << (num & BITARRAY_MASK)))
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

/****************************/

//检测
void test(int value)
{
    if (value)
    {
        printf("In the array.\n");
    }
    else
    {
        printf("Not in the array.\n");
    }
}

int main(int argc, char* argv[])
{
    //存储0~10这11个数
    int max_size = 11;
    //存储9
    int number = 9;
    char *bitArray = (char*)malloc(BITARRAY_SIZE(max_size) * sizeof(char));
    int count;
     
    printf("Init: ");
    test(BITARRAY_IS_IN(bitArray, number));
 
    //9放到位数组上
    BITARRAY_SET(bitArray, number);
    printf("BITARRAY_SET: ");
    test(BITARRAY_IS_IN(bitArray, number));
    
    BITARRAY_SET(bitArray, 3);
    printf("BITARRAY_SET: ");
    test(BITARRAY_IS_IN(bitArray, 3));
    
    printf("BITARRAY_BYTE_BIT_NUM: %d\n", BITARRAY_BYTE_BIT_NUM(bitArray[BITARRAY_BYTE_INDEX(number)]));
    
    count = BITARRAY_ARRAY_BIT_NUM(bitArray, max_size);
    printf("BITARRAY_ARRAY_BIT_NUM: %d\n", count);
    
    //9从位数组上清除
    BITARRAY_CLR(bitArray, number);
    printf("BITARRAY_CLR: ");
    test(BITARRAY_IS_IN(bitArray, number));
     
    if (bitArray)
    {
        free(bitArray);
        bitArray = NULL;
    }
    
    printf("\n");
    
    return 0;
}