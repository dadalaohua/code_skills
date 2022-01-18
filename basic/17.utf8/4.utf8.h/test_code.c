#include <stdio.h>

#include "utf8.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/
const char hello_data[] = {
    '\xe4', '\xbd', '\xa0', '\xe5', '\xa5', '\xbd', '\0'};  //你好
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    char test_data[16];
    printf("%s\n", hello_data);
    printf("utf8valid %p\n", utf8valid(hello_data));//为NULL，有效
    printf("utf8len %ld\n",utf8len(hello_data));//长度2，两个utf8字符
    printf("utf8nlen %ld\n",utf8nlen(hello_data, 3));//长度1，前3个Byte共1个utf8字符
    
    utf8cpy(test_data, hello_data);//将hello_data拷贝到test_data
    printf("%s\n", test_data);
    
    printf("utf8size %ld\n", utf8size(hello_data));//有7个Byte，含'\0'
    printf("utf8size_lazy %ld\n", utf8size_lazy(hello_data));//有6个Byte，不含'\0'
    
    int ret = utf8casecmp(test_data, hello_data);//比大小
    printf("utf8casecmp test_data %s hello_data\n", ret > 0 ? ">" : (ret == 0 ? "=" : "<"));
    
    utf8cat(test_data, hello_data);//将hello_data附加到test_data
    printf("%s\n", test_data);
    
    ret = utf8casecmp(test_data, hello_data);//比大小
    printf("utf8casecmp test_data %s hello_data\n", ret > 0 ? ">" : (ret == 0 ? "=" : "<"));
    
    return 0;
}