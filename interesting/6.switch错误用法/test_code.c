#include <stdio.h>

int main(int argc, char* argv[])
{
    int a = 10;
    
    switch(a)
    {
        int b = 20;
        case 10:
            printf("1: %d %d %d\n", a, b, a + b);
            break;
        default:
            printf("2: %d\n", a + b);
            break;
    }

    return 0;
}