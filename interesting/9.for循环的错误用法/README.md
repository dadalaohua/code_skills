代码7

#include<stdio.h>
int main(void)
{
    int arr[] = {5,4,3,2,1};
    for(int i = -1; i < sizeof(arr)/sizeof(int) - 1; i++)
    {
        printf("%d\n",arr[i+1]);
    }
    printf("end\n");
    return 0;
}
输出结果：

end
原因也很简单，sizeof(arr)/sizeof(int)的结果是unsigend， 
int类型的i 和unsigned比较，被转换为一个很大的unsigned数，所以for循环的条件不满足。