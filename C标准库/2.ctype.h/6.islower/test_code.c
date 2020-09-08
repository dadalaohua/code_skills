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
    int var1 = 'Q';
    int var2 = 'q';
    int var3 = '3';

    if( islower(var1) )
    {
        printf("var1 = |%c| 是小写字母\n", var1 );
    }
    else
    {
        printf("var1 = |%c| 不是小写字母\n", var1 );
    }
    
    if( islower(var2) )
    {
        printf("var2 = |%c| 是小写字母\n", var2 );
    }
    else
    {
        printf("var2 = |%c| 不是小写字母\n", var2 );
    }
    
    if( islower(var3) )
    {
        printf("var3 = |%c| 是小写字母\n", var3 );
    }
    else
    {
        printf("var3 = |%c| 不是小写字母\n", var3 );
    }

    return 0;
}