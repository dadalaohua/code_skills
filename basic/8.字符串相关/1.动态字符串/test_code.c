#include "utstring.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
//These examples show how to use utstring. 这些示例展示了如何使用 utstring。
void test_function_1(void)
{
    UT_string *s;

    //allocate a new utstring 申请一个新的utstring
    utstring_new(s);
    
    //printf into a utstring (appends) printf 转换为 utstring（追加）
    utstring_printf(s, "hello world!" );
    
    //get `char*` to body of s (buffer is always null-terminated) 获取 `char*` 到 s 的主体（缓冲区始终以空值结尾）
    printf("%s\n", utstring_body(s));

    //free an allocated utstring 释放一个分配的 utstring
    utstring_free(s);
}

//non-alloc 非申请
void test_function_1_1(void)
{
    UT_string *s = (UT_string*)malloc(sizeof(UT_string));

    //init a utstring (non-alloc) 初始化一个 utstring（非分配）
    utstring_init(s);
    
    //printf into a utstring (appends)
    utstring_printf(s, "hello world!" );
    
    //get `char*` to body of s (buffer is always null-terminated)
    printf("%s\n", utstring_body(s));

    //dispose of a utstring (non-alloc) 销毁 utstring（非申请）
    utstring_done(s);
}

//The next example demonstrates that `utstring_printf` 'appends' to the string. 下一个示例演示了“utstring_printf”“追加”到字符串。
//It also shows concatenation.
void test_function_2(void)
{
    UT_string *s, *t;

    utstring_new(s);
    utstring_new(t);

    utstring_printf(s, "hello " );
    utstring_printf(s, "world " );

    utstring_printf(t, "hi " );
    utstring_printf(t, "there " );

    //concatenate src utstring to end of dst utstring 将 src utstring 连接到 dst utstring 的结尾
    utstring_concat(s, t);
    
    //obtain the length of s as an unsigned integer 以无符号整数形式获取 s 的长度
    printf("length: %u\n", utstring_len(s));
    printf("%s\n", utstring_body(s));

    utstring_free(s);
    utstring_free(t);
}

//The next example shows how binary data can be inserted into the string. It also
//clears the string and prints new data into it. 下一个示例显示了如何将二进制数据插入到字符串中。 它还清除字符串并将新数据打印到其中。
void test_function_3(void)
{
    UT_string *s;
    char binary[] = "\xff\xff";

    utstring_new(s);
    
    //insert binary data of length len (appends) 插入长度为len的二进制数据（追加）
    utstring_bincpy(s, binary, sizeof(binary));
    printf("length is %u\n", utstring_len(s));

    //clear the content of s (setting its length to 0) 清除s的内容（将其长度设置为0）
    utstring_clear(s);
    utstring_printf(s,"number %d", 10);
    printf("%s\n", utstring_body(s));

    utstring_free(s);
}

//Substring search 子串检索
void test_function_4(void)
{
    UT_string *s;

    utstring_new(s);
    
    utstring_printf(s, "ABC ABCDAB ABCDABCDABDE");

    //forward search from pos for a substring 从pos向前搜索子字符串
    printf("%ld\n", utstring_find(  s, -9, "ABC", 3 ));//从-9的位置开始找"ABC"，最后在从头开始数15的位置找到
    printf("%ld\n", utstring_find(  s,  3, "ABC", 3 ));
    printf("%ld\n", utstring_find(  s, 16, "ABC", 3 ));
    
    //reverse search from pos for a substring 从pos反向搜索子字符串
    printf("%ld\n", utstring_findR( s, -9, "ABC", 3 ));
    printf("%ld\n", utstring_findR( s, 12, "ABC", 3 ));
    printf("%ld\n", utstring_findR( s,  2, "ABC", 3 ));

    utstring_free(s);
}

//Multiple search mode 多重搜索模式
void test_function_5(void)
{
    UT_string *s;

    utstring_new(s);
    
    long *KPM_TABLE, offset, result;
    
    KPM_TABLE = (long *)malloc( sizeof(long) * (strlen("ABC")) + 1);
    
    // utstring_printf(s, "ABC ABCDAB ABCDABCDABDE");
    utstring_printf(s, "ABC ABCDAB ABCDABCDABDE");
    
    //build the KMP table for a forward search 构建KMP表以进行正向搜索
    _utstring_BuildTable("ABC", 3, KPM_TABLE);
    
    //forward search using a prebuilt KMP table 使用预先构建的KMP表进行正向搜索
    offset = _utstring_find(utstring_body(s), utstring_len(s), "ABC", 3, KPM_TABLE );
    while(offset != -1)
    {
        printf("%ld\n", offset);
        result = _utstring_find(utstring_body(s) + offset + strlen("ABC"), utstring_len(s) - (offset + strlen("ABC")), "ABC", 3, KPM_TABLE );
        if(result != -1)
            offset = result + offset + strlen("ABC");
        else
            break;
    }
    
    printf("%ld\n", result);
    
    free(KPM_TABLE);
    
    utstring_free(s);
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    printf("test_function_1\n");
    test_function_1();
    printf("\n");
    
    printf("test_function_1_1\n");
    test_function_1_1();
    printf("\n");
    
    printf("test_function_2\n");
    test_function_2();
    printf("\n");
    
    printf("test_function_3\n");
    test_function_3();
    printf("\n");
    
    printf("test_function_4\n");
    test_function_4();
    printf("\n");
    
    printf("test_function_5\n");
    test_function_5();
    printf("\n");
    
    return 0;
}