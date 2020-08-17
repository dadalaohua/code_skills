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
    
    /*****************************************/
    
    x = y = 0;
    
    printf("Exchange two numbers test code\n");
    printf("Input x:\n");
    scanf("%d",&x);
    
    printf("Input y:\n");
    scanf("%d",&y);
    
    //使用该用法要注意，结合顺序可能会有问题
    x^=y^=x^=y;
    
    printf("Exchange two numbers\n");
    printf("result x:%d, y:%d\n", x, y);
    
    return 0;
}