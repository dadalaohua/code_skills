/*
 * Copyright (c) 2021, hongjh
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef unsigned char          uint8_t;
typedef unsigned short         uint16_t;
typedef unsigned int           uint32_t;
typedef signed char            int8_t;
typedef signed short           int16_t;
typedef signed int             int32_t;
/************************************************************************/
/*                                                                      */
/************************************************************************/
//使用前需要设置以下参数

//存储空间有多大
#define STATIC_DOUBLY_LIST_BUF_VALID_LEN    62

//使用的数据类型
typedef uint32_t itemtype;
/************************************************************************/
/*                                                                      */
/************************************************************************/
#define STATIC_DOUBLY_LIST_BUF_LEN  (STATIC_DOUBLY_LIST_BUF_VALID_LEN + 2)
#define STATIC_DOUBLY_LIST_END      (STATIC_DOUBLY_LIST_BUF_LEN - 1)

#if STATIC_DOUBLY_LIST_BUF_LEN > 65536
typedef struct
{
    itemtype    data;
    uint32_t    prev;
    uint32_t    next;
} static_doubly_list, static_doubly_list_buf[STATIC_DOUBLY_LIST_BUF_LEN];
#elif STATIC_DOUBLY_LIST_BUF_LEN > 256
typedef struct
{
    itemtype    data;
    uint16_t    prev;
    uint16_t    next;
} static_doubly_list, static_doubly_list_buf[STATIC_DOUBLY_LIST_BUF_LEN];
#else
typedef struct
{
    itemtype    data;
    uint8_t     prev;
    uint8_t     next;
} static_doubly_list, static_doubly_list_buf[STATIC_DOUBLY_LIST_BUF_LEN];
#endif

/**
 * 
 * @par Description:
 * 链表缓冲区初始化
 * 
 * @param list  链表
 * 
 * @retval None.
 * 
 */
static inline void static_list_buf_init(static_doubly_list_buf list)
{
    int i;
    
    for (i = 0; i < (STATIC_DOUBLY_LIST_BUF_LEN-2); i++)
        list[i].next = i + 1;
    
    list[STATIC_DOUBLY_LIST_BUF_LEN-2].next = 0;
    
    list[STATIC_DOUBLY_LIST_BUF_LEN-1].next = STATIC_DOUBLY_LIST_BUF_LEN-1;
    list[STATIC_DOUBLY_LIST_BUF_LEN-1].prev = STATIC_DOUBLY_LIST_BUF_LEN-1;
}

/**
 * 
 * @par Description:
 * 链表初始化
 * 
 * @param list      链表
 * @param cursor    需要初始化的游标位置
 * 
 * @retval None.
 * 
 */
static inline void static_list_init(static_doubly_list_buf list, int32_t cursor)
{
    list[cursor].next = cursor;
    list[cursor].prev = cursor;
}

/**
 * 
 * @par Description:
 * 申请链表游标
 * 
 * @param list      链表
 * 
 * @retval cursor.  游标位置
 * 
 */
static inline int32_t static_list_malloc(static_doubly_list_buf list)
{
    int32_t cursor = list[0].next;
    
    if(list[0].next)
        list[0].next = list[cursor].next;

    return cursor;
}

/**
 * 
 * @par Description:
 * 释放链表游标
 * 
 * @param list      链表
 * @param cursor    要进行释放的游标位置
 * 
 * @retval None.
 * 
 */
static inline void static_list_free(static_doubly_list_buf list, int32_t cursor)
{
    list[cursor].next = list[0].next;
    list[0].next = cursor;
}

/**
 * 
 * @par Description:
 * 链表是否为空
 * 
 * @param list      链表
 * 
 * @retval TRUE  静态双向链表为空.
 * @retval FALSE 静态双向链表不为空.
 * 
 */
static inline int32_t static_list_is_empty(static_doubly_list_buf list)
{
    return (list[STATIC_DOUBLY_LIST_END].next == STATIC_DOUBLY_LIST_END);
}

/**
 * 
 * @par Description:
 * 链表是否已满
 * 
 * @param list      链表
 * 
 * @retval TRUE  静态双向链表已满.
 * @retval FALSE 静态双向链表不为满.
 * 
 */
static inline int32_t static_list_is_full(static_doubly_list_buf list)
{
    return (list[0].next == 0);
}

/**
 * 
 * @par Description:
 * 向链表中添加结点
 * 
 * @param list      链表
 * @param target    要添加在哪个游标位置之后
 * @param cursor    所要添加的游标
 * 
 * @retval None.
 * 
 */
static inline void static_list_add(static_doubly_list_buf list, int32_t target, int32_t cursor)
{
    list[cursor].next = list[target].next;
    list[cursor].prev = target;
    
    list[(list[target].next)].prev = cursor;
    list[target].next = cursor;
}

/**
 * 
 * @par Description:
 * 向链表头中添加结点
 * 
 * @param list      链表
 * @param cursor    所要添加的游标
 * 
 * @retval None.
 * 
 */
static inline void static_list_head_insert(static_doubly_list_buf list, int32_t cursor)
{
    static_list_add(list, STATIC_DOUBLY_LIST_END, cursor);
}

/**
 * 
 * @par Description:
 * 向链表尾中添加结点
 * 
 * @param list      链表
 * @param cursor    所要添加的游标
 * 
 * @retval None.
 * 
 */
static inline void static_list_tail_insert(static_doubly_list_buf list, int32_t cursor)
{
    static_list_add(list, list[STATIC_DOUBLY_LIST_END].prev, cursor);
}

/**
 * 
 * @par Description:
 * 从链表中删除结点
 * 
 * @param list      链表
 * @param cursor    所要删除的游标
 * 
 * @retval None.
 * 
 */
static inline void static_list_delete(static_doubly_list_buf list, int32_t cursor)
{
    list[(list[cursor].next)].prev = list[cursor].prev;
    list[(list[cursor].prev)].next = list[cursor].next;
    list[cursor].next = 0;
    list[cursor].prev = 0;
}

/**
 * 
 * @par Description:
 * 从链表中删除并释放结点
 * 
 * @param list      链表
 * @param cursor    所要删除并释放的游标
 * 
 * @retval None.
 * 
 */
static inline void static_list_delete_and_free(static_doubly_list_buf list, int32_t cursor)
{
    static_list_delete(list, cursor);
    static_list_free(list, cursor);
}

/**
 * 
 * @par Description:
 * 从链表中删除并释放头结点
 * 
 * @attention
 * 未做保护，如果为空链表则会出错
 * 
 * @param list      链表
 * 
 * @retval None.
 * 
 */
static inline void static_list_remove_head(static_doubly_list_buf list)
{
    static_list_delete_and_free(list, list[STATIC_DOUBLY_LIST_END].next);
}

/**
 * 
 * @par Description:
 * 从链表中删除并释放尾结点
 * 
 * @attention
 * 未做保护，如果为空链表则会出错
 * 
 * @param list      链表
 * 
 * @retval None.
 * 
 */
static inline void static_list_remove_tail(static_doubly_list_buf list)
{
    static_list_delete_and_free(list, list[STATIC_DOUBLY_LIST_END].prev);
}

/**
 * 
 * @par Description:
 * 从链表中删除并返回头结点的游标
 * 
 * @param list      链表
 * 
 * @retval None.
 * 
 */
static inline int32_t static_list_get_and_remove_head_cursor(static_doubly_list_buf list)
{
    uint32_t cursor = list[STATIC_DOUBLY_LIST_END].next;
    
    if(cursor == STATIC_DOUBLY_LIST_END)
        return 0;
    
    static_list_delete(list, list[STATIC_DOUBLY_LIST_END].next);
    
    return cursor;
}

/**
 * 
 * @par Description:
 * 从链表中删除并返回尾结点的游标
 * 
 * @param list      链表
 * 
 * @retval None.
 * 
 */
static inline int32_t static_list_get_and_remove_tail_cursor(static_doubly_list_buf list)
{
    uint32_t cursor = list[STATIC_DOUBLY_LIST_END].prev;
    
    if(cursor == STATIC_DOUBLY_LIST_END)
        return 0;
    
    static_list_delete(list, list[STATIC_DOUBLY_LIST_END].prev);
    
    return cursor;
}

/**
 * 
 * @par Description:
 * 遍历链表
 * 
 * @param item  游标变量
 * @param list  链表
 * 
 * @retval None.
 * 
 */
#define STATIC_LIST_FOR_EACH(item, list)            \
    for (item = list[STATIC_DOUBLY_LIST_END].next;  \
         (item) != (STATIC_DOUBLY_LIST_END);        \
         item = list[item].next)

/**
 * 
 * @par Description:
 * 安全的遍历链表，可以在遍历中删除结点
 * 
 * @param item      游标变量
 * @param nextitem  游标变量
 * @param list      链表
 * 
 * @retval None.
 * 
 */
#define STATIC_LIST_FOR_EACH_SAFE(item, nextitem, list)                         \
    for (item = list[STATIC_DOUBLY_LIST_END].next, nextitem = list[item].next;  \
         (item) != (STATIC_DOUBLY_LIST_END);                                    \
         item = nextitem, nextitem = list[item].next)

/**
 * 
 * @par Description:
 * 反向遍历链表
 * 
 * @param item  游标变量
 * @param list  链表
 * 
 * @retval None.
 * 
 */
#define STATIC_LIST_FOR_EACH_REVERSE(item, list)            \
    for (item = list[STATIC_DOUBLY_LIST_END].prev;  \
         (item) != (STATIC_DOUBLY_LIST_END);        \
         item = list[item].prev)

/**
 * 
 * @par Description:
 * 安全的反向遍历链表，可以在遍历中删除结点
 * 
 * @param item      游标变量
 * @param nextitem  游标变量
 * @param list      链表
 * 
 * @retval None.
 * 
 */
#define STATIC_LIST_FOR_EACH_SAFE_REVERSE(item, previtem, list)                         \
    for (item = list[STATIC_DOUBLY_LIST_END].prev, previtem = list[item].prev;  \
         (item) != (STATIC_DOUBLY_LIST_END);                                    \
         item = previtem, previtem = list[item].prev)

/**
 * 
 * @par Description:
 * 遍历链表获取数据
 * 
 * @param item      游标变量
 * @param list      链表
 * @param member    数据成员指针
 * @param element   数据成员名称
 * 
 * @retval None.
 * 
 */
#define STATIC_LIST_FOR_EACH_ENTRY_ELEMENT(item, list, member, element)             \
    for (item = list[STATIC_DOUBLY_LIST_END].next, member = &(list[item].element);  \
         (item) != (STATIC_DOUBLY_LIST_END);                                        \
         item = list[item].next, member = &(list[item].element))

/**
 * 
 * @par Description:
 * 反向遍历链表获取数据
 * 
 * @param item      游标变量
 * @param list      链表
 * @param member    数据成员指针
 * @param element   数据成员名称
 * 
 * @retval None.
 * 
 */
#define STATIC_LIST_FOR_EACH_ENTRY_ELEMENT_REVERSE(item, list, member, element)     \
    for (item = list[STATIC_DOUBLY_LIST_END].prev, member = &(list[item].element);  \
         (item) != (STATIC_DOUBLY_LIST_END);                                        \
         item = list[item].prev, member = &(list[item].element))

/**
 * 
 * @par Description:
 * 安全的遍历链表获取数据，可以在遍历中删除结点
 * 
 * @param item      游标变量
 * @param nextitem  游标变量
 * @param list      链表
 * @param member    数据成员指针
 * @param element   数据成员名称
 * 
 * @retval None.
 * 
 */
#define STATIC_LIST_FOR_EACH_ENTRY_ELEMENT_SAFE(item, nextitem, list, member, element)                          \
    for (item = list[STATIC_DOUBLY_LIST_END].next, nextitem = list[item].next, member = &(list[item].element);  \
         (item) != (STATIC_DOUBLY_LIST_END);                                                                    \
         item = nextitem, nextitem = list[item].next, member = &(list[item].element))

/**
 * 
 * @par Description:
 * 安全的反向遍历链表获取数据，可以在遍历中删除结点
 * 
 * @param item      游标变量
 * @param previtem  游标变量
 * @param list      链表
 * @param member    用于保存数据成员的指针
 * @param element   数据成员名称
 * 
 * @retval None.
 * 
 */
#define STATIC_LIST_FOR_EACH_ENTRY_ELEMENT_SAFE_REVERSE(item, previtem, list, member, element)                  \
    for (item = list[STATIC_DOUBLY_LIST_END].prev, previtem = list[item].prev, member = &(list[item].element);  \
         (item) != (STATIC_DOUBLY_LIST_END);                                                                    \
         item = previtem, previtem = list[item].prev, member = &(list[item].element))

/**
 * 
 * @par Description:
 * 查看链表头的数据
 * 
 * @attention
 * None.
 * 
 * @param list      链表
 * @param type      数据成员类型
 * @param element   数据成员名称
 * 
 * @retval 数据成员地址.
 * 
 */
#define STATIC_LIST_PEEK_HEAD_TYPE(list, type, element) ({              \
    type *__t;                                                          \
    if (list[STATIC_DOUBLY_LIST_END].next == STATIC_DOUBLY_LIST_END) {  \
        __t = NULL;                                                     \
    } else {                                                            \
        __t = &(list[list[STATIC_DOUBLY_LIST_END].next].element);       \
    }                                                                   \
    __t;                                                                \
})

/**
 * 
 * @par Description:
 * 查看链表尾的数据
 * 
 * @attention
 * None.
 * 
 * @param list      链表
 * @param type      数据成员类型
 * @param element   数据成员名称
 * 
 * @retval 数据成员地址.
 * 
 */
#define STATIC_LIST_PEEK_TAIL_TYPE(list, type, element) ({              \
    type *__t;                                                          \
    if (list[STATIC_DOUBLY_LIST_END].prev == STATIC_DOUBLY_LIST_END) {  \
        __t = NULL;                                                     \
    } else {                                                            \
        __t = &(list[list[STATIC_DOUBLY_LIST_END].prev].element);       \
    }                                                                   \
    __t;                                                                \
})

/**
 * 
 * @par Description:
 * 获取链表头的数据，并删除释放结点
 * 
 * @attention
 * 存在安全性问题，返回数据成员地址的时候，已将结点删除并释放了
 * 如果只用于删除并释放结点则无此问题
 * 
 * @param list      链表
 * @param type      数据成员类型
 * @param element   数据成员名称
 * 
 * @retval 数据成员地址.
 * 
 */
#define STATIC_LIST_REMOVE_HEAD_TYPE(list, type, element) ({                    \
    type *__t;                                                                  \
    if (list[STATIC_DOUBLY_LIST_END].next == STATIC_DOUBLY_LIST_END) {          \
        __t = NULL;                                                             \
    } else {                                                                    \
        __t = &(list[list[STATIC_DOUBLY_LIST_END].next].element);               \
        static_list_delete_and_free(list, list[STATIC_DOUBLY_LIST_END].next);   \
    }                                                                           \
    __t;                                                                        \
})

/**
 * 
 * @par Description:
 * 获取链表尾的数据，并删除结点
 * 如果只用于删除并释放结点则无此问题
 * 
 * @attention
 * 存在安全性问题，返回数据成员地址的时候，已将结点删除并释放了
 * 
 * @param list      链表
 * @param type      数据成员类型
 * @param element   数据成员名称
 * 
 * @retval 数据成员地址.
 * 
 */
#define STATIC_LIST_REMOVE_TAIL_TYPE(list, type, element) ({                    \
    type *__t;                                                                  \
    if (list[STATIC_DOUBLY_LIST_END].prev == STATIC_DOUBLY_LIST_END) {          \
        __t = NULL;                                                             \
    } else {                                                                    \
        __t = &(list[list[STATIC_DOUBLY_LIST_END].prev].element);               \
        static_list_delete_and_free(list, list[STATIC_DOUBLY_LIST_END].prev);   \
    }                                                                           \
    __t;                                                                        \
})

/**
 * 
 * @par Description:
 * 获取链表头的数据，并删除结点
 * 
 * @attention
 * None.
 * 
 * @param list      链表
 * @param element   数据成员名称
 * @param data      用于保存数据的变量
 * 
 * @retval TRUE  成功.
 * @retval FALSE 无数据.
 * 
 */
#define STATIC_LIST_REMOVE_HEAD_TYPE_SAFE(list, element, data) ({               \
    int __t;                                                                    \
    if (list[STATIC_DOUBLY_LIST_END].next == STATIC_DOUBLY_LIST_END) {          \
        __t = 0;                                                                \
    } else {                                                                    \
        memcpy(&data, &(list[list[STATIC_DOUBLY_LIST_END].next].element),       \
                sizeof(list[list[STATIC_DOUBLY_LIST_END].next].element));       \
        static_list_delete_and_free(list, list[STATIC_DOUBLY_LIST_END].next);   \
        __t = 1;                                                                \
    }                                                                           \
    __t;                                                                        \
})

/**
 * 
 * @par Description:
 * 获取链表尾的数据，并删除结点
 * 
 * @attention
 * None.
 * 
 * @param list      链表
 * @param element   数据成员名称
 * @param data      用于保存数据的变量
 * 
 * @retval TRUE  成功.
 * @retval FALSE 无数据.
 * 
 */
#define STATIC_LIST_REMOVE_TAIL_TYPE_SAFE(list, element, data) ({               \
    int __t;                                                                    \
    if (list[STATIC_DOUBLY_LIST_END].prev == STATIC_DOUBLY_LIST_END) {          \
        __t = 0;                                                                \
    } else {                                                                    \
        memcpy(&data, &(list[list[STATIC_DOUBLY_LIST_END].prev].element),       \
                sizeof(list[list[STATIC_DOUBLY_LIST_END].prev].element));       \
        static_list_delete_and_free(list, list[STATIC_DOUBLY_LIST_END].prev);   \
        __t = 1;                                                                \
    }                                                                           \
    __t;                                                                        \
})

/**
 * 
 * @par Description:
 * 将数据添加到链表头中，自动申请
 * 
 * @attention
 * None.
 * 
 * @param list      链表
 * @param element   数据成员名称
 * @param data      用于保存数据的变量
 * 
 * @retval cursor  游标.
 * 
 */
#define STATIC_LIST_ADD_HEAD_TYPE(list, element, data) ({                       \
    uint32_t cursor = static_list_malloc(list);                                 \
    if(cursor) {                                                                \
        memcpy(&(list[cursor].element), &data, sizeof(list[cursor].element));   \
        static_list_head_insert(list, cursor);                                  \
    }                                                                           \
    cursor;                                                                     \
})

/**
 * 
 * @par Description:
 * 将数据添加到链表尾中，自动申请
 * 
 * @attention
 * None.
 * 
 * @param list      链表
 * @param element   数据成员名称
 * @param data      用于保存数据的变量
 * 
 * @retval cursor  游标.
 * 
 */
#define STATIC_LIST_ADD_TAIL_TYPE(list, element, data) ({                       \
    uint32_t cursor = static_list_malloc(list);                                 \
    if(cursor) {                                                                \
        memcpy(&(list[cursor].element), &data, sizeof(list[cursor].element));   \
        static_list_tail_insert(list, cursor);                                  \
    }                                                                           \
    cursor;                                                                     \
})

/************************************************************************/
/*                                                                      */
/************************************************************************/
int main(int argc, char* argv[])
{
    int i;
    int cursor;
    int next_cursor;
    itemtype value;
    itemtype *p_value;
    
    //结构体初始化
    static_doubly_list_buf list_buf;
    
    //初始化
    static_list_buf_init(list_buf);
    
    //放入数值
    for (i=0; i < 10; i++)
    {
        value = i+10;
        //往链表队尾添加数据
        STATIC_LIST_ADD_TAIL_TYPE(list_buf, data, value);
        printf("Node %d has added to the list...\n", i+1);
    }
    printf("\n");
    
    //遍历链表 方式一
    printf("********************************\n");
    printf("遍历链表 方式一 测试\n");
    printf("********************************\n");
    i = 0;
    STATIC_LIST_FOR_EACH_ENTRY_ELEMENT(cursor, list_buf, p_value, data)
    {
        printf("Node %d's data: %d\n", i, *p_value);
        i++;
    }
    printf("\n");
    
    //遍历链表 方式二
    printf("********************************\n");
    printf("遍历链表 方式二 测试\n");
    printf("********************************\n");
    i = 0;
    STATIC_LIST_FOR_EACH_ENTRY_ELEMENT_SAFE(cursor, next_cursor, list_buf, p_value, data)
    {
        printf("Node %d's data: %d\n", i, *p_value);
        i++;
    }
    printf("\n");
    
    //遍历链表 方式三
    printf("********************************\n");
    printf("遍历链表 方式三 测试\n");
    printf("********************************\n");
    i = 0;
    STATIC_LIST_FOR_EACH(cursor, list_buf)
    {
        printf("Node %d's data: %d\n", i, list_buf[cursor].data);
        i++;
    }
    printf("\n");
    
    //遍历链表 方式四
    printf("********************************\n");
    printf("遍历链表 方式四 测试\n");
    printf("********************************\n");
    i = 0;
    STATIC_LIST_FOR_EACH_SAFE(cursor, next_cursor, list_buf)
    {
        printf("Node %d's data: %d\n", i, list_buf[cursor].data);
        i++;
    }
    printf("\n");
    
    //反向遍历链表 方式一
    printf("********************************\n");
    printf("反向遍历链表 方式一 测试\n");
    printf("********************************\n");
    i = 0;
    STATIC_LIST_FOR_EACH_ENTRY_ELEMENT_REVERSE(cursor, list_buf, p_value, data)
    {
        printf("Node %d's data: %d\n", i, *p_value);
        i++;
    }
    printf("\n");
    
    //反向遍历链表 方式二
    printf("********************************\n");
    printf("反向遍历链表 方式二 测试\n");
    printf("********************************\n");
    i = 0;
    STATIC_LIST_FOR_EACH_ENTRY_ELEMENT_SAFE_REVERSE(cursor, next_cursor, list_buf, p_value, data)
    {
        printf("Node %d's data: %d\n", i, *p_value);
        i++;
    }
    printf("\n");
    
    //反向遍历链表 方式三
    printf("********************************\n");
    printf("反向遍历链表 方式三 测试\n");
    printf("********************************\n");
    i = 0;
    STATIC_LIST_FOR_EACH_REVERSE(cursor, list_buf)
    {
        printf("Node %d's data: %d\n", i, list_buf[cursor].data);
        i++;
    }
    printf("\n");
    
    //反向遍历链表 方式四
    printf("********************************\n");
    printf("反向遍历链表 方式四 测试\n");
    printf("********************************\n");
    i = 0;
    STATIC_LIST_FOR_EACH_SAFE_REVERSE(cursor, next_cursor, list_buf)
    {
        printf("Node %d's data: %d\n", i, list_buf[cursor].data);
        i++;
    }
    printf("\n");
    
    printf("********************************\n");
    printf("删除数据 测试\n");
    printf("********************************\n");
    //判断链表是否为空
    printf("list %s empty\n", static_list_is_empty(list_buf) ? "is" : "isn't");
    printf("\n");
    
    //删除数据数值
    for (i=0; i < 10; i++)
    {
        //往链表队尾删除数据
        STATIC_LIST_REMOVE_TAIL_TYPE(list_buf, itemtype, data);
        printf("Node %d has del to the list...\n", i+1);
    }
    printf("\n");
    
    //判断链表是否为空
    printf("list %s empty\n", static_list_is_empty(list_buf) ? "is" : "isn't");
    printf("\n");
    
    //遍历检查下链表
    i = 0;
    STATIC_LIST_FOR_EACH_ENTRY_ELEMENT(cursor, list_buf, p_value, data)
    {
        printf("Node %d's data: %d\n", i, *p_value);
        i++;
    }
    printf("\n");
    
    printf("********************************\n");
    printf("链表队头添加数据 测试\n");
    printf("********************************\n");
    //放入数值
    for (i=0; i < 10; i++)
    {
        value = i+10;
        //往链表队头添加数据
        STATIC_LIST_ADD_HEAD_TYPE(list_buf, data, value);
        printf("Node %d has added to the list...\n", i+1);
    }
    printf("\n");
    
    //遍历检查下链表
    i = 0;
    STATIC_LIST_FOR_EACH_ENTRY_ELEMENT(cursor, list_buf, p_value, data)
    {
        printf("Node %d's data: %d\n", i, *p_value);
        i++;
    }
    printf("\n");
    
    //删除数据数值
    for (i=0; i < 10; i++)
    {
        //往链表队头删除数据
        STATIC_LIST_REMOVE_HEAD_TYPE(list_buf, itemtype, data);
        printf("Node %d has del to the list...\n", i+1);
    }
    printf("\n");
    
    //判断链表是否为空
    printf("list %s empty\n", static_list_is_empty(list_buf) ? "is" : "isn't");
    printf("\n");
    
    //遍历检查下链表
    i = 0;
    STATIC_LIST_FOR_EACH_ENTRY_ELEMENT(cursor, list_buf, p_value, data)
    {
        printf("Node %d's data: %d\n", i, *p_value);
        i++;
    }
    printf("\n");
    
    
    //放入数值
    for (i = 0; i < 10; i++)
    {
        value = i+10;
        //往链表队尾添加数据
        STATIC_LIST_ADD_TAIL_TYPE(list_buf, data, value);
        printf("Node %d has added to the list...\n", i+1);
    }
    printf("\n");
    
    for (i = 0; i < 10; i++)
    {
        if(STATIC_LIST_REMOVE_HEAD_TYPE_SAFE(list_buf, data, value))
            printf("Node %d has %d...\n", i+1, value);
    }
    
    //判断链表是否为空
    printf("list %s empty\n", static_list_is_empty(list_buf) ? "is" : "isn't");
    printf("\n");
    
    //放入数值
    for (i = 0; i < 10; i++)
    {
        value = i+10;
        //往链表队尾添加数据
        STATIC_LIST_ADD_TAIL_TYPE(list_buf, data, value);
        printf("Node %d has added to the list...\n", i+1);
    }
    printf("\n");
    
    for (i = 0; i < 10; i++)
    {
        if(STATIC_LIST_REMOVE_TAIL_TYPE_SAFE(list_buf, data, value))
            printf("Node %d has %d...\n", i+1, value);
    }
    
    //判断链表是否为空
    printf("list %s empty\n", static_list_is_empty(list_buf) ? "is" : "isn't");
    printf("\n");
    
    printf("********************************\n");
    printf("其他接口 测试\n");
    printf("********************************\n");
    //放入数值
    for (i = 0; i < 10; i++)
    {
        value = i+10;
        //往链表队尾添加数据
        STATIC_LIST_ADD_TAIL_TYPE(list_buf, data, value);
        printf("Node %d has added to the list...\n", i+1);
    }
    printf("\n");
    
    cursor = static_list_get_and_remove_head_cursor(list_buf);
    printf("Node HEAD has %d...\n", list_buf[cursor].data);
    
    cursor = static_list_get_and_remove_tail_cursor(list_buf);
    printf("Node TAIL has %d...\n", list_buf[cursor].data);
    
    //遍历检查下链表
    i = 0;
    STATIC_LIST_FOR_EACH_ENTRY_ELEMENT(cursor, list_buf, p_value, data)
    {
        printf("Node %d's data: %d\n", i, *p_value);
        i++;
    }
    printf("\n");
    
    p_value = STATIC_LIST_PEEK_HEAD_TYPE(list_buf, itemtype, data);
    printf("Node HEAD has %d...\n", *p_value);
    
    p_value = STATIC_LIST_PEEK_TAIL_TYPE(list_buf, itemtype, data);
    printf("Node TAIL has %d...\n", *p_value);
    
    printf("\n");
    
    //清空所有元素
    STATIC_LIST_FOR_EACH_ENTRY_ELEMENT_SAFE(cursor, next_cursor, list_buf, p_value, data)
        static_list_delete_and_free(list_buf, cursor);
    
    printf("********************************\n");
    printf("遍历链表中删除元素测试\n");
    printf("********************************\n");
    
    //放入数值
    for (i = 0; i < 10; i++)
    {
        value = i+10;
        //往链表队尾添加数据
        STATIC_LIST_ADD_TAIL_TYPE(list_buf, data, value);
        printf("Node %d has added to the list...\n", i+1);
    }
    printf("\n");
    
    //遍历链表中删除元素
    i = 0;
    STATIC_LIST_FOR_EACH_ENTRY_ELEMENT_SAFE(cursor, next_cursor, list_buf, p_value, data)
    {
        printf("Node %d's data: %d\n", i, *p_value);
        if(*p_value > 15)
            static_list_delete_and_free(list_buf, cursor);
        
        i++;
    }
    printf("\n");
    
    //遍历检查下链表
    i = 0;
    STATIC_LIST_FOR_EACH_ENTRY_ELEMENT(cursor, list_buf, p_value, data)
    {
        printf("Node %d's data: %d\n", i, *p_value);
        i++;
    }
    printf("\n");
    
    return 0;
}