#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "khash.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
//hash table for integers
KHASH_MAP_INIT_INT(32, char)

void hash_table_for_integers(void)
{
    //generic hash table with open addressing
    //使用开放定址法
    
    //hash table for integers
    //整数的哈希表
    
    int ret, is_missing;
    khiter_t k;
    //allocate a hash table 分配一个散列表
    khash_t(32) *h = kh_init(32);
    
    //insert a key to the hash table 向散列表插入一个键key，键key为5
    //返回地址k, 得到ret表示是否成功
    k = kh_put(32, h, 5, &ret);
    printf("k %d ret %d\n", k, ret);
    
    //set the value
    //往地址k放入数值10
    kh_value(h, k) = 10;
    printf("kh_value(h, k) %d\n", kh_value(h, k));
    
    //query the hash table
    //查询键key为12对应的散列表地址
    k = kh_get(32, h, 12);
    printf("k %d\n", k);
    
    //test if the key is present
    //测试键是否存在, 如果k == kh_end(h)则表示不存在
    is_missing = (k == kh_end(h));
    printf("is_missing %d\n", is_missing);//这里is_missing为1，表示不存在
    
    //查询键key为5对应的散列表地址
    k = kh_get(32, h, 5);
    printf("k %d\n", k);
    //remove a key-value pair
    //删除键-值对
    kh_del(32, h, k);
    
    //test if a bucket contains data
    //测试桶是否有数据
    for (k = kh_begin(h); k != kh_end(h); ++k)
        if (kh_exist(h, k)) kh_value(h, k) = 1;
    
    //deallocate the hash table
    //释放散列表
    kh_destroy(32, h);
}

KHASH_MAP_INIT_INT(m32, char)      // instantiate structs and methods

int hash_table_for_integers_2(void)
{
    int absent, is_missing;
    khint_t k;
    khash_t(m32) *h = kh_init(m32);  // allocate a hash table
    k = kh_put(m32, h, 5, &absent);  // insert a key to the hash table
    if (!absent) kh_del(m32, h, k);
    kh_value(h, k) = 10;             // set the value
    k = kh_get(m32, h, 10);          // query the hash table
    is_missing = (k == kh_end(h));   // test if the key is present
    printf("is_missing %d\n", is_missing);
    
    k = kh_get(m32, h, 5);
    kh_del(m32, h, k);               // remove a key-value pair
    for (k = kh_begin(h); k != kh_end(h); ++k)  // traverse
        if (kh_exist(h, k))          // test if a bucket contains data
            kh_value(h, k) = 1;
    kh_destroy(m32, h);              // deallocate the hash table
    
    return 0;
}

/************************************************************************/
//counting distinct words (without heap allocation)
KHASH_SET_INIT_STR(str)

void hash_table_for_string(void)
{
    //counting distinct words (without heap allocation)
    //计算不同的单词（无堆分配） 
    
    char strbuf[][7] = {
        "test 1",
        "test 2",
        "test 3",
    };
    
    int count = sizeof(strbuf)/sizeof(strbuf[0]);
    
    khash_t(str) *h;
    khint_t k;
    int i, absent;
    h = kh_init(str);
    for (i = 0; i < count; ++i)
    {
        k = kh_put(str, h, strbuf[i], &absent);
        
        printf("i %d k %d\n", i, k);
    }
    printf("# of distinct words: %d\n", kh_size(h));
    
    kh_destroy(str, h);
}

/************************************************************************/
//counting distinct words (with heap allocation)
KHASH_SET_INIT_STR(str2)

void hash_table_for_string_2(void)
{
    char s[4096]; // max string length: 4095 characters
    khash_t(str2) *h;
    khint_t k;
    h = kh_init(str2);
    while (scanf("%s", s) > 0) {
        int absent;
        k = kh_put(str2, h, s, &absent);
        printf("k %d absent %d\n", k, absent);
        if (absent) kh_key(h, k) = strdup(s);
        // else, the key is not touched; we do nothing
    }
    printf("# of distinct words: %d\n", kh_size(h));
    // IMPORTANT: free memory allocated by strdup() above
    for (k = 0; k < kh_end(h); ++k)
        if (kh_exist(h, k))
            free((char*)kh_key(h, k));
    kh_destroy(str2, h);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    hash_table_for_integers();
    hash_table_for_string();
    hash_table_for_string_2();
    
    return 0;
}
