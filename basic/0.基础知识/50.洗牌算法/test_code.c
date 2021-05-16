#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/**
 * swap - swap values of @a and @b
 * @a: first value
 * @b: second value
 */
#define swap(a, b) \
    do { typeof(a) __tmp = (a); (a) = (b); (b) = __tmp; } while (0)

/****************************/
/*     rand_range()函数     */
/*返回min～max的随机函数    */
/****************************/
int rand_range(int min, int max)
{
    return rand()%(max - min + 1) + min;
}

void shuffle1(unsigned int *buf, int len)
{
    int i;
    int rand;
    
    for (i = 0; i < len; i++)
    {
        // 从 i 到最后随机选一个元素
        rand = rand_range(i, len - 1);

        swap(buf[i], buf[rand]);
    }
}

void shuffle2(unsigned int *buf, int len)
{
    int i;
    int rand;
    
    for (i = 0 ; i < len - 1; i++)
    {
        rand = rand_range(i, len - 1);

        swap(buf[i], buf[rand]);
    }
}

void shuffle3(unsigned int *buf, int len)
{
    int i;
    int rand;
    
    for (i = len - 1; i >= 0; i--)
    {
        rand = rand_range(0, i);
        
        swap(buf[i], buf[rand]);
    }
}

void shuffle4(unsigned int *buf, int len)
{
    int i;
    int rand;
    
    for (i = len - 1; i > 0; i--)
    {
        rand = rand_range(0, i);
        
        swap(buf[i], buf[rand]);
    }
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    unsigned int buf[10];
    int i;
    
    srand((unsigned)time(NULL));     // 设置随机数种子
    
    /************************************************************************/
    for(i = 0; i < 10; i++)
    {
        buf[i] = i;
    }
    
    shuffle1(buf, 10);
    
    for(i = 0; i < 10; i++)
    {
        printf("%d ", buf[i]);
    }
    printf("\n");
    
    /************************************************************************/
    for(i = 0; i < 10; i++)
    {
        buf[i] = i;
    }
    
    shuffle2(buf, 10);
    
    for(i = 0; i < 10; i++)
    {
        printf("%d ", buf[i]);
    }
    printf("\n");
    
    /************************************************************************/
    for(i = 0; i < 10; i++)
    {
        buf[i] = i;
    }
    
    shuffle3(buf, 10);
    
    for(i = 0; i < 10; i++)
    {
        printf("%d ", buf[i]);
    }
    printf("\n");
    
    /************************************************************************/
    for(i = 0; i < 10; i++)
    {
        buf[i] = i;
    }
    
    shuffle4(buf, 10);
    
    for(i = 0; i < 10; i++)
    {
        printf("%d ", buf[i]);
    }
    printf("\n");
    
    /************************************************************************/
    /*验证洗牌算法***********************************************************/
    /************************************************************************/
    unsigned int arr[3] = {1, 2, 3};
    unsigned int count[6];
    
    memset(count, 0, sizeof(count));
    
    // 蒙特卡罗
    int N = 1000000;
 
    for (i = 0; i < N; i++)
    {
        shuffle1(arr, 3);
        // 此时 arr 已被打乱
        
        if(arr[0] == 1 && arr[1] == 2 && arr[2] == 3)
        {
            count[0]++;
        }
        else if(arr[0] == 1 && arr[1] == 3 && arr[2] == 2)
        {
            count[1]++;
        }
        else if(arr[0] == 2 && arr[1] == 1 && arr[2] == 3)
        {
            count[2]++;
        }
        else if(arr[0] == 2 && arr[1] == 3 && arr[2] == 1)
        {
            count[3]++;
        }
        else if(arr[0] == 3 && arr[1] == 1 && arr[2] == 2)
        {
            count[4]++;
        }
        else if(arr[0] == 3 && arr[1] == 2 && arr[2] == 1)
        {
            count[5]++;
        }
    }
    
    for (i = 0; i < 6; i++)
    {
        printf("%d:%d %f\n", i, count[i], (double)count[i]/N);
    }
   
    return 0;
}