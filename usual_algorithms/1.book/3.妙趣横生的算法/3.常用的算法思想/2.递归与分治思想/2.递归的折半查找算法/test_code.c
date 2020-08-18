#include <stdio.h>
#include <stdlib.h>

/****************************/
int bin_search(int key[],int low, int high,int k)
{
    int mid;
    if(low>high)
        return -1;
    else{
        mid = (low+high) / 2;
        if(key[mid]==k)
            return mid;
        if(k>key[mid])
            return bin_search(key,mid+1,high,k);    /*在序列的后半部分查找*/
        else
            return bin_search(key,low,mid-1,k);     /*在序列的前半部分查找*/
    }
}

/****************************/

int main(int argc, char* argv[])
{
    int n , i , addr;
    int A[10] = {2,3,5,7,8,10,12,15,19,21};         /*初始化数组序列A*/
    printf("The contents of the Array A[10] are\n");
    for(i=0;i<10;i++)
    printf("%d ",A[i]);                             /*显示数组A中的内容*/
    printf("\nPlease input a interger for search\n");
    scanf("%d",&n);                                 /*输入待查找的元素*/
    addr = bin_search(A,0,9,n);
    if(-1 != addr)                                  /*查找成功*/
    printf("%d is at the %dth unit is array A\n ",n,addr);
    else printf("There is no %d in array A\n",n);   /*查找失败*/
    printf("\n");
    
    return 0;
}
