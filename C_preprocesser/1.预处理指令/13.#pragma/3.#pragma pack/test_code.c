#include <stdio.h>              //包含一个源代码文件

/************************************************************************/
/*                                                                      */
/************************************************************************/
struct test1
{
    char a;
    int  b;
    short c;
};

#pragma pack(2)
struct test2
{
    char a;
    int  b;
    short c;
};
#pragma pack()

#pragma pack(4)
struct test3
{
    char a;
    int  b;
    short c;
};
#pragma pack()

#pragma pack(8)
struct test4
{
    char a;
    int  b;
    short c;
};
#pragma pack()


#pragma pack(2)
struct test20
{
    char a;
    char b;
    int  c;
};
#pragma pack()

#pragma pack(4)
struct test21
{
    char a;
    char b;
    int  c;
};
#pragma pack()

#pragma pack(push)
#pragma pack(1)
struct test30
{
    char a;
    char b;
    int  c;
};
#pragma pack(pop)

struct test31
{
    char a;
    char b;
    int  c;
};

#pragma pack(push, 1)
struct test40
{
    char a;
    char b;
    int  c;
};
#pragma pack(pop)

struct test41
{
    char a;
    char b;
    int  c;
};

#pragma pack(push, identifier_1, 1)
struct test50
{
    char a;
    int b;
};
#pragma pack(push, identifier_2, 2)
struct test51
{
    char a;
    int b;
};
#pragma pack(pop, identifier_2)
struct test52
{
    char a;
    int b;
};
#pragma pack(pop, identifier_1)
struct test53
{
    char a;
    int b;
};
/************************************************************************/
/*                                                                      */
/************************************************************************/
int main(int argc, char* argv[])
{
    printf("sizeof(test1) = %d\n",sizeof(struct test1)); //sizeof(test1) = 12
    printf("sizeof(test2) = %d\n",sizeof(struct test2)); //sizeof(test2) = 8
    printf("sizeof(test3) = %d\n",sizeof(struct test3)); //sizeof(test3) = 12
    printf("sizeof(test4) = %d\n",sizeof(struct test4)); //sizeof(test4) = 12
    
    printf("sizeof(test20) = %d\n",sizeof(struct test20)); //sizeof(test20) = 6
    printf("sizeof(test21) = %d\n",sizeof(struct test21)); //sizeof(test21) = 8

    printf("sizeof(test30) = %d\n",sizeof(struct test30)); //sizeof(test30) = 6
    printf("sizeof(test31) = %d\n",sizeof(struct test31)); //sizeof(test31) = 8
    
    printf("sizeof(test40) = %d\n",sizeof(struct test40)); //sizeof(test40) = 6
    printf("sizeof(test41) = %d\n",sizeof(struct test41)); //sizeof(test41) = 8
    
    printf("sizeof(test50) = %d\n",sizeof(struct test50)); //sizeof(test50) = 5
    printf("sizeof(test51) = %d\n",sizeof(struct test51)); //sizeof(test51) = 6
    printf("sizeof(test52) = %d\n",sizeof(struct test52)); //sizeof(test52) = 5
    printf("sizeof(test53) = %d\n",sizeof(struct test53)); //sizeof(test53) = 8
    
    return 0;
}