#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
struct buffer{
    int len;
    char data[0];
};

void test(char *buf, int len)
{
    struct buffer *temp_buffer;

    temp_buffer = (struct buffer *)malloc(sizeof(struct buffer) + len);
    
    temp_buffer->len = 20;
    memcpy(temp_buffer->data, buf, len);
    
    printf("%s\n", temp_buffer->data);
    
    free(temp_buffer);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
struct buffer_2{
    int len;
    char data[];
};

/************************************************************************/
/*                                                                      */
/************************************************************************/
struct buffer_3{
    int head1;
    int head2;
    int head3;
    char body[];
};

//零长度数组 body 不占用结构体的大小，且其值指向结构体的末尾
void test2(void)
{
    struct buffer_3 temp_buffer;
    printf("%d \n", sizeof(temp_buffer));
    printf("%p \n", &temp_buffer);
    printf("%p \n", &(temp_buffer.body) );
    printf("0x%x \n", ((int)&temp_buffer + sizeof(temp_buffer)) );
    printf("%d \n", ((int)&temp_buffer + sizeof(temp_buffer)) == ((int)&temp_buffer.body) );
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    printf("sizeof %d\n", sizeof(struct buffer));   //零长度数组不占用空间
    
    test("hello world!!!\n", sizeof("hello world!!!\n"));
    
    printf("sizeof %d\n", sizeof(struct buffer_2));
    
    printf("\n");
    
    test2();
    
    return 0;
}