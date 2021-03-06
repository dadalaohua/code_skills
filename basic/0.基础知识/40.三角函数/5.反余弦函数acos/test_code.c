#include <stdio.h>
#include <math.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define PI 3.14159265

/************************************************************************/
/*                                                                      */
/************************************************************************/

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    double i;
    
    for(i = 0; i < 1; i += 0.05)
    {
        printf("The arc cosine of %f is %f degrees\n", i, acos (i) * 180 / PI);
    }
    
    printf("The arc cosine of %f is %f degrees\n", i, acos (1) * 180 / PI);
    
    printf("\n");
    
    return 0;
}