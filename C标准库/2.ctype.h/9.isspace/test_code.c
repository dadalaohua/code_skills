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
    int var1 = 't';
    int var2 = '\r';
    int var3 = ' ';

    if(isspace(var1))
    {
        printf("var1 = |%c| 是空白字符\n", var1 );
    }
    else
    {
        printf("var1 = |%c| 不是空白字符\n", var1 );
    }
    
    if(isspace(var2))
    {
        printf("var2 = |%c| 是空白字符\n", var2 );
    }
    else
    {
        printf("var2 = |%c| 不是空白字符\n", var2 );
    }
    
    if(isspace(var3))
    {
        printf("var3 = |%c| 是空白字符\n", var3 );
    }
    else
    {
        printf("var3 = |%c| 不是空白字符\n", var3 );
    }

    return 0;
}