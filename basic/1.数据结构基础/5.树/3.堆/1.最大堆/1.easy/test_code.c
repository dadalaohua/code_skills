#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define MAX_ELEMENTS 20
#define HEAP_FULL(n) (MAX_ELEMENTS - 1 == n)
#define HEAP_EMPTY(n) (!n)
typedef struct {
    int key;
}element;

element heapbuf[MAX_ELEMENTS];
/************************************************************************/
/*                                                                      */
/************************************************************************/
//最大堆的插入
void insert_max_heap(element *heap, element item) {
    int *total = &((*heap).key);
    
    if(HEAP_FULL(*total)){
        return;
    }
    
    int i = ++(*total);
    for(;(i != 1) && (item.key > heap[i/2].key);i = i / 2){ // i ≠ 1是因为数组的第一个元素并没有保存堆结点
        heap[i] = heap[i/2];    // 这里其实和递归操作类似，就是去找父结点
    }
    heap[i] = item;
}

//最大堆的删除
element delete_max_heap(element *heap) {
    int parent, child;
    element temp, item;
    int *total = &((*heap).key);
    
    if(*total < 1){
        item.key = 0;
        return item;
    }
    
    temp = heap[*total];
    *total -= 1;
    item = heap[1];
    parent = 1,child=2;
    for(;child <= *total; child = child * 2) {
        if( (child < *total) && heap[child].key < heap[child+1].key){    // 这一步是为了看当前结点是左子结点大还是右子结点大，然后选择较大的那个子结点
            child++;
        }
        if(temp.key >= heap[child].key){
            break;
        }
        heap[parent] = heap[child]; //这就是上图中第二步和第三步中黄色部分操作
        parent = child; // 这其实就是一个递归操作，让parent指向当前子树的根结点
    }
    heap[parent] = temp;
    
    return item;
}

//创建最大堆
void create_max_heap(element *heap) {
    int total = heap->key;
    
    // 求倒数第一个非叶子结点
    int child = 2,parent = 1;
    for (int node = total/2; node > 0; node--) {
        parent = node;
        child = 2 * node;
        element temp = *(heap + parent);
        for (; child <= total; child *= 2) {
            if (child+1 <= total && (*(heap + child)).key < (*(heap + child + 1)).key) {
                child++;
            }
            if (temp.key > (*(heap + child)).key) {
                break;
            }
            *(heap + parent) = *(heap + child);
            parent = child;
        }
        *(heap + parent) = temp;
    }
}

//创建二叉树
//数组的0位作为哨兵，标记二叉树的大小
int create_binary_tree(element *heap, int *items, int size)
{
    int total = 1;
    
    if (!items)
        return 0;
    
    element *heap_size = heap;
    heap++;
    
    for (int i = 0; i < size; i++) {
        heap_size->key = total++;
        heap->key      = *items++;
        heap++;
    }
    
    return 1;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int items[] = {79,66,43,83,30,87,38,55,91,72,49,9};
    element *position = heapbuf;

    // 创建二叉树
    create_binary_tree(position, items, sizeof(items)/sizeof(int));
    for (int i = 0; (*(position+i)).key > 0; i++) {
        printf("heap element %d is %d\n", i, (*(position + i)).key);
    }
    printf("\n");
    
    // 创建最大堆
    create_max_heap(position);
    for (int i = 0; (*(position+i)).key > 0; i++) {
        printf("heap element %d is %d\n", i, (*(position + i)).key);
    }
    printf("\n");
    
    //插入值
    element num;
    num.key = 100;
    insert_max_heap(position, num);
    
    printf("heap element len %d \n", position->key);
    for (int i = 1; i <= position->key; i++) {
        printf("heap element %d is %d\n", i, (*(position + i)).key);
    }
    printf("\n");
    
    //删除值
    num = delete_max_heap(position);
    printf("delete max heap %d\n", num.key);
    printf("heap element len %d \n", position->key);
    for (int i = 1; i <= position->key; i++) {
        printf("heap element %d is %d\n", i, (*(position + i)).key);
    }
    printf("\n");
    
    //删除值
    num = delete_max_heap(position);
    printf("delete max heap %d %d\n", num.key, position->key);
    printf("heap element len %d \n", position->key);
    for (int i = 1; i <= position->key; i++) {
        printf("heap element %d is %d\n", i, (*(position + i)).key);
    }
    printf("\n");
    
    //删除值
    num = delete_max_heap(position);
    printf("delete max heap %d %d\n", num.key, position->key);
    printf("heap element len %d \n", position->key);
    for (int i = 1; i <= position->key; i++) {
        printf("heap element %d is %d\n", i, (*(position + i)).key);
    }
    printf("\n");
    
    //删除值
    int len = position->key;
    for (int i = 0; i < len; i++) {
        num = delete_max_heap(position);
        printf("delete max heap %d %d\n", num.key, position->key);
    }
    printf("\n");
    
    return 0;
}