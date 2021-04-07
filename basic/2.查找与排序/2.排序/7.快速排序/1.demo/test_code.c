#include <stdio.h>

void swap(int *a,int *b)
{                            /*序列中元素位置的交换*/
  int tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}

/*快速排序, 递增排序*/
void quicksort_inc(int k[], int s, int t)       /*快速排序*/
{
    int i,j;
    if(s<t){
        i = s;
        j = t+1;
        while(1){
            do i++;
            while(!(k[s]<=k[i] || i==t));        /*重复执行i++操作*/
            do j--;
            while(!(k[s]>=k[j] || j==s));        /*重复执行j--操作*/
            if(i<j)
                swap(&k[i],&k[j]);               /*交换k[i]和k[j]的位置*/
            else
                break;

        }
        swap(&k[s],&k[j]);                       /*交换基准元素与k[j]的位置*/
        quicksort_inc(k,s,j-1);                  /*递归排序基准元素前面的子序列*/
        quicksort_inc(k,j+1,t);                  /*递归排序基准元素后面的子序列*/
    }
}

/*快速排序, 递减排序*/
void quicksort_dec(int k[], int s, int t)        /*快速排序*/
{
    int i,j;
    if(s<t){
        i = s;
        j = t+1;
        while(1){
            do i++;
            while(!(k[s]>=k[i] || i==t));        /*重复执行i++操作*/
            do j--;
            while(!(k[s]<=k[j] || j==s));        /*重复执行j--操作*/
            if(i<j)
                swap(&k[i],&k[j]);               /*交换k[i]和k[j]的位置*/
            else
                break;

        }
        swap(&k[s],&k[j]);                       /*交换基准元素与k[j]的位置*/
        quicksort_dec(k,s,j-1);                  /*递归排序基准元素前面的子序列*/
        quicksort_dec(k,j+1,t);                  /*递归排序基准元素后面的子序列*/
    }
}

int main(int argc, char* argv[])
{ 
    int i, buf[10] = {2,5,6,3,-7,8,0,9,12,1};           /*初始化序列*/
    
    printf("The orginal data array is\n") ;
    for(i = 0; i < 10; i++)                             /*显示原序列之中的元素*/
        printf("%d ",buf[i]);
        
    quicksort_inc(buf, 0, 9);                           /*快速排序*/
    
    printf("\nThe result of quick sorting for the array is\n");
    for(i = 0; i < 10; i++)
        printf("%d ",buf[i]); 
    
    printf("\n"); 
    
    quicksort_dec(buf, 0, 9);                           /*快速排序*/
    
    printf("\nThe result of quick sorting for the array is\n");
    for(i = 0; i < 10; i++)
        printf("%d ",buf[i]); 
    
    printf("\n"); 
    
    return 0;
}