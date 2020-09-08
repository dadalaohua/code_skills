#include <stdio.h>
#include <ctype.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/


/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{ 
    int var1 = 'M';
    int var2 = 'm';
    int var3 = '3';

    if(isupper(var1))
    {
        printf("var1 = |%c| 是大写字母\n", var1);
    }
    else
    {
        printf("var1 = |%c| 不是大写字母\n", var1);
    }
    
    if(isupper(var2))
    {
        printf("var2 = |%c| 是大写字母\n", var2);
    }
    else
    {
        printf("var2 = |%c| 不是大写字母\n", var2);
    }
    
    if(isupper(var3))
    {
        printf("var3 = |%c| 是大写字母\n", var3);
    }
    else
    {
        printf("var3 = |%c| 不是大写字母\n", var3);
    }

    return 0;
}