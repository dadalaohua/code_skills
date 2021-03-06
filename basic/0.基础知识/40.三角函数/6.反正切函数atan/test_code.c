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
    
    for(i = 0; i < 10; i += 0.5)
    {
        printf("The arc tangent of %f is %f degrees\n", i, atan (i) * 180 / PI);
    }
    
    printf("\n");
    
    return 0;
}