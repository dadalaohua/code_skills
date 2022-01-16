#include <stdio.h>

#include "uthash.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/
/* 
uthash底层本身就是用双向链表实现的hash
当达到容量时，先删除最久未使用的数据，这个最久未使用就在双向链表的表头
 */
struct hash_struct {
    int key;
    int value;
    UT_hash_handle hh;
};

typedef struct {
    int capacity;
    struct hash_struct *hash;
} LRUCache;

LRUCache* lRUCacheCreate(int capacity) {
    LRUCache* obj = malloc(sizeof(LRUCache));
    obj->capacity = capacity;
    obj->hash = NULL;
    return obj;
}

int lRUCacheGet(LRUCache* obj, int key) {
    struct hash_struct *user;
    HASH_FIND_INT(obj->hash, &key, user);
    if (user != NULL) {
        HASH_DEL(obj->hash, user);
        HASH_ADD_INT(obj->hash, key, user);
        return user->value;
    }
    return -1;
}

void lRUCachePut(LRUCache* obj, int key, int value) {
    struct hash_struct *user;
    HASH_FIND_INT(obj->hash, &key, user);
    if (user != NULL) {
        HASH_DEL(obj->hash, user);
        user->value = value;
        HASH_ADD_INT(obj->hash, key, user);
    } else {
        if(HASH_COUNT(obj->hash) == obj->capacity) {
            struct hash_struct *cur_user = NULL, *tmp = NULL;
            HASH_ITER(hh, obj->hash, cur_user, tmp) {
                HASH_DEL(obj->hash, cur_user);
                free(cur_user);
                break;
            }
        }

        user = (struct hash_struct *)malloc(sizeof *user);
        user->key = key;
        user->value = value;
        HASH_ADD_INT(obj->hash, key, user);
    }
}

void lRUCacheFree(LRUCache* obj) {
    struct hash_struct *user, *tmp;

    HASH_ITER(hh, obj->hash, user, tmp) {
        HASH_DEL(obj->hash, user);
        free(user);
    }

    free(obj);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    LRUCache* obj = lRUCacheCreate(2);
    
    lRUCachePut(obj, 1, 1);
    lRUCachePut(obj, 2, 2);
    printf("%d\n", lRUCacheGet(obj, 1));
    lRUCachePut(obj, 3, 3);
    printf("%d\n", lRUCacheGet(obj, 2));
    lRUCachePut(obj, 4, 4);
    printf("%d\n", lRUCacheGet(obj, 1));
    printf("%d\n", lRUCacheGet(obj, 3));
    printf("%d\n", lRUCacheGet(obj, 4));
    
    lRUCacheFree(obj);
    return 0;
}