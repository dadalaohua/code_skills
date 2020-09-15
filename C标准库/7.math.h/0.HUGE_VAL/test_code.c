#include <stdio.h>
#include <math.h>
#include <errno.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/


/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    double x;
    double value;
   
    printf("HUGE_VAL : %f\n", HUGE_VAL);
    
    x = 0.000000;
    value = log(x);
    
    if(value == HUGE_VAL)
    {
        printf("value : %f\n", value);
    }

    if(errno == ERANGE) 
    {
        printf("Log(%f) is out of range, value: %f\n", x, value);
    }
    else 
    {
        printf("Log(%f) = %f\n", x, value);
    }

   
    return 0;
}