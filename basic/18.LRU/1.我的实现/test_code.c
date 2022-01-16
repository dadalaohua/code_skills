#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "uthash.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/
struct list_struct {
    int key;
    int value;
    struct list_struct *next, *prev;
};

struct hash_struct {
    int key;
    struct list_struct *list;
    UT_hash_handle hh;
};

typedef struct {
    int cnt;
    int capacity;
    struct list_struct list_head;
    struct hash_struct *hash;
} LRUCache;

LRUCache* lRUCacheCreate(int capacity) {
    LRUCache* obj = malloc(sizeof(LRUCache));
    obj->cnt = 0;
    obj->capacity = capacity;
    obj->list_head.next = &(obj->list_head);
    obj->list_head.prev = &(obj->list_head);
    obj->hash = NULL;
    return obj;
}

int lRUCacheGet(LRUCache* obj, int key) {
    struct hash_struct *s;
    HASH_FIND_INT(obj->hash, &key, s);
    if (s != NULL) {
        struct list_struct *tmp_list;
        s->list->prev->next = s->list->next;
        s->list->next->prev = s->list->prev;

        tmp_list = obj->list_head.prev;
        obj->list_head.prev->next = s->list;
        s->list->prev = tmp_list;
        s->list->next = &(obj->list_head);
        obj->list_head.prev = s->list;

        return s->list->value;
    }

    return -1;
}

void lRUCachePut(LRUCache* obj, int key, int value) {
    struct hash_struct *s;
    HASH_FIND_INT(obj->hash, &key, s);
    if (s != NULL) {
        struct list_struct *tmp_list;
        s->list->prev->next = s->list->next;
        s->list->next->prev = s->list->prev;

        tmp_list = obj->list_head.prev;
        obj->list_head.prev->next = s->list;
        s->list->prev = tmp_list;
        s->list->next = &(obj->list_head);
        obj->list_head.prev = s->list;
        
        s->list->value = value;
    } else {
        struct list_struct *tmp_list;

        if(obj->cnt == obj->capacity) {
            tmp_list = obj->list_head.next;
            obj->list_head.next->next->prev = &(obj->list_head);
            obj->list_head.next = tmp_list->next;
            HASH_FIND_INT(obj->hash, &(tmp_list->key), s);
            HASH_DEL(obj->hash, s);
            free(s);
            free(tmp_list);
        } else {
            obj->cnt++;
        }

        tmp_list = malloc(sizeof(struct list_struct));
        tmp_list->key = key;
        tmp_list->value = value;
        s = (struct hash_struct *)malloc(sizeof *s);
        s->key = key;
        s->list = tmp_list;
        HASH_ADD_INT(obj->hash, key, s);

        tmp_list = obj->list_head.prev;
        obj->list_head.prev->next = s->list;
        s->list->prev = tmp_list;
        s->list->next = &(obj->list_head);
        obj->list_head.prev = s->list;
    }
}

void lRUCacheFree(LRUCache* obj) {
    struct hash_struct *current_user, *tmp;

    HASH_ITER(hh, obj->hash, current_user, tmp) {
        HASH_DEL(obj->hash, current_user);
        free(current_user->list);
        free(current_user);
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