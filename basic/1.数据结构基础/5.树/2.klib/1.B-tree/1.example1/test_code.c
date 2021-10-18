#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
#include "kbtree.h"

typedef struct {
    char *key;
    int count;
} elem_t;

#define elem_cmp(a, b) (strcmp((a).key, (b).key))
KBTREE_INIT(str, elem_t, elem_cmp)

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
    count distinct words on the command line
    在命令行上计算不同的单词
    
    例如
     ./test_code absent gulf graceful grey absent
    得到结果
    2       absent
    1       graceful
    1       grey
    1       gulf
*/

int main(int argc, char* argv[])
{
    kbtree_t(str) *b;
    elem_t *p, t;
    kbitr_t itr;
    int i;
    b = kb_init(str, KB_DEFAULT_SIZE);
    for (i = 1; i < argc; ++i) {
        // no need to allocate; just use pointer 无需分配；只需使用指针
        t.key = argv[i], t.count = 1;
        p = kb_getp(str, b, &t); // kb_get() also works 也有效
        // IMPORTANT: put() only works if key is absent 重要提示：put() 仅在 key 不存在时才有效
        if (!p) kb_putp(str, b, &t);
        else ++p->count;
    }
    // ordered tree traversal   //有序树遍历
    kb_itr_first(str, b, &itr); // get an iterator pointing to the first 得到一个指向第一个的迭代器
    for (; kb_itr_valid(&itr); kb_itr_next(str, b, &itr)) { // move on  继续前行 
        p = &kb_itr_key(elem_t, &itr);
        printf("%d\t%s\n", p->count, p->key);
    }
    kb_destroy(str, b);
    return 0;
}