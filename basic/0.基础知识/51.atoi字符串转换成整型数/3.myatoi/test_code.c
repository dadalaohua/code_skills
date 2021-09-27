#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/

int myAtoi(char * s){
    long long int value = 0;
    int ret;
    int flag = 1;

    while (*s == ' ')
    {
        s++;
    }
    if (*s == '-')
    {
        flag = 0;
        s++;
    }
    else if (*s == '+')
    {
        flag = 1;
        s++;
    }
    else if (*s > '9' || *s < '0') 
    {
        return 0;    
    }

    while (*s != '\0' && *s <= '9' && *s >= '0')
    {
        value = value * 10 + *s - '0';
        s++;

        if(value > INT_MAX)
            break;
    }

    if (flag == 0)
    {
        value = -value;
    }

    if(value > INT_MAX)
        ret = INT_MAX;
    else if(value < INT_MIN)
        ret = INT_MIN;
    else
        ret = value;

    return ret;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int val;
    char str[20];

    strcpy(str, "123456789");
    val = myAtoi(str);
    printf("字符串值 = %s, 整型值 = %d\n", str, val);
    
    strcpy(str, "-321654987");
    val = myAtoi(str);
    printf("字符串值 = %s, 整型值 = %d\n", str, val);
    
    strcpy(str, "helloworld");
    val = myAtoi(str);
    printf("字符串值 = %s, 整型值 = %d\n", str, val);
    
    strcpy(str, "123helloworld");
    val = myAtoi(str);
    printf("字符串值 = %s, 整型值 = %d\n", str, val);

    return 0;
}