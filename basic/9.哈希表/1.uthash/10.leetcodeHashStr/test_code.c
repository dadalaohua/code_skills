#include <stdio.h>
#include <stdbool.h>
#include "uthash.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef struct {
    char *key;
    UT_hash_handle hh;
} HashItem;

HashItem *hashFindItem(HashItem **obj, const char *key) {
    HashItem *pEntry = NULL;
    HASH_FIND_STR(*obj, key, pEntry);
    return pEntry;
}

bool hashAddItem(HashItem **obj, const char* key) {
    if (hashFindItem(obj, key)) {
        return false;
    }
    HashItem *pEntry = (HashItem *)malloc(sizeof(HashItem));
    pEntry->key = (char *)key;
    HASH_ADD_STR(*obj, key, pEntry);
    return true;
}

void hashFree(HashItem **obj) {
    HashItem *curr = NULL, *tmp = NULL;
    HASH_ITER(hh, *obj, curr, tmp) {
        HASH_DEL(*obj, curr);
        free(curr->key);
        free(curr);
    }
}

int hashCount(HashItem **obj) {
    return HASH_COUNT(*obj);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    const char *names[] = { "joe", "bob", "betty", "bill", "bob" "anne"};
    HashItem *keyhash = NULL;
    for(int i = 0; i < sizeof(names) / sizeof(char *); i++) {
        if(!hashFindItem(&keyhash, names[i])) {
            char *key = malloc(strlen(names[i]) + 1);
            strcpy(key, names[i]);
            hashAddItem(&keyhash, key);
            printf("add %d key %s\n", i, key);
        }
    }
    printf("\n");
    
    printf("count %d\n", hashCount(&keyhash));
    printf("\n");
    
    hashFree(&keyhash);
    
    return 0;
}