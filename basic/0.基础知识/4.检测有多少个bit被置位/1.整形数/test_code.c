#include <stdio.h>

const int ones[] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2,\
 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4,\
 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 1, 2, 2, 3, 2,\
 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5,\
 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5,\
 6, 4, 5, 5, 6, 5, 6, 6, 7, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,\
 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3,\
 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 2, 3,\
 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5,\
 6, 5, 6, 6, 7, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6,\
 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8};
 
unsigned int count_bit1_1(unsigned int data)
{
    unsigned int count = 0;     //置0计数
    
    while(data)
    {
       count += (data&1);   //检查Num最后一位是否为1
       data >>= 1;          //位移一位
    }
    
    return count;
}

unsigned int count_bit1_2(unsigned int data)
{
    unsigned int count = 0;     //置0计数
    
    //一个32位的数减1相当于把从后数第一个1及之后的数取反，
    //然后与原数相与就把这些去反以后的位清0了，
    //等到所有的位都被清0，就会跳出循环。
    //这种算法的效率跟1的个数有关，有多少1就循环多少次。
    while(data)
    {
       data &= (data - 1);
       count ++;
    }
    
    return count;
}

unsigned int count_bit1_3(unsigned int data)
{
    data = (data & 0x55555555) + ((data >> 1) & 0x55555555);
    data = (data & 0x33333333) + ((data >> 2) & 0x33333333);
    data = (data & 0x0f0f0f0f) + ((data >> 4) & 0x0f0f0f0f);
    data = (data & 0x00ff00ff) + ((data >> 8) & 0x00ff00ff);
    data = (data & 0x0000ffff) + ((data >> 16) & 0x0000ffff);
    
    return data;
}

unsigned int count_bit1_4(unsigned int data)
{
    return (ones[data & 0xff] + ones[(data >> 8) & 0xff] + ones[(data >> 16) & 0xff]\
    + ones[(data >> 24) & 0xff]);

    return data;
}

int main(int argc, char* argv[])
{ 
    unsigned int test = 0x5134684B;

    printf("count_bit1: %d\n", count_bit1_1(test));
    printf("count_bit1: %d\n", count_bit1_2(test));
    printf("count_bit1: %d\n", count_bit1_3(test));
    printf("count_bit1: %d\n", count_bit1_4(test));

    return 0;
}