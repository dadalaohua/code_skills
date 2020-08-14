#include <stdio.h>

typedef enum bool{false, true} bool;

//遍历是否有相同公约数
bool isPrime(unsigned int m, unsigned int n)
{
    unsigned int i=0;
    bool Flag = true;

    if(!m || !n)
        return false;
    
    if(m < 2 || n < 2)
        return true;

    unsigned int tem = ( m > n ) ? n : m;
    for(i = 2; i <= tem && Flag; i++)
    {
        bool mFlag = true;
        bool nFlag = true;
        if( m % i == 0 )
            mFlag = false;
        if( n % i == 0 )
            nFlag = false;
        if( !mFlag && !nFlag )
            Flag = false;
    }
    if(Flag)
        return true;
    else
        return false;
}

//欧几里得算法（辗转相除法）
bool gcd(unsigned int x, unsigned int y)
{
    int c;
    
    //求出两个正整数的最大公约数
    do{
        c = x % y;
        x = y;
        y = c;
    }while (c);
    
    if(x == 1)  //最大公约数为1
        return true;
    else
        return false;
}

/****************************/

int main(int argc, char* argv[])
{
    unsigned int x, y;
    
    printf("1, 2:\n");
    x = 1;
    y = 2;
    printf("%s \n", isPrime(x, y) == true ? "互质":"不是互质");
    printf("%s \n", gcd(x, y) == true ? "互质":"不是互质");
    
    printf("0, 5:\n");
    x = 0;
    y = 5;
    printf("%s \n", isPrime(x, y) == true ? "互质":"不是互质");
    printf("%s \n", gcd(x, y) == true ? "互质":"不是互质");
    
    printf("17, 31:\n");
    x = 17;
    y = 31;
    printf("%s \n", isPrime(x, y) == true ? "互质":"不是互质");
    printf("%s \n", gcd(x, y) == true ? "互质":"不是互质");
    
    printf("14, 13:\n");
    x = 14;
    y = 13;
    printf("%s \n", isPrime(x, y) == true ? "互质":"不是互质");
    printf("%s \n", gcd(x, y) == true ? "互质":"不是互质");
    
    printf("75, 77:\n");
    x = 75;
    y = 77;
    printf("%s \n", isPrime(x, y) == true ? "互质":"不是互质");
    printf("%s \n", gcd(x, y) == true ? "互质":"不是互质");
    
    printf("13, 1:\n");
    x = 13;
    y = 1;
    printf("%s \n", isPrime(x, y) == true ? "互质":"不是互质");
    printf("%s \n", gcd(x, y) == true ? "互质":"不是互质");
    
    printf("97, 16:\n");
    x = 97;
    y = 16;
    printf("%s \n", isPrime(x, y) == true ? "互质":"不是互质");
    printf("%s \n", gcd(x, y) == true ? "互质":"不是互质");
    
    printf("13, 25:\n");
    x = 13;
    y = 25;
    printf("%s \n", isPrime(x, y) == true ? "互质":"不是互质");
    printf("%s \n", gcd(x, y) == true ? "互质":"不是互质");
    
    printf("317, 52:\n");
    x = 317;
    y = 52;
    printf("%s \n", isPrime(x, y) == true ? "互质":"不是互质");
    printf("%s \n", gcd(x, y) == true ? "互质":"不是互质");
    
    printf("84, 104:\n");
    x = 84;
    y = 104;
    printf("%s \n", isPrime(x, y) == true ? "互质":"不是互质");
    printf("%s \n", gcd(x, y) == true ? "互质":"不是互质");
    
    printf("69, 105:\n");
    x = 69;
    y = 105;
    printf("%s \n", isPrime(x, y) == true ? "互质":"不是互质");
    printf("%s \n", gcd(x, y) == true ? "互质":"不是互质");
    
    printf("\n");
    
    return 0;
}