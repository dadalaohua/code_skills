#include <stdbool.h>

//判断是否是奇数
bool isOdd(unsigned int num)
{
    if(num & 1)
        return true;    //num是个奇数
    else
        return false;   //num是个偶数
}

/****************************/

int main(int argc, char* argv[])
{
    int i;
    
    for(i = 0; i < 10; i++)
    {
        printf("%d is %s number\n", i, isOdd(i) == true ? "odd" : "even");
    }
    
    return 0;
}