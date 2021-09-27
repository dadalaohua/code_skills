#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
int gray_code_reversal(int g)
{
    int n = 0;
    while(g) {
        n ^= g;
        g >>= 1;
    }
    return n;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
int gray_code(int n)
{
    return n ^ (n >> 1);
}

void integer_to_bin_ascii(int num, int size, char* buf)
{
    unsigned char *p = (unsigned char*)&num + size - 1;
    unsigned char tmp;
    int i, j, cnt = 0;
    
    for (i = 0; i < size; i++) //处理4个字节(32位）
    {
        tmp = *(p - i); //取每个字节的首地址
        for (j = 7; j >= 0; j--) //处理每个字节的8个位
        {
            if (tmp & (1 << j))
                buf[cnt++] = '1';
            else
                buf[cnt++] = '0';
        }
        buf[cnt++] = ' ';
    }
    buf[cnt] = '\0';
}

int main(int argc, char* argv[])
{
    int i, val, rev;
    char buf[128];
    
    for(i = 0; i < 64; i++)
    {
        val = gray_code(i);                             //格雷码计算
        integer_to_bin_ascii(val, sizeof(val), buf);    //展示二进制形式
        
        rev = gray_code_reversal(val);
        printf("%d 0x%x %s reversal %d\n", i, val, buf, rev);
    }
    
    return 0;
}