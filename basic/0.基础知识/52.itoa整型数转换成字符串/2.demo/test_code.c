#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/

/************************************************************************
char *itoa( int value, char *string,int radix);

原型说明：
value：欲转换的数据。
string：目标字符串的地址。
radix：转换后的进制数，只支持10进制以下，如2进制，8进制，10进制，不支持16进制
************************************************************************/
int itoa(long long value, char *s, unsigned radix)
{
    char *p, aux;
    unsigned long long v;
    size_t l;

    /* Generate the string representation, this method produces
     * an reversed string. */
    v = (value < 0) ? -value : value;
    p = s;
    do {
        *p++ = '0' + (v % radix);
        v /= radix;
    } while (v);
    if (value < 0) *p++ = '-';

    /* Compute length and add null term. */
    l = p - s;
    *p = '\0';

    /* Reverse the string. */
    p--;
    while (s < p) {
        aux = *s;
        *s = *p;
        *p = aux;
        s++;
        p--;
    }
    return l;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int val = 1234;
    char str[30];

    itoa(val, str, 10);
    printf("val %d decimal: %s\n", val, str);
    // itoa(val, str, 16);
    // printf("val %d hexadecimal: %s\n", val, str);//不支持
    itoa(val, str, 2);
    printf("val %d binary: %s\n", val, str);
    itoa(val, str, 8);
    printf("val %d octal: %s\n", val, str);

    return 0;
}