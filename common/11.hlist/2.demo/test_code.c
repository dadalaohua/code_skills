#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "list.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef unsigned char       u8;
typedef unsigned short      u16;
typedef unsigned int        u32;
typedef unsigned long long  u64;
typedef signed char         s8;
typedef short               s16;
typedef int                 s32;
typedef long long           s64;

typedef u8  uint8_t;
typedef u16 uint16_t;
typedef u32 uint32_t;
typedef u64 uint64_t;
typedef s8  int8_t;
typedef s16 int16_t;
typedef s32 int32_t;
typedef s64 int64_t;

/************************************************************************/
/*                                                                      */
/************************************************************************/

#define        CMD_HASH_HEAD_SIZE        27

typedef struct _cmd_hash_head
{
    struct  hlist_head  head;           // 哈希桶的首地址
    int8_t              ch;             // 哈希桶的关键字(a~z,?，总共27个)
    int8_t              offset;         // 这个哈希桶在整个哈希表中的偏移
    int16_t             count;          // 当前哈希桶中节点的个数
}cmd_hash_head_t;

typedef struct _cmd_hash_node
{
    struct  hlist_node  node;
    int8_t              name[20];
}cmd_hash_node_t;

/************************************************************************/
/*                                                                      */
/************************************************************************/

static cmd_hash_head_t cmd_hash[CMD_HASH_HEAD_SIZE];

static void cmd_hash_init(void)
{
    int32_t index = 0;

    memset(cmd_hash, 0, sizeof(cmd_hash));

    for(index = 0; index < (CMD_HASH_HEAD_SIZE - 1); index++)
    {
        INIT_HLIST_HEAD(&cmd_hash[index].head);
        cmd_hash[index].count    = 0;
        cmd_hash[index].offset    = index;
        cmd_hash[index].ch        = 'a' + index;
    }    

    index = CMD_HASH_HEAD_SIZE - 1;
    INIT_HLIST_HEAD(&cmd_hash[index].head);
    cmd_hash[index].count    = 0;
    cmd_hash[index].offset    = index;
    cmd_hash[index].ch        = '?';
}

static void cmd_hash_show(void)
{
    int32_t index = 0;

    for (index = 0; index < (CMD_HASH_HEAD_SIZE - 1); index++)
        printf("hash%d,head : %p,count : %d,offset : %d,ch : %c\n",index,
                &cmd_hash[index].head, cmd_hash[index].count, cmd_hash[index].offset,cmd_hash[index].ch);

    index = CMD_HASH_HEAD_SIZE - 1;
    printf("hash%d,head : %p,count : %d,offset : %d,ch : %c\n",index,
            &cmd_hash[index].head,cmd_hash[index].count,cmd_hash[index].offset,cmd_hash[index].ch);
}

static void to_lower(int8_t *str)
{
    int32_t len     = 0;
    int32_t index   = 0;

    if (str == NULL)
        return;
    
    len = strlen((char*)str);

    for (index = 0; index < len; index++)
    {
        str[index] = tolower(str[index]);
    }
}

static int8_t node_type(int8_t *name)
{
    int8_t ch     = 0x00;
    int8_t offset = 0;
    
    if (name == NULL)
        return -1;

    ch = name[0];
    switch(ch)
    {
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
        case 'g':
        case 'h':
        case 'i':
        case 'j':
        case 'k':
        case 'l':
        case 'm':
        case 'n':
        case 'o':
        case 'p':
        case 'q':
        case 'r':
        case 's':
        case 't':
        case 'u':
        case 'v':
        case 'w':
        case 'x':
        case 'y':
        case 'z':
            offset = ch - 'a' + 0;
            break;

        default :
            offset = 26;
            break;
    }

    return offset;    
}

static void hash_node_init(int8_t *name)
{
    int8_t offset = 0;

    cmd_hash_node_t *node_ptr = (cmd_hash_node_t*)calloc(1,sizeof(cmd_hash_node_t)); 
    
    offset = node_type(name);

    if(offset < 0)
        return;

    strncpy(node_ptr->name, name, strlen((char*)name));
    INIT_HLIST_NODE(&node_ptr->node);
    hlist_add_head(&node_ptr->node,&cmd_hash[offset].head);
    cmd_hash[offset].count++;
}

static void cmd_hash_node_init(void)
{
    hash_node_init((int8_t*)"hello");
    hash_node_init((int8_t*)"help");
    hash_node_init((int8_t*)"scan");
    hash_node_init((int8_t*)"???");
}

static void cmd_hash_node_show(void)
{
    int32_t index = 0;
    int16_t count = 0;
    
    cmd_hash_node_t *entry = NULL;
    struct hlist_node *ptr = NULL;

    printf("display\n");

    for (index = 0; index < CMD_HASH_HEAD_SIZE; index++)
    {
        count = cmd_hash[index].count;
        if (count > 0)
        {
            printf("hash%d,head : %p,count : %d,offset : %d,ch : %c\n",index,
                &cmd_hash[index].head,cmd_hash[index].count,cmd_hash[index].offset,cmd_hash[index].ch);

            hlist_for_each_entry(entry,ptr, &cmd_hash[index].head, node)
            {
                printf("    name : %s\n",entry->name);
            }    
        }        
    }
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{  
    cmd_hash_init();
    cmd_hash_show();
    cmd_hash_node_init();
    cmd_hash_show();
    cmd_hash_node_show(); 

    return 0;
}