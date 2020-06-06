#include <stdio.h>

int main(int argc, char* argv[])
{ 
    int x;
    printf("Odd and even number judgment test code\n");
    printf("Input num:\n");
    scanf("%d",&x);
    
    //一般做法
    if(x % 2 == 1){
        //n是个奇数
        printf("%d Odd number\n", x);
    }
    else{
        //n是个偶数
        printf("%d even number\n", x);
    }

    //位运算
    if(x & 1 == 1){
        //n是个奇数
        printf("%d Odd number\n", x);
    }
    else{
        //n是个偶数
        printf("%d even number\n", x);
    }
    
    return 0;
}