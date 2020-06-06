#include <stdio.h>

int bit_pow(int m, int n){
    int sum = 1;

    while(n != 0){
        if(n & 1 == 1){
            sum *= m;
        }
        m *= m;
        n = n >> 1;
    }

    return sum;
}

int main(int argc, char* argv[])
{ 
    int m, n;
    int sum;
    
    printf("Input m:\n");
    scanf("%d",&m);
    
    printf("Input n:\n");
    scanf("%d",&n);
    
    sum = bit_pow(m, n);
    
    printf("sum = %d\n", sum);
    
    return 0;
}