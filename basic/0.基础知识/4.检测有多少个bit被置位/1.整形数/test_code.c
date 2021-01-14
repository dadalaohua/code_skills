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
}

unsigned int count_bit1_5(unsigned int v)
{
    unsigned int c; // c is the total bits set in v

    c = BitsSetTable256[ v        & 0xff] +
        BitsSetTable256[(v >>  8) & 0xff] +
        BitsSetTable256[(v >> 16) & 0xff] +
        BitsSetTable256[ v >> 24        ];
    
    return c;
}

unsigned int count_bit1_5_2(unsigned int v)
{
    unsigned int c; // c is the total bits set in v
    unsigned char * p = (unsigned char *) &v;
    
    c = BitsSetTable256[p[0]] + 
        BitsSetTable256[p[1]] + 
        BitsSetTable256[p[2]] +
        BitsSetTable256[p[3]];
    
    return c;
}

unsigned int count_bit1_6(unsigned int v)
{
    v = BitsSetTable16[v       & 0x0F] +
        BitsSetTable16[v >>  4 & 0x0F] +
        BitsSetTable16[v >>  8 & 0x0F] +
        BitsSetTable16[v >> 12 & 0x0F] +
        BitsSetTable16[v >> 16 & 0x0F] +
        BitsSetTable16[v >> 20 & 0x0F] +
        BitsSetTable16[v >> 24 & 0x0F] +
        BitsSetTable16[v >> 28 & 0x0F];
    
    return v;
}

unsigned int count_bit1_6_2(unsigned int v)
{
    unsigned int c; // c is the total bits set in v
    unsigned char * p = (unsigned char *) &v;
    
    c = BitsSetTable16[p[0]      & 0x0F] + 
        BitsSetTable16[p[0] >> 4 & 0x0F] + 
        BitsSetTable16[p[1]      & 0x0F] + 
        BitsSetTable16[p[1] >> 4 & 0x0F] + 
        BitsSetTable16[p[2]      & 0x0F] +
        BitsSetTable16[p[2] >> 4 & 0x0F] +
        BitsSetTable16[p[3]      & 0x0F] +
        BitsSetTable16[p[3] >> 4 & 0x0F];
    
    return c;
}

unsigned int count_bit1_7(unsigned int v)
{
    unsigned int c; // c accumulates the total bits set in v

    for (c = 0; v; v >>= 1)
    {
        c += v & 1;
    }
    
    return c;
}

unsigned int count_bit1_8(unsigned int v)
{
    unsigned int c; // c accumulates the total bits set in v

    for (c = 0; v; c++)
    {
        v &= v - 1;   // clear the least significant bit set
    }
    
    return c;
}

unsigned int count_bit1_9(unsigned int x)
{
    unsigned int val;

    val =  ((x & 0xfff) * 0x1001001001001ULL & 0x84210842108421ULL) % 0x1f;
    val += (((x & 0xfff000) >> 12) * 0x1001001001001ULL & 0x84210842108421ULL) % 0x1f;
    val += ((x >> 24) * 0x1001001001001ULL & 0x84210842108421ULL) % 0x1f;
    
    return val;
}

unsigned int count_bit1_10(unsigned int x)
{
    x = x - ((x >> 1) & 0x55555555);
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    x = (x + (x >> 4)) & 0x0f0f0f0f;
    x = x + (x >> 8);
    x = x + (x >> 16);
    
    return x & 0x0000003f;
}

unsigned int count_bit1_11(unsigned int x)
{
    unsigned int n;
    
    n = (x >> 1) & 033333333333;
    x = x - n;
    n = (n >> 1) & 033333333333;
    x = x - n;
    x = (x + (x >> 3)) & 030707070707;
    
    return x % 63;
}

int main(int argc, char* argv[])
{ 
    unsigned int test = 0x5134684B;

    printf("count_bit1: %d\n", count_bit1_1(test));
    printf("count_bit1: %d\n", count_bit1_2(test));
    printf("count_bit1: %d\n", count_bit1_3(test));
    printf("count_bit1: %d\n", count_bit1_4(test));
    printf("count_bit1: %d\n", count_bit1_5(test));
    printf("count_bit1: %d\n", count_bit1_5_2(test));
    printf("count_bit1: %d\n", count_bit1_6(test));
    printf("count_bit1: %d\n", count_bit1_6_2(test));
    printf("count_bit1: %d\n", count_bit1_7(test));
    printf("count_bit1: %d\n", count_bit1_8(test));
    printf("count_bit1: %d\n", count_bit1_9(test));
    printf("count_bit1: %d\n", count_bit1_10(test));
    printf("count_bit1: %d\n", count_bit1_11(test));

    return 0;
}