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
    int var1 = 'k'; //可打印的
    int var2 = '8'; //可打印的
    int var3 = '\t';//不可打印的
    int var4 = ' '; //可打印的

    if( isprint(var1) )
    {
        printf("var1 = |%c| 是可打印的\n", var1 );
    }
    else
    {
        printf("var1 = |%c| 是不可打印的\n", var1 );
    }
    
    if( isprint(var2) )
    {
        printf("var2 = |%c| 是可打印的\n", var2 );
    }
    else
    {
        printf("var2 = |%c| 是不可打印的\n", var2 );
    }
    
    if( isprint(var3) )
    {
        printf("var3 = |%c| 是可打印的\n", var3 );
    }
    else
    {
        printf("var3 = |%c| 是不可打印的\n", var3 );
    }
    
    if( isprint(var4) )
    {
        printf("var4 = |%c| 是可打印的\n", var4 );
    }
    else
    {
        printf("var4 = |%c| 是不可打印的\n", var4 );
    }

    return 0;
}