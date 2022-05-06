#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/


/************************************************************************/
/*                                                                      */
/************************************************************************/
//https://blog.csdn.net/fanxianchao_2012/article/details/108167253
int main(int argc, char* argv[])
{
    /*
        srandom :void srandom(unsigned int seed);
        设置随机数种子；
        srandom()用来设置random()产生随机数时的随机数种子。参数seed必须是个整数，通常可以利用getpid()
        或time(0)的返回值来当作seed，如果第次seed都设相同值，random()所产生的随机数值每次就会一样；
        
        random :long int random(void);
        产生随机数；
        random()会返回一随机数，范围在0~RAND_MAX之间。在调用此函数产生随机数前，必须先利用srandom()设好随机数
        种子，如果未设置随机数种子，random()在调用时会自动设置随机数种子为1。
        返回0~RAND_MAX之间的随机数值。
    */
    //srand(time(NULL));
    srandom(time(NULL));
    printf("Random number in the 0-99 range: %ld\n", random() % 100);
    printf("\n");
    
    /*
        initstate :char *initstate(unsigned int seed, char *state, int n);
        建立随机数状态数组；
        initstate()用来初始化random()所使用的数组，参数n为数组的大小，
        参数seed为初始化的随机数种子；
        返回调用initstate()前random()所使用的数组；
        EINVAL 参数state数组大小不足8个字符长；
        
        setstate :char *setstate(char *state);
        建立随机数状态数组；
        setstate()用来建立random()所使用的随机数状态数组。参数state指向新的随机数数组，
        此数组会供产生随机数的函数使用；
        返回调用setstate()前的random()所使用的数组；
    */
    char state[256];
    initstate(123, state, sizeof(state));
    printf("Random number in the 0-99 range: %ld\n", random() % 100);
    printf("Random number in the 0-99 range: %ld\n", random() % 100);
    printf("Random number in the 0-99 range: %ld\n", random() % 100);
    printf("\n");
    initstate(321, state, sizeof(state));
    printf("Random number in the 0-99 range: %ld\n", random() % 100);
    printf("Random number in the 0-99 range: %ld\n", random() % 100);
    printf("Random number in the 0-99 range: %ld\n", random() % 100);
    printf("\n");
    
    char state2[256];
    initstate(123, state2, sizeof(state2));
    printf("%ld\n", random() % 100);
    printf("\n");
    
    //修改
    char state3[256];
    char *saved = initstate(321, state3, sizeof(state3));
    printf("%ld\n", random() % 100);
    printf("%ld\n", random() % 100);
    printf("\n");
    
    //恢复成继续按initstate(123, state2, sizeof(state2));之后的随机数
    saved = setstate(saved);
    printf("%ld\n", random() % 100);
    printf("%ld\n", random() % 100);
    
    return 0;
}
