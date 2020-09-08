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
    int var1 = 'd';
    int var2 = '2';
    int var3 = '\t';
    int var4 = ' ';
    
    if(isalpha(var1))
    {
        printf("var1 = |%c| 是字母\n", var1);
    }
    else
    {
        printf("var1 = |%c| 不是字母\n", var1);
    }
    
    if(isalpha(var2))
    {
        printf("var2 = |%c| 是字母\n", var2);
    }
    else
    {
        printf("var2 = |%c| 不是字母\n", var2);
    }
    if(isalpha(var3))
    {
        printf("var3 = |%c| 是字母\n", var3);
    }
    else
    {
        printf("var3 = |%c| 不是字母\n", var3);
    }
    if(isalpha(var4))
    {
        printf("var4 = |%c| 是字母\n", var4);
    }
    else
    {
        printf("var4 = |%c| 不是字母\n", var4);
    }
    
    return 0;
}