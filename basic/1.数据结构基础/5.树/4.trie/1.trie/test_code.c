#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//word 和 prefix 仅由小写英文字母组成

typedef struct Trie {
    struct Trie* children[26];
    bool isEnd;
} Trie;

//初始化前缀树对象
Trie* trieCreate() {
    Trie* ret = malloc(sizeof(Trie));
    memset(ret->children, 0, sizeof(ret->children));
    ret->isEnd = false;
    return ret;
}

//向前缀树中插入字符串 word
void trieInsert(Trie* obj, char* word) {
    int n = strlen(word);
    for (int i = 0; i < n; i++) {
        int ch = word[i] - 'a';
        if (obj->children[ch] == NULL) {
            obj->children[ch] = trieCreate();
        }
        obj = obj->children[ch];
    }
    obj->isEnd = true;
}

//如果字符串 word 在前缀树中，返回 true（即，在检索之前已经插入）；否则，返回 false 
bool trieSearch(Trie* obj, char* word) {
    int n = strlen(word);
    for (int i = 0; i < n; i++) {
        int ch = word[i] - 'a';
        if (obj->children[ch] == NULL) {
            return false;
        }
        obj = obj->children[ch];
    }
    return obj->isEnd;
}

//如果之前已经插入的字符串 word 的前缀之一为 prefix ，返回 true ；否则，返回 false 。
bool trieStartsWith(Trie* obj, char* prefix) {
    int n = strlen(prefix);
    for (int i = 0; i < n; i++) {
        int ch = prefix[i] - 'a';
        if (obj->children[ch] == NULL) {
            return false;
        }
        obj = obj->children[ch];
    }
    return true;
}

//释放前缀树
void trieFree(Trie* obj) {
    for (int i = 0; i < 26; i++) {
        if (obj->children[i]) {
            trieFree(obj->children[i]);
        }
    }
    free(obj);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    Trie *trie = trieCreate();
    bool ret;
    
    trieInsert(trie, "apple");
    ret = trieSearch(trie, "apple");   // 返回 True
    printf("Search %s ret %d\n", "apple", ret);
    
    ret = trieSearch(trie, "app");     // 返回 False
    printf("Search %s ret %d\n", "app", ret);
    
    ret = trieStartsWith(trie, "app"); // 返回 True
    printf("Search %s ret %d\n", "app", ret);
    
    trieInsert(trie, "app");
    ret = trieSearch(trie, "app");     // 返回 True
    printf("Search %s ret %d\n", "app", ret);
    
    trieFree(trie);
    
    return 0;
}