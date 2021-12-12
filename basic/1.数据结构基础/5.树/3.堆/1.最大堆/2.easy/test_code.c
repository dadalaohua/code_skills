#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void push(int *heap, int *heapSize, int x) {
    heap[++(*heapSize)] = x;
    for (int i = (*heapSize); i > 1 && heap[i] > heap[i >> 1]; i >>= 1) {
        swap(&heap[i], &heap[i >> 1]);
    }
    //heap[0] = *heapSize;
}

int pop(int *heap, int *heapSize) {
    int top = heap[1];
    int tmp = heap[1] = heap[(*heapSize)--];
    int i = 1, j = 2;
    while (j <= (*heapSize)) {
        if (j != (*heapSize) && heap[j + 1] > heap[j]) ++j;
        if (heap[j] > tmp) {
            heap[i] = heap[j];
            i = j;
            j = i << 1;
        } else {
            break;
        }
    }
    heap[i] = tmp;
    
    return top;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    #define HEAP_LEN 20
    
    int heap[HEAP_LEN + 1], heapSize = 0;
    int items[] = {79,66,43,83,30,87,38,55,91,72,49,9};
    
    //数据放进最大堆
    for(int i = 0; i < sizeof(items)/sizeof(int); i++){
        push(heap, &heapSize, items[i]);
    }
    
    //打印数据
    for(int i = 1; i <= heapSize; i++){
        printf("heap element %d is %d\n", i, heap[i]);
    }
    
    printf("\n");
    
    //从最大堆中取出数据
    int len = heapSize;
    for(int i = 1; i <= len; i++){
        printf("heap element %d is %d\n", i, pop(heap, &heapSize));
    }
    
    return 0;
}