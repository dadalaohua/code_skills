#include <stdio.h>
#include <errno.h>
#include <math.h>
 
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

    x = 2.000000;
    value = log(x); //Log(2.000000) = 0.693147

    if(errno == ERANGE)
    {
        printf("Log(%f) is out of range\n", x);
    }
    else 
    {
        printf("Log(%f) = %f\n", x, value);
    }

    x = 1.000000;
    value = log(x); //Log(1.000000) = 0.000000

    if(errno == ERANGE)
    {
        printf("Log(%f) is out of range\n", x);
    }
    else 
    {
        printf("Log(%f) = %f\n", x, value);
    }

    x = 0.000000;
    value = log(x); //Log(0.000000) is out of range

    if(errno == ERANGE)
    {
        printf("Log(%f) is out of range\n", x);
    }
    else 
    {
        printf("Log(%f) = %f\n", x, value);
    }
   
    return 0;
}