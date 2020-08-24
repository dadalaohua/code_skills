#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory_pool.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
memory_pool_colume * b_p = NULL;
int buffer_pool_no = 0;

int buffer_pool_init(unsigned int colume_no, unsigned int block_len[] , unsigned int block_count[])
{
    b_p = (memory_pool_colume *)malloc(sizeof(memory_pool_colume) * colume_no);
    if (b_p == NULL)
        return MP_MALLOC_FIAL;
    memset(b_p , 0 , sizeof(memory_pool_colume) * colume_no);
    buffer_pool_no = colume_no;

    memory_pool_node * curr_node = NULL;
    memory_pool_node * new_node = NULL;
    for (int i = 0; i < colume_no; i++)
    {
        b_p[i].block_len = block_len[i];
        b_p[i].total_count = block_count[i];
        for (int j = 0; j < block_count[i]; j++)
        {
            new_node =(memory_pool_node *)malloc(sizeof(memory_pool_node));
            new_node->column = i;
            new_node->data =(unsigned char *) malloc(block_len[i]);
            memset(new_node->data , 0 ,block_len[i]);
            if (new_node == NULL || new_node->data == NULL)
                return MP_MALLOC_FIAL;
            new_node->next = NULL;
            if (j == 0)
            {
                b_p[i].free_header = new_node;
                curr_node = b_p[i].free_header;
            }
            else
            {
                curr_node->next = new_node;
                curr_node = curr_node->next;
            }
        }
    }
    return MP_OK;
}

memory_pool_node * buffer_malloc(unsigned int size)

{
    memory_pool_node * node = NULL;
    if (size > b_p[buffer_pool_no - 1].block_len)
    {
        printf("malloc size[%d] so big ,need new from stack!!\n" , size);
a:      node = (memory_pool_node *)malloc(sizeof(memory_pool_node));
        node->column = 9999;
        node->data = (unsigned char *)malloc(size);
        memset(node->data, 0, size);
        if (node == NULL || node->data == NULL)
            return NULL;
        node->next = NULL;
        return node;
    }
    for (int i = 0 ; i < buffer_pool_no ; i++)
    {
        if (size > b_p[i].block_len)
            continue;
        if (b_p[i].total_count - b_p[i].used_count == 0)
        {
            printf("warning!!!!  size[%d]pool use up!!!! \n" , b_p[i].block_len);
            continue;
        }
        node = b_p[i].free_header;
        b_p[i].free_header = b_p[i].free_header->next;
        b_p[i].used_count++;
        node->next = b_p[i].used_header;
        b_p[i].used_header = node;
        return node;
    }
    printf("warning!!!!  all of pool used up!!!! \n");
    goto a;
}

int buffer_free(memory_pool_node * buffer)
{
    memory_pool_node * node_cur = b_p[buffer->column].used_header;
    memory_pool_node * node_pre = NULL;
    if (buffer->column == 9999)
    {
        free(buffer->data);
        free(buffer);
        buffer = NULL;
        return MP_OK;
    }
    while(node_cur != NULL)
    {
        if (node_cur != buffer)
        {
            node_pre = node_cur;
            node_cur = node_cur->next;
            continue;
        }
        if (node_pre == NULL)
        {
            b_p[buffer->column].used_header = b_p[buffer->column].used_header->next;
        }
        else
        {
            node_pre->next = node_cur->next;
        }
        b_p[buffer->column].used_count--;
        node_cur->next = b_p[buffer->column].free_header;
        b_p[buffer->column].free_header = node_cur;
        break;
    }
    return MP_OK;
}

int buffer_pool_destory(void)
{
    memory_pool_node * node_cur = NULL;
    memory_pool_node * node_del = NULL;
    if (b_p == NULL)
        return MP_NOT_INIT;
    for (int i = 0; i < buffer_pool_no; i++)
    {
        node_cur = b_p[i].used_header;
        while (node_cur != NULL)
        {
            node_del = node_cur;
            node_cur = node_cur->next;
            free(node_del->data);
            free(node_del);
        }
        node_cur = b_p[i].free_header;
        while (node_cur != NULL)
        {
            node_del = node_cur;
            node_cur = node_cur->next;
            free(node_del->data);
            free(node_del);
        }
    }
    free(b_p);
    b_p = NULL;
    buffer_pool_no = 0;
    return MP_OK;
}

int buffer_runtime_print(void)
{
    if (b_p == NULL)
    {
        printf("buffer pool not init yet!!!\n");
        return MP_NOT_INIT;
    }
    printf("\n*********************** memory pool runtime report start************************\n");
    for (int i = 0; i < buffer_pool_no; i++)
    {
        printf("pool no[%d] blocksize[%d] blockTotalCount[%d] usedBlock[%d] used percentage[%d%%]\n" \
            , i , b_p[i].block_len , b_p[i].total_count , b_p[i].used_count , b_p[i].used_count*100/ b_p[i].total_count);
    }
    printf("*********************** memory pool runtime report end**************************\n");
    return MP_OK;
}
