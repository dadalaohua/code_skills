#include <stdio.h>

// int findN(int N){
    // int sum = 1;
    // while(1){
        // if(sum * 2 > N){
            // return sum;
        // }
        // sum = sum * 2;
   // }
// }

int findN(int n){
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8; // 整型一般是 32 位，上面我是假设 8 位。
    return (n + 1) >> 1;
}

int main(int argc, char* argv[])
{ 
    int n;
    int reseult;
    
    printf("Input n:\n");
    scanf("%d",&n);
    
    reseult = findN(n);
    
    printf("reseult = %d\n", reseult);
    
    return 0;
}