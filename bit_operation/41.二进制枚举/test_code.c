#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
void enumeration_test(int n) {
    for(int i = 0; i < (1<<n); i++) //从0 ～ 2^n - 1个状态
    {
        printf("i %d : ", i);
        for(int j = 0; j < n; j++) //遍历二进制的每一位 共n位
        {
            if(i & (1 << j))    //判断二进制数字i的第j位是否存在
            {
                //操作或者输出
                printf("1 ");
            } else {
                printf("0 ");
            }
        }
        printf("\n");
    }
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    enumeration_test(5);    //2^5 种可能
    return 0;
}