#include <stdio.h>
#include <stdlib.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
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

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    char buf[128];
    int a = 753;
    int b = -16;
    short c = 753;
    short d = -16;
    char e = 15;
    char f = -1;
    long long l1 = 753;
    long long l2 = -16;
    
    printf("定义int a=%d, int b=%d\r\n", a, b);

    printf("\n");
    printf("a的2进制格式(显示32位)：\n");
    integer_to_bin_ascii(a, sizeof(a), buf);
    printf("%s\n", buf);
    
    printf("\n");
    printf("b的2进制格式(显示32位)：\n");
    integer_to_bin_ascii(b, sizeof(b), buf);
    printf("%s\n", buf);
    
    printf("\n");
    printf("定义short c=%d, short d=%d\r\n", c, d);

    printf("\n");
    printf("c的2进制格式(显示16位)：\n");
    integer_to_bin_ascii(c, sizeof(c), buf);
    printf("%s\n", buf);
    
    printf("\n");
    printf("d的2进制格式(显示16位)：\n");
    integer_to_bin_ascii(d, sizeof(d), buf);
    printf("%s\n", buf);
    
    printf("\n");
    printf("定义char e=%d, char f=%d\r\n", e, f);

    printf("\n");
    printf("e的2进制格式(显示8位)：\n");
    integer_to_bin_ascii(e, sizeof(e), buf);
    printf("%s\n", buf);
    
    printf("\n");
    printf("f的2进制格式(显示8位)：\n");
    integer_to_bin_ascii(f, sizeof(f), buf);
    printf("%s\n", buf);
    
    printf("\n");
    printf("定义long long l1=%lld, long long ll2=%lld\r\n", l1, l2);

    printf("\n");
    printf("l1的2进制格式(显示64位)：\n");
    integer_to_bin_ascii(l1, sizeof(l1), buf);
    printf("%s\n", buf);
    
    printf("\n");
    printf("l2的2进制格式(显示64位)：\n");
    integer_to_bin_ascii(l2, sizeof(l2), buf);
    printf("%s\n", buf);
    
    return 0;
}