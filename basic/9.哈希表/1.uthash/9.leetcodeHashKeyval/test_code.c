#include <stdio.h>
#include <stdbool.h>
#include "uthash.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef struct {
    int key;
    int val;
    UT_hash_handle hh;
} HashItem; 

HashItem *hashFindItem(HashItem **obj, int key) {
    HashItem *pEntry = NULL;
    HASH_FIND_INT(*obj, &key, pEntry);
    return pEntry;
}

bool hashAddItem(HashItem **obj, int key, int val) {
    if (hashFindItem(obj, key)) {
        return false;
    }
    HashItem *pEntry = (HashItem *)malloc(sizeof(HashItem));
    pEntry->key = key;
    pEntry->val = val;
    HASH_ADD_INT(*obj, key, pEntry);
    return true;
}

bool hashSetItem(HashItem **obj, int key, int val) {
    HashItem *pEntry = hashFindItem(obj, key);
    if (!pEntry) {
        hashAddItem(obj, key, val);
    } else {
        pEntry->val = val;
    }
    return true;
}

int hashGetItem(HashItem **obj, int key, int defaultVal) {
    HashItem *pEntry = hashFindItem(obj, key);
    if (!pEntry) {
        return defaultVal;
    }
    return pEntry->val;
}

int hashCount(HashItem **obj) {
    return HASH_COUNT(*obj);
}

void hashFree(HashItem **obj) {
    HashItem *curr = NULL, *tmp = NULL;
    HASH_ITER(hh, *obj, curr, tmp) {
        HASH_DEL(*obj, curr);
        free(curr);
    }
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    HashItem *keyhash = NULL;
    for(int i = 0; i < 10; i++) {
        if(!hashFindItem(&keyhash, i)) {
            hashAddItem(&keyhash, i, i + 100);
            printf("add key %d val %d\n", i, i + 100);
        }
    }
    printf("\n");
    
    printf("count %d\n", hashCount(&keyhash));
    printf("\n");
    
    for(int i = 0; i < 15; i++) {
        printf("get key %d val %d\n", i, hashGetItem(&keyhash, i, -1));
    }
    printf("\n");
    
    for(int i = 5; i < 12; i++) {
        hashSetItem(&keyhash, i, i + 20);
        printf("set key %d val %d\n", i, i + 20);
    }
    printf("\n");
    
    for(int i = 0; i < 15; i++) {
        printf("get key %d val %d\n", i, hashGetItem(&keyhash, i, -1));
    }
    printf("\n");
    
    printf("count %d\n", hashCount(&keyhash));
    printf("\n");
    
    hashFree(&keyhash);
    
    return 0;
}