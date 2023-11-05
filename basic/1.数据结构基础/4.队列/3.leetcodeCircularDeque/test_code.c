#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
作者：LeetCode-Solution
链接：https://leetcode.cn/problems/shortest-subarray-with-sum-at-least-k/solution/he-zhi-shao-wei-k-de-zui-duan-zi-shu-zu-57ffq/
*/
/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef struct {
    int *elements;
    int rear, front;
    int capacity;
} MyCircularDeque;

MyCircularDeque* myCircularDequeCreate(int k) {
    MyCircularDeque *obj = (MyCircularDeque *)malloc(sizeof(MyCircularDeque));
    obj->capacity = k + 1;
    obj->rear = obj->front = 0;
    obj->elements = (int *)malloc(sizeof(int) * obj->capacity);
    return obj;
}

bool myCircularDequeInsertFront(MyCircularDeque* obj, int value) {
    if ((obj->rear + 1) % obj->capacity == obj->front) {
        return false;
    }
    obj->front = (obj->front - 1 + obj->capacity) % obj->capacity;
    obj->elements[obj->front] = value;
    return true;
}

bool myCircularDequeInsertLast(MyCircularDeque* obj, int value) {
    if ((obj->rear + 1) % obj->capacity == obj->front) {
        return false;
    }
    obj->elements[obj->rear] = value;
    obj->rear = (obj->rear + 1) % obj->capacity;
    return true;
}

bool myCircularDequeDeleteFront(MyCircularDeque* obj) {
    if (obj->rear == obj->front) {
        return false;
    }
    obj->front = (obj->front + 1) % obj->capacity;
    return true;
}

bool myCircularDequeDeleteLast(MyCircularDeque* obj) {
    if (obj->rear == obj->front) {
        return false;
    }
    obj->rear = (obj->rear - 1 + obj->capacity) % obj->capacity;
    return true;
}

int myCircularDequeGetFront(MyCircularDeque* obj) {
    if (obj->rear == obj->front) {
        return -1;
    }
    return obj->elements[obj->front];
}

int myCircularDequeGetRear(MyCircularDeque* obj) {
    if (obj->rear == obj->front) {
        return -1;
    }
    return obj->elements[(obj->rear - 1 + obj->capacity) % obj->capacity];
}

bool myCircularDequeIsEmpty(MyCircularDeque* obj) {
    return obj->rear == obj->front;
}

bool myCircularDequeIsFull(MyCircularDeque* obj) {
    return (obj->rear + 1) % obj->capacity == obj->front;
}

void myCircularDequeFree(MyCircularDeque* obj) {
    free(obj->elements);
    free(obj);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    //定义双端队列
    MyCircularDeque *queue = myCircularDequeCreate(6);
    
    //定义要用于传入的数据
    int items[] = {81, 13, 16, 38, 49, 67};
    int i;
    
    //查看当前的状态
    printf("\nempty : %d full : %d\n", myCircularDequeIsEmpty(queue), myCircularDequeIsFull(queue));
    
    //数据添加到队尾
    printf("\npush tail:\n");
    for(i = 0; i < sizeof(items)/sizeof(int); i++) {
        if(myCircularDequeInsertLast(queue, items[i]))
            printf("%d ", items[i]);
    }
    printf("\n");
    
    //查看当前的状态
    printf("\nempty : %d full : %d\n", myCircularDequeIsEmpty(queue), myCircularDequeIsFull(queue));
    
    //查看队首的数据
    printf("\npeek head %d\n", myCircularDequeGetFront(queue));
    
    //查看队尾的数据
    printf("\npeek tail %d\n", myCircularDequeGetRear(queue));
    
    //队首数据出队
    printf("\npop head:\n");
    for(i = 0; i < sizeof(items)/sizeof(int); i++) {
        printf("%d ", myCircularDequeGetFront(queue));
        myCircularDequeDeleteFront(queue);
    }
    printf("\n");
    
    //查看当前的状态
    printf("\nempty : %d full : %d\n", myCircularDequeIsEmpty(queue), myCircularDequeIsFull(queue));
    
    //数据添加到队首
    printf("\npush head:\n");
    for(i = 0; i < sizeof(items)/sizeof(int); i++) {
        if(myCircularDequeInsertFront(queue, items[i]))
            printf("%d ", items[i]);
    }
    printf("\n");
    
    //查看当前的状态
    printf("\nempty : %d full : %d\n", myCircularDequeIsEmpty(queue), myCircularDequeIsFull(queue));
    
    //查看队首的数据
    printf("\npeek head %d\n", myCircularDequeGetFront(queue));
    
    //查看队尾的数据
    printf("\npeek tail %d\n", myCircularDequeGetRear(queue));
    
    //队首数据出队
    printf("\npop head:\n");
    for(i = 0; i < sizeof(items)/sizeof(int); i++) {
        printf("%d ", myCircularDequeGetRear(queue));
        myCircularDequeDeleteLast(queue);
    }
    printf("\n");
    
    //查看当前的状态
    printf("\nempty : %d full : %d\n", myCircularDequeIsEmpty(queue), myCircularDequeIsFull(queue));
    
    //销毁双端队列
    myCircularDequeFree(queue);
    
    return 0;
}