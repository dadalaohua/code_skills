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

static const unsigned char BitsSetTable256[] = 
{
    0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8
};

static const unsigned char BitsSetTable16[] = 
{
    0, 1, 1, 2, 1, 2, 2, 3,
    1, 2, 2, 3, 2, 3, 3, 4,
};

unsigned char count_bit1_1(unsigned char data)
{
    unsigned char count = 0;     //置0计数
    
    while(data)
    {
       count += (data&1);   //检查Num最后一位是否为1
       data >>= 1;          //位移一位
    }
    
    return count;
}

unsigned char count_bit1_2(unsigned char data)
{
    unsigned char count = 0;     //置0计数
    
    //一个8位的数减1相当于把从后数第一个1及之后的数取反，
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

unsigned char count_bit1_3(unsigned char data)
{
    data = (data & 0x55) + ((data >> 1) & 0x55);
    data = (data & 0x33) + ((data >> 2) & 0x33);
    data = (data & 0x0f) + ((data >> 4) & 0x0f);
    
    return data;
}

unsigned char count_bit1_4(unsigned char data)
{
    return (ones[data]);
}

unsigned char count_bit1_5(unsigned char v)
{
    return BitsSetTable256[v];
}

unsigned char count_bit1_6(unsigned char v)
{
    v = BitsSetTable16[v      & 0x0F] +
        BitsSetTable16[v >> 4 & 0x0F];

    return v;
}

unsigned char count_bit1_7(unsigned char v)
{
    unsigned char c; // c accumulates the total bits set in v

    for (c = 0; v; v >>= 1)
    {
        c += v & 1;
    }
    
    return c;
}

unsigned char count_bit1_8(unsigned char v)
{
    unsigned char c; // c accumulates the total bits set in v

    for (c = 0; v; c++)
    {
        v &= v - 1;   // clear the least significant bit set
    }
    
    return c;
}

unsigned char count_bit1_9(unsigned char x)
{
    x = (x * 0x200040008001ULL & 0x111111111111111ULL) % 0xf;

    return x;
}

unsigned char count_bit1_10(unsigned char x)
{
    x =  (x * 0x1001001001001ULL & 0x84210842108421ULL) % 0x1f;

    return x;
}

unsigned char count_bit1_11(unsigned char x)
{
    x = x - ((x >> 1) & 0x55);
    x = (x & 0x33) + ((x >> 2) & 0x33);
    x = (x + (x >> 4)) & 0x0f;
    
    return x & 0x0f;
}

unsigned char count_bit1_12(unsigned char x)
{
    unsigned char n;
    
    n = (x >> 1) & 033333333333;
    x = x - n;
    n = (n >> 1) & 033333333333;
    x = x - n;
    x = (x + (x >> 3)) & 030707070707;
    
    return x % 63;
}

int main(int argc, char* argv[])
{ 
    unsigned char test = 0x5F;

    printf("count_bit1: %d\n", count_bit1_1(test));
    printf("count_bit1: %d\n", count_bit1_2(test));
    printf("count_bit1: %d\n", count_bit1_3(test));
    printf("count_bit1: %d\n", count_bit1_4(test));
    printf("count_bit1: %d\n", count_bit1_5(test));
    printf("count_bit1: %d\n", count_bit1_6(test));
    printf("count_bit1: %d\n", count_bit1_7(test));
    printf("count_bit1: %d\n", count_bit1_8(test));
    printf("count_bit1: %d\n", count_bit1_9(test));
    printf("count_bit1: %d\n", count_bit1_10(test));
    printf("count_bit1: %d\n", count_bit1_11(test));
    printf("count_bit1: %d\n", count_bit1_12(test));

    return 0;
}