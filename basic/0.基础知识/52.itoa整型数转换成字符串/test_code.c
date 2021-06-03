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
radix：转换后的进制数，可以是10进制、16进制等
************************************************************************/
char *itoa(int val, char *buf, unsigned radix)
{
    char        *p;
    char        *firstdig;
    char        temp;
    unsigned    digval;

    p = buf;
    if(val <0)
    {
        *p++ = '-';
        val = (unsigned long)(-(long)val);
    }
    firstdig = p; 
    do{
        digval = (unsigned)(val % radix);
        val /= radix;
        
        if  (digval > 9)
            *p++ = (char)(digval - 10 + 'a');
        else
            *p++ = (char)(digval + '0');
    }while(val > 0);

    *p-- = '\0';
    do{
        temp = *p;
        *p = *firstdig;
        *firstdig = temp;
        --p;
        ++firstdig;
    }while(firstdig < p);

    return buf;
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
    itoa(val, str, 16);
    printf("val %d hexadecimal: %s\n", val, str);
    itoa(val, str, 2);
    printf("val %d binary: %s\n", val, str);

    return 0;
}