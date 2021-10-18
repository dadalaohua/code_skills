#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
#include "kavl.h"
 
struct my_node {
    char key;
    KAVL_HEAD(struct my_node) head;
};
#define my_cmp(p, q) (((q)->key < (p)->key) - ((p)->key < (q)->key))
KAVL_INIT(my, struct my_node, head, my_cmp)

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
    generic intrusive AVL tree additionally supporting counting
    额外支持计数的通用侵入式 AVL 树
    
    inserting letters "MNOLKQOPHIA" in order
    按顺序插入字母“MNOLKQOPHIA”
    
    运行结果
    AHIKLMNOPQ
*/
int main(int argc, char* argv[])
{
    const char *str = "MNOLKQOPHIA"; // from wiki, except a duplicate
    struct my_node *root = 0;
    int i, l = strlen(str);
    for (i = 0; i < l; ++i) {        // insert in the input order 按输入顺序插入
        struct my_node *q, *p = malloc(sizeof(*p));
        p->key = str[i];
        q = kavl_insert(my, &root, p, 0);
        if (p != q) free(p);         // if already present, free 如果已经存在，释放
    }
    kavl_itr_t(my) itr;
    kavl_itr_first(my, root, &itr);  // place at first 首先放置
    do {                             // traverse 遍历
        const struct my_node *p = kavl_at(&itr);
        putchar(p->key);
        free((void*)p);              // free node 释放节点
    } while (kavl_itr_next(my, &itr));
    putchar('\n');
    
    return 0;
}