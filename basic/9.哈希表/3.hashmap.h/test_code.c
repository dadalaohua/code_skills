#include <stdio.h>

#include "hashmap.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/


/************************************************************************/
/*                                                                      */
/************************************************************************/
static int test_func(void *const context, void *const element) {
    *(int *)context += 1;   //这个值是total，累加计算total
    printf("%d\n", *(int *)element);
    return 1;//返回1继续迭代，返回0结束迭代
}

static int test_func_2(void *context, struct hashmap_element_s *e) {
    *(int *)context += 1;   //这个值是total，累加计算total
    char *c = (char *)e->key;
    printf("%c %d %d\n", *c, e->key_len, *(int *)(e->data));
    return 0;//0继续，1退出，-1删除该元素
}

static int rem_all(void *context, struct hashmap_element_s *e) {
    (*(int *)context) += 1;   //这个值是total，累加计算total
    return -1;//-1删除该元素
}

int main(int argc, char* argv[])
{
    //hashmap
    struct hashmap_s hashmap;
    char s[26];
    int num[26] = {0};
    for(int i = 0; i < 26; i++) {
        s[i] = i + 'a';
        num[i] = i;
    }
    //创建
    hashmap_create(1, &hashmap);
    
    //获取大小
    printf("num : %d\n", hashmap_num_entries(&hashmap));
    
    //将数据放入hash
    for(int i = 0; i < 26; i++) {
        hashmap_put(&hashmap, s + i, 1, num + i);
    }
    
    //获取大小
    printf("num : %d\n", hashmap_num_entries(&hashmap));
    
    //删除一个key
    hashmap_remove(&hashmap, "g", (unsigned)strlen("g"));
    
    //删除并返回key
    char *c = (char *)hashmap_remove_and_return_key(&hashmap, "t", (unsigned)strlen("t"));
    printf("remove %c\n", *c);
    
    //获取大小
    printf("num : %d\n", hashmap_num_entries(&hashmap));
    
    //查询hash
    for(int i = 0; i < 26; i++) {
        int *x = hashmap_get(&hashmap, s + i, 1);
        if(x)
            printf("%c : %d\n", *(s + i), *x);
        else
            printf("%c : %p\n", *(s + i), x);
    }
    
    //查询不存在的数据，获取到NULL
    int *x = hashmap_get(&hashmap, "test", 4);
    printf("%s : %p\n", "test", x);
    printf("\n\n");
    
    //迭代遍历所有value，并在test_func计算total
    int total = 0;
    hashmap_iterate(&hashmap, test_func, &total);
    printf("total : %d\n", total);
    
    //迭代遍历,打印数据
    total = 0;
    hashmap_iterate_pairs(&hashmap, test_func_2, &total);
    printf("total : %d\n", total);
    
    //删除所有元素
    total = 0;
    hashmap_iterate_pairs(&hashmap, rem_all, &total);
    printf("total : %d\n", total);
    
    //获取大小
    printf("num : %d\n", hashmap_num_entries(&hashmap));
    
    //放入字符串形式的value
    hashmap_put(&hashmap, "hello", 5, "world");
    char *valuestr = hashmap_get(&hashmap, "hello", 5);
    printf("valuestr : %s\n", valuestr);
    
    //销毁
    hashmap_destroy(&hashmap);
    
    return 0;
}