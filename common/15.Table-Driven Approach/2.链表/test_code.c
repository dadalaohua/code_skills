#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

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
typedef struct _teststruct teststruct; 
struct  _teststruct
{
    int TestID;
    char * TestName;
    void (*TestPrepare)(int id);
    int (*TestMessage)(void);
    void (*TestEnd)(void);
    struct list_head list;
};

enum TestID{
    TestID_0,
    TestID_1,
    TestID_2,
};

LIST_HEAD(table_list);    //链表头
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    char str[50];
    teststruct *pteststruct;
    
    //构建表
    pteststruct = (teststruct *)malloc(sizeof(teststruct));
    pteststruct->TestID         = TestID_0;
    pteststruct->TestName       = "ID0";
    pteststruct->TestPrepare    = TestPrepare_0;
    pteststruct->TestMessage    = TestMessage_0;
    pteststruct->TestEnd        = TestEnd_0;
    
    list_add_tail(&pteststruct->list, &table_list);
    
    pteststruct = (teststruct *)malloc(sizeof(teststruct));
    pteststruct->TestID         = TestID_1;
    pteststruct->TestName       = "ID1";
    pteststruct->TestPrepare    = TestPrepare_1;
    pteststruct->TestMessage    = TestMessage_1;
    pteststruct->TestEnd        = TestEnd_1;
    
    list_add_tail(&pteststruct->list, &table_list);
    
    pteststruct = (teststruct *)malloc(sizeof(teststruct));
    pteststruct->TestID         = TestID_2;
    pteststruct->TestName       = "ID2";
    pteststruct->TestPrepare    = TestPrepare_2;
    pteststruct->TestMessage    = TestMessage_2;
    pteststruct->TestEnd        = TestEnd_2;
    
    list_add_tail(&pteststruct->list, &table_list);
    
    while(fgets(str, 4, stdin) != NULL)
    {
        list_for_each_entry(pteststruct, &table_list, list)
        {
            if(strncmp(pteststruct->TestName, str, 5) == 0)
            {
                printf("TestName : %s\n", pteststruct->TestName);
                printf("TestID : %d\n", pteststruct->TestID);
                pteststruct->TestPrepare(pteststruct->TestID);
                pteststruct->TestMessage();
                pteststruct->TestEnd();
            }
        }
    }
    
    return 0;
}