#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/

https://leetcode.cn/problems/design-skiplist/solution/she-ji-tiao-biao-by-leetcode-solution-e8yh/

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define MAX(a, b) ((a) > (b) ? (a) : (b))
const int MAX_LEVEL = 32;
const int P_FACTOR = RAND_MAX >> 2;

typedef struct SkiplistNode {
    int val;
    int maxLevel;
    struct SkiplistNode **forward;
} SkiplistNode;

typedef struct {
    SkiplistNode *head;
    int level;
} Skiplist;

SkiplistNode *skiplistNodeCreat(int val, int maxLevel) {
    SkiplistNode *obj = (SkiplistNode *)malloc(sizeof(SkiplistNode));
    obj->val = val;
    obj->maxLevel = maxLevel;
    obj->forward = (SkiplistNode **)malloc(sizeof(SkiplistNode *) * maxLevel);
    for (int i = 0; i < maxLevel; i++) {
        obj->forward[i] = NULL;
    }
    return obj;
}

void skiplistNodeFree(SkiplistNode* obj) {
    if (obj->forward) {
        free(obj->forward);
        obj->forward = NULL;
        obj->maxLevel = 0;
    }
    free(obj);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
Skiplist* skiplistCreate() {
    Skiplist *obj = (Skiplist *)malloc(sizeof(Skiplist));
    obj->head = skiplistNodeCreat(-1, MAX_LEVEL);
    obj->level = 0;
    srand(time(NULL));
    return obj;
}

static inline int randomLevel() {
    int lv = 1;
    /* 随机生成 lv */
    while (rand() < P_FACTOR && lv < MAX_LEVEL) {
        lv++;
    }
    return lv;
}

bool skiplistSearch(Skiplist* obj, int target) {
    SkiplistNode *curr = obj->head;
    for (int i = obj->level - 1; i >= 0; i--) {
        /* 找到第 i 层小于且最接近 target 的元素*/
        while (curr->forward[i] && curr->forward[i]->val < target) {
            curr = curr->forward[i];
        }
    }
    curr = curr->forward[0];
    /* 检测当前元素的值是否等于 target */
    if (curr && curr->val == target) {
        return true;
    } 
    return false;
}

void skiplistAdd(Skiplist* obj, int num) {
    SkiplistNode *update[MAX_LEVEL];
    SkiplistNode *curr = obj->head;
    for (int i = obj->level - 1; i >= 0; i--) {
        /* 找到第 i 层小于且最接近 num 的元素*/
        while (curr->forward[i] && curr->forward[i]->val < num) {
            curr = curr->forward[i];
        }
        update[i] = curr;
    }
    int lv = randomLevel();
    if (lv > obj->level) {
        for (int i = obj->level; i < lv; i++) {
            update[i] = obj->head;
        }
        obj->level = lv;
    }
    SkiplistNode *newNode = skiplistNodeCreat(num, lv);
    for (int i = 0; i < lv; i++) {
        /* 对第 i 层的状态进行更新，将当前元素的 forward 指向新的节点 */
        newNode->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = newNode;
    }
}

bool skiplistErase(Skiplist* obj, int num) {
    SkiplistNode *update[MAX_LEVEL];
    SkiplistNode *curr = obj->head;
    for (int i = obj->level - 1; i >= 0; i--) {
        /* 找到第 i 层小于且最接近 num 的元素*/
        while (curr->forward[i] && curr->forward[i]->val < num) {
            curr = curr->forward[i];
        }
        update[i] = curr;
    }
    curr = curr->forward[0];
    /* 如果值不存在则返回 false */
    if (!curr || curr->val != num) {
        return false;
    }
    for (int i = 0; i < obj->level; i++) {
        if (update[i]->forward[i] != curr) {
            break;
        } 
        /* 对第 i 层的状态进行更新，将 forward 指向被删除节点的下一跳 */
        update[i]->forward[i] = curr->forward[i];
    }
    skiplistNodeFree(curr);
    /* 更新当前的 level */
    while (obj->level > 1 && obj->head->forward[obj->level - 1] == NULL) {
        obj->level--;
    }
    return true;
}

void skiplistFree(Skiplist* obj) {
    for (SkiplistNode * curr = obj->head; curr; ) {
        SkiplistNode *prev = curr;
        curr = curr->forward[0];
        skiplistNodeFree(prev);
    }
    free(obj);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    Skiplist* obj = skiplistCreate();
    
    for(int i = 0; i < 10; i++) {
        skiplistAdd(obj, i);
    }
    
    for(int i = 5; i < 12; i++) {
        printf("%d : %d\n", i, skiplistSearch(obj, i));
    }
    printf("\n");
    
    for(int i = 5; i < 12; i++) {
        printf("%d : %d\n", i, skiplistErase(obj, i));
    }
    printf("\n");
    
    for(int i = 0; i < 10; i++) {
        printf("%d : %d\n", i, skiplistSearch(obj, i));
    }
    printf("\n");
    
    skiplistFree(obj);
    return 0;
}