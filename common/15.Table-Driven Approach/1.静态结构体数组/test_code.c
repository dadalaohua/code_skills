#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/

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
/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef struct  _teststruct teststruct; 
struct  _teststruct
{
    int TestID;
    char * TestName;
    void (*TestPrepare)(int id);
    int (*TestMessage)(void);
    void (*TestEnd)(void);
};

enum TestID{
    TestID_0,
    TestID_1,
    TestID_2,
};

teststruct table[] = {
    {TestID_0, "ID0", TestPrepare_0, TestMessage_0, TestEnd_0},
    {TestID_1, "ID1", TestPrepare_1, TestMessage_1, TestEnd_1},
    {TestID_2, "ID2", TestPrepare_2, TestMessage_2, TestEnd_2},
};
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    char str[50];
    int i;

    while(fgets(str, 4, stdin) != NULL)
    {
        for(i = 0; i < (sizeof(table) / sizeof(teststruct)); i++)
        {
            if(strncmp(table[i].TestName, str, 5) == 0)
            {
                printf("TestName : %s\n", table[i].TestName);
                printf("TestID : %d\n", table[i].TestID);
                table[i].TestPrepare(table[i].TestID);
                table[i].TestMessage();
                table[i].TestEnd();
            }
        }
    }
    
    return 0;
}