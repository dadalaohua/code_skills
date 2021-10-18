#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
#include "kvec.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int arrayLen, i;
    
    //声明动态数组
    kvec_t(int) array;
    
    //初始化动态数组
    kv_init(array);
    
    //放入10个数据
    for(i = 0; i < 10; i++) {
        kv_push(int, array, i);
    }

    //获取动态数值的大小
    arrayLen = kv_size(array);
    printf("arrayLen : %d\n", arrayLen);
    
    //打印出所有数据
    for(i = 0; i < arrayLen; i++) {
        printf("%d : %d\n", i, kv_A(array, i));
    }
    
    printf("\n");
    
    //修改所有数据
    for(i = 0; i < arrayLen; i++) {
        kv_A(array, i) = i + 100;
    }
    
    printf("\n");
    
    //打印出所有数据
    for(i = 0; i < arrayLen; i++) {
        printf("%d : %d\n", i, kv_A(array, i));
    }
    
    printf("\n");
    
    //在特定位置插入数值，这里在20的位置插入
    kv_a(int, array, 20);
    kv_A(array, 20) = 20;
    
    //查看当前数组的大小和插入数据点的数值大小
    printf("%d : %d\n", kv_size(array), kv_A(array, 20));
    
    //销毁动态数组
    kv_destroy(array);
    
    return 0;
}