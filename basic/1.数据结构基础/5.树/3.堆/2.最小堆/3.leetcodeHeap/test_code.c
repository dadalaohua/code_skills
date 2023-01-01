#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
https://leetcode.cn/problems/kth-largest-element-in-a-stream/solutions/600598/shu-ju-liu-zhong-de-di-k-da-yuan-su-by-l-woz8/
*/
/************************************************************************/
/*                                                                      */
/************************************************************************/
struct Heap {
    int* heap;
    int heapSize;
    bool (*cmp)(int, int);
};

void Heapinit(struct Heap* obj, int n, bool (*cmp)(int, int)) {
    obj->heap = malloc(sizeof(int) * (n + 1));
    obj->heapSize = 0;
    obj->cmp = cmp;
}

void Heapfree(struct Heap* obj) {
    free(obj->heap);
}

bool cmp(int a, int b) {
    return a > b;
}

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b, *b = tmp;
}

void push(struct Heap* obj, int x) {
    int p = ++(obj->heapSize), q = p >> 1;
    obj->heap[p] = x;
    while (q) {
        if (!obj->cmp(obj->heap[q], obj->heap[p])) {
            break;
        }
        swap(&(obj->heap[q]), &(obj->heap[p]));
        p = q, q = p >> 1;
    }
}

void pop(struct Heap* obj) {
    swap(&(obj->heap[1]), &(obj->heap[(obj->heapSize)--]));
    int p = 1, q = p << 1;
    while (q <= obj->heapSize) {
        if (q + 1 <= obj->heapSize) {
            if (obj->cmp(obj->heap[q], obj->heap[q + 1])) {
                q++;
            }
        }
        if (!obj->cmp(obj->heap[p], obj->heap[q])) {
            break;
        }
        swap(&(obj->heap[q]), &(obj->heap[p]));
        p = q, q = p << 1;
    }
}

int top(struct Heap* obj) {
    return obj->heap[1];
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
int main(int argc, char* argv[])
{
    struct Heap obj;
    Heapinit(&obj, 10, cmp);
    for(int i = 0; i < 10; i++) {
        push(&obj, i);
    }
    
    for(int i = 0; i < 10; i++) {
        printf("top %d\n", top(&obj));
        pop(&obj);
    }
    
    Heapfree(&obj);
    
    return 0;
}