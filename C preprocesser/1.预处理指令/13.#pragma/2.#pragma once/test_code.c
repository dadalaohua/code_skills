#include <stdio.h>
#include "test_code.h"
#include "test_code.h" //被 include 两次

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    printf("g_nValue = %d \n",g_nValue);
    
    return 0;
}
