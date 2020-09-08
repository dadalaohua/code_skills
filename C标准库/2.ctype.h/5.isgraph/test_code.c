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
    int i;
    
    int var1 = '3';//可打印
    int var2 = 'm';//可打印
    int var3 = ' ';//不可打印
    
    printf("C 语言中所有图形字符: \n");
    
    for (i=0;i<=127;++i)
    {
        if (isgraph(i)!=0)
            printf("%c ",i);
    }
    
    printf("\n" );
    
    if(isgraph(var1))
    {
        printf("var1 = |%c| 是可打印的\n", var1 );
    }
    else
    {
        printf("var1 = |%c| 是不可打印的\n", var1 );
    }
    if(isgraph(var2))
    {
        printf("var2 = |%c| 是可打印的\n", var2 );
    }
    else
    {
        printf("var2 = |%c| 是不可打印的\n", var2 );
    }
    if(isgraph(var3))
    {
        printf("var3 = |%c| 是可打印的\n", var3 );
    }
    else
    {
        printf("var3 = |%c| 是不可打印的\n", var3 );
    }

    return 0;
}