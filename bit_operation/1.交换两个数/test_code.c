#include <stdio.h>

int main(int argc, char* argv[])
{ 
    int x, y;
    printf("Exchange two numbers test code\n");
    printf("Input x:\n");
    scanf("%d",&x);
    
    printf("Input y:\n");
    scanf("%d",&y);
    
    x = x ^ y;
    y = x ^ y;
    x = x ^ y;

    printf("Exchange two numbers\n");
    printf("result x:%d, y:%d\n", x, y);
    
    return 0;
}