#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/


/************************************************************************/
/*                                                                      */
/************************************************************************/
//https://www.man7.org/linux/man-pages/man3/drand48.3.html
int main(int argc, char* argv[])
{
    srand48(time(NULL));
    printf("Random number in the [0.0, 1.0) range: %f\n", drand48());
    
    //unsigned short seed16v[3] = {1, 2, 3};
    unsigned short seed16v[3] = {time(NULL) + 1, time(NULL) + 2, time(NULL) + 3};
    unsigned short *p = seed48(seed16v);
    for(int i = 0; i < 3; i++)
        printf("%d\n", *(p+i));
    printf("\n");
    printf("Random number in the [0, 2^31) range: %ld\n", lrand48());
    
    //unsigned short int param[7] = {1, 2, 3, 4, 5, 6, 7};
    unsigned short int param[7] = {time(NULL) + 1, time(NULL) + 2, time(NULL) + 3, time(NULL) + 4, time(NULL) + 5, time(NULL) + 6, time(NULL) + 7};
    lcong48(param);
    printf("Random number in the [-2^31, 2^31) range: %ld\n", mrand48());
    
    
    //下面这三个接口不需要调用初始化程序
    //unsigned short xsubi[3] = {1, 2, 3};
    unsigned short xsubi[3] = {time(NULL) + 1, time(NULL) + 2, time(NULL) + 3};
    printf("Random number in the [0.0, 1.0) range: %f\n", erand48(xsubi));
    
    printf("Random number in the [0, 2^31) range: %ld\n", nrand48(xsubi));
    
    printf("Random number in the [-2^31, 2^31) range: %ld\n", jrand48(xsubi));
    
    return 0;
}