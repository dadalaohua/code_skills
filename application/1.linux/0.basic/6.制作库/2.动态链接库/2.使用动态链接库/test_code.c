#include <stdio.h>
#include "func.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
 

/****************************/

int main(int argc, char* argv[])
{
    int x;
    
    func1();
    
    x = func2(2, 3);
    
    printf("x = 2 + 3 = %d\n", x);
    
    return 0;
}