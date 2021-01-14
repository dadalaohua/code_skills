#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define SWAP(a, b) (((a) ^= (b)), ((b) ^= (a)), ((a) ^= (b)))

#define SWAP2(a, b) (((a) == (b)) || (((a) ^= (b)), ((b) ^= (a)), ((a) ^= (b))))

#define SWAP3(a, b) (((a) ^ (b)) && ((b) ^= (a) ^= (b), (a) ^= (b)))

#define SWAP4(a, b) ((&(a) == &(b)) || (((a) ^= (b)), ((b) ^= (a)), ((a) ^= (b))))

#define SWAP5(a, b) (((a) ^ (b)) && (((a) ^= (b)), ((b) ^= (a)), ((a) ^= (b))))

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int x, y;
    
    x = 10;
    y = 20;
    
    // printf("x = %d, x = %d\n", x, x);
    
    // SWAP(x, x);
    
    // printf("x = %d, x = %d\n", x, x);
    
    // x = 10;
    
    // printf("x = %d, x = %d\n", x, x);
    
    // SWAP2(x, x);
    
    // printf("x = %d, x = %d\n", x, x);
    
    // x = 10;
    
    // printf("x = %d, x = %d\n", x, x);
    
    // SWAP4(x, x);
    
    // printf("x = %d, x = %d\n", x, x);
    
    // x = 10;
    
    // printf("x = %d, x = %d\n", x, x);
    
    // SWAP5(x, x);
    
    // printf("x = %d, x = %d\n", x, x);
    
    printf("x = %d, y = %d\n", x, y);
    
    SWAP(x, y);
    
    printf("x = %d, y = %d\n", x, y);
    
    SWAP2(x, y);
    
    printf("x = %d, y = %d\n", x, y);
    
    SWAP3(x, y);
    
    printf("x = %d, y = %d\n", x, y);
    
    SWAP4(x, y);
    
    printf("x = %d, y = %d\n", x, y);
    
    SWAP5(x, y);
    
    printf("x = %d, y = %d\n", x, y);
    
    return 0;
}