#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
https://leetcode.cn/problems/design-hashset/solutions/652778/she-ji-ha-xi-ji-he-by-leetcode-solution-xp4t/
*/
/************************************************************************/
/*                                                                      */
/************************************************************************/
struct List {
    int val;
    struct List* next;
};

void listPush(struct List* head, int x) {
    struct List* tmp = malloc(sizeof(struct List));
    tmp->val = x;
    tmp->next = head->next;
    head->next = tmp;
}

void listDelete(struct List* head, int x) {
    for (struct List* it = head; it->next; it = it->next) {
        if (it->next->val == x) {
            struct List* tmp = it->next;
            it->next = tmp->next;
            free(tmp);
            break;
        }
    }
}

bool listContains(struct List* head, int x) {
    for (struct List* it = head; it->next; it = it->next) {
        if (it->next->val == x) {
            return true;
        }
    }
    return false;
}

void listFree(struct List* head) {
    while (head->next) {
        struct List* tmp = head->next;
        head->next = tmp->next;
        free(tmp);
    }
}

const int base = 769;

int hash(int key) {
    return key % base;
}

typedef struct {
    struct List* data;
} MyHashSet;

MyHashSet* myHashSetCreate() {
    MyHashSet* ret = malloc(sizeof(MyHashSet));
    ret->data = malloc(sizeof(struct List) * base);
    for (int i = 0; i < base; i++) {
        ret->data[i].val = 0;
        ret->data[i].next = NULL;
    }
    return ret;
}

void myHashSetAdd(MyHashSet* obj, int key) {
    int h = hash(key);
    if (!listContains(&(obj->data[h]), key)) {
        listPush(&(obj->data[h]), key);
    }
}

void myHashSetRemove(MyHashSet* obj, int key) {
    int h = hash(key);
    listDelete(&(obj->data[h]), key);
}

bool myHashSetContains(MyHashSet* obj, int key) {
    int h = hash(key);
    return listContains(&(obj->data[h]), key);
}

void myHashSetFree(MyHashSet* obj) {
    for (int i = 0; i < base; i++) {
        listFree(&(obj->data[i]));
    }
    free(obj->data);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
输入：
["MyHashSet", "add", "add", "contains", "contains", "add", "contains", "remove", "contains"]
[[], [1], [2], [1], [3], [2], [2], [2], [2]]
输出：
[null, null, null, true, false, null, true, null, false]

MyHashSet myHashSet = new MyHashSet();
myHashSet.add(1);      // set = [1]
myHashSet.add(2);      // set = [1, 2]
myHashSet.contains(1); // 返回 True
myHashSet.contains(3); // 返回 False ，（未找到）
myHashSet.add(2);      // set = [1, 2]
myHashSet.contains(2); // 返回 True
myHashSet.remove(2);   // set = [1]
myHashSet.contains(2); // 返回 False ，（已移除）
*/
int main(int argc, char* argv[])
{
    MyHashSet* obj = myHashSetCreate();
    myHashSetAdd(obj, 1);
    myHashSetAdd(obj, 2);
    
    printf("contains(%d) %s\n", 1, myHashSetContains(obj, 1) ? "True" : "False");
    printf("contains(%d) %s\n", 3, myHashSetContains(obj, 3) ? "True" : "False");
    
    myHashSetAdd(obj, 2);
    printf("contains(%d) %s\n", 2, myHashSetContains(obj, 2) ? "True" : "False");
    
    myHashSetRemove(obj, 2);
    printf("contains(%d) %s\n", 2, myHashSetContains(obj, 2) ? "True" : "False");
    
    myHashSetFree(obj);
    return 0;
}