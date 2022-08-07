#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define PI 3.14159265

/************************************************************************/
/*                                                                      */
/************************************************************************/
double myfactorial(int num) {
    long long ret = num;
    while(--num) {
        ret *= num;
    }
    return ret;
}

double mypower(double num, int exp) {
    double ret = 1;
    while(exp--) {
        ret *= num;
    }
    return ret;
}

double mysin(double x) {
    return x - (mypower(x, 3) / myfactorial(3))\
            + (mypower(x, 5) / myfactorial(5))\
            - (mypower(x, 7) / myfactorial(7))\
            + (mypower(x, 9) / myfactorial(9))\
            - (mypower(x, 11) / myfactorial(11));
}

double mycos(double x) {
    return 1 - (mypower(x, 2) / myfactorial(2))\
            + (mypower(x, 4) / myfactorial(4))\
            - (mypower(x, 6) / myfactorial(6))\
            + (mypower(x, 8) / myfactorial(8))\
            - (mypower(x, 12) / myfactorial(12));
}

int main(int argc, char* argv[])
{
    printf("%f\n", mysin(0 * PI / 180));
    printf("%f\n", mysin(30 * PI / 180));
    printf("%f\n", mysin(45 * PI / 180));
    printf("%f\n", mysin(60 * PI / 180));
    printf("%f\n", mysin(90 * PI / 180));
    
    printf("\n");
    
    printf("%f\n", mycos(0 * PI / 180));
    printf("%f\n", mycos(30 * PI / 180));
    printf("%f\n", mycos(45 * PI / 180));
    printf("%f\n", mycos(60 * PI / 180));
    printf("%f\n", mycos(90 * PI / 180));
    
    return 0;
}