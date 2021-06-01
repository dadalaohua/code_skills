#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//以2为底取对数函数log2(pow((double) v, 1./pow(2, r)))
int bit_log2(float v, int r)
{
    //const int r;
    //const float v; // find int(log2(pow((double) v, 1. / pow(2, r)))), 
                   // where isnormal(v) and v > 0
    int c;         // 32-bit int c gets the result;

    c = *(const int *) &v;  // OR, for portability:  memcpy(&c, &v, sizeof c);
    c = ((((c - 0x3f800000) >> r) + 0x3f800000) >> 23) - 127;
    
    return c;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    float i;

    for(i = 0; i < 65; i+= 0.8)
    {
        //log2((double) v)
        printf("%f %d\n", i, bit_log2(i, 0));
    }
    
    for(i = 0; i < 65; i+= 0.8)
    {
        //log2(sqrt((double) v))
        printf("%f %d\n", i, bit_log2(i, 1));
    }
    
    for(i = 0; i < 65; i+= 0.8)
    {
        //log2(pow((double) v, 1./4))
        printf("%f %d\n", i, bit_log2(i, 2));
    }
    
    return 0;
}