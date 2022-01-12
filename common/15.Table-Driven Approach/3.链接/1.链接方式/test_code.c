#include <stdio.h>
#include <string.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/

//section中只能2的次幂对齐，如8,16,32,64字节，否则会出错
//这个结构体在64位机中sizeof(teststruct) = 40，需要使用aligned (32)将其变成sizeof(teststruct) = 64
typedef struct _teststruct
{
    char * TestCmd;
    int TestID;
    void (*TestPrepare)(int id);
    int (*TestMessage)(void);
    void (*TestEnd)(void);
} __attribute__ ((aligned (32))) teststruct;

#define TEST_USED __attribute__((used))
#define TEST_SECTION(x) __attribute__((section(".rodata_test_cmd" x)))
#define TEST_CMD_EXPORT_START(cmd, id, prefunc, mesfunc, endfunc) \
    TEST_USED const teststruct _test_cmd_start_ TEST_SECTION("_start") = {#cmd, 0, NULL, NULL, NULL}
#define TEST_CMD_EXPORT(cmd, id, prefunc, mesfunc, endfunc) \
    TEST_USED const teststruct _test_cmd_##cmd TEST_SECTION("") = {#cmd, id, prefunc, mesfunc, endfunc}
#define TEST_CMD_EXPORT_END(cmd, id, prefunc, mesfunc, endfunc) \
    TEST_USED const teststruct _test_cmd_end_ TEST_SECTION("_end") = {#cmd, 0, NULL, NULL, NULL}

TEST_CMD_EXPORT_START(start, 0, NULL, NULL, NULL);
TEST_CMD_EXPORT_END(end, 0, NULL, NULL, NULL);

/************************************************************************/
/*                                                                      */
/************************************************************************/
void TestPrepare_0(int id)
{
    printf("TestPrepare_0 ID:%d\n", id);
}

int TestMessage_0(void)
{
    printf("TestMessage_0\n");
    
    return 0;
}

void TestEnd_0(void)
{
    printf("TestEnd_0\n");
}

TEST_CMD_EXPORT(test0, 0, TestPrepare_0, TestMessage_0, TestEnd_0);
/************************************************************************/
/*                                                                      */
/************************************************************************/
void TestPrepare_1(int id)
{
    printf("TestPrepare_1 ID:%d\n", id);
}

int TestMessage_1(void)
{
    printf("TestMessage_1\n");
    
    return 0;
}

void TestEnd_1(void)
{
    printf("TestEnd_1\n");
}

TEST_CMD_EXPORT(test1, 1, TestPrepare_1, TestMessage_1, TestEnd_1);
/************************************************************************/
/*                                                                      */
/************************************************************************/
void TestPrepare_2(int id)
{
    printf("TestPrepare_2 ID:%d\n", id);
}

int TestMessage_2(void)
{
    printf("TestMessage_2\n");
    
    return 0;
}

void TestEnd_2(void)
{
    printf("TestEnd_2\n");
}

TEST_CMD_EXPORT(test2, 2, TestPrepare_2, TestMessage_2, TestEnd_2);
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    char str[50] = {0};
    
    printf("sizeof=0x%lx\r\n",sizeof(teststruct));
    
    //输入test0,test1或者test2进行匹配
    while(fgets(str, 10, stdin) != NULL)
    {
        printf("str : %s\n", str);
        for(const teststruct *p = &_test_cmd_start_ + 1; p < &_test_cmd_end_; p++)
        {
            if(strncmp(p->TestCmd, str, 5) == 0)
            {
                printf("TestCmd : %s\n", p->TestCmd);
                printf("TestID : %d\n", p->TestID);
                p->TestPrepare(p->TestID);
                p->TestMessage();
                p->TestEnd();
            }
        }
    }
    
    return 0;
}