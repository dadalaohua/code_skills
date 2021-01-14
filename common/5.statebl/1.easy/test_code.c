#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef enum {
  state_1   =   1,
  state_2,
  state_3,
  state_4
}State;

typedef enum{
  event_1   =   1,
  event_2,
  event_3,
  event_4,
  event_5
}EventID;

typedef struct {
    int event;              //事件
    int CurState;           //当前状态
    void (*eventActFun)();  //函数指针
    int NextState;          //下一个状态
}StateTable;

/************************************************************************/
/*                                                                      */
/************************************************************************/
void task_function_1(void);
void task_function_2(void);
void task_function_3(void);
void task_function_4(void);

StateTable fTable[] =
{
    //{到来的事件，当前的状态，将要要执行的函数，下一个状态}
    { event_1,  state_1,    task_function_1,  state_2 },
    { event_2,  state_2,    task_function_2,  state_3 },
    { event_3,  state_3,    task_function_3,  state_4 },
    { event_4,  state_4,    task_function_4,  state_1 },
    //add your code here
};

/*状态机类型*/
typedef struct {
    int curState;//当前状态
    StateTable * stateTable;//状态表
    int size;//表的项数
}fsmType;

/*状态机注册,给它一个状态表*/
void fsmRegist(fsmType* pFsm, StateTable* pTable)
{
    pFsm->stateTable = pTable;
}

/*状态迁移*/
void fsmStateTransfer(fsmType* pFsm, int state)
{
    pFsm->curState = state;
}

/*事件处理*/
void fsmEventHandle(fsmType* pFsm, int event)
{
    StateTable* pActTable = pFsm->stateTable;
    void (*eventActFun)() = NULL;  //函数指针初始化为空
    int NextState;
    int CurState = pFsm->curState;
    int maxNum = pFsm->size;
    int flag = 0;                   //标识是否满足条件
    int i;

    /*获取当前动作函数*/
    for (i = 0; i < maxNum; i++)
    {
        //当且仅当当前状态下来个指定的事件，我才执行它
        if (event == pActTable[i].event && CurState == pActTable[i].CurState)
        {
            flag = 1;
            eventActFun = pActTable[i].eventActFun;
            NextState = pActTable[i].NextState;
            break;
        }
    }


    if (flag) //如果满足条件了
    {
        /*动作执行*/
        if (eventActFun)
        {
            eventActFun();
        }

        //跳转到下一个状态
        fsmStateTransfer(pFsm, NextState);
    }
    else
    {
        printf("there is no match\n");
    }
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

void task_function_1(void)
{
    printf("this is task function 1\n");
}
void task_function_2(void)
{
    printf("this is task function 2\n");
}
void task_function_3(void)
{
    printf("this is task function 3\n");
}

void task_function_4(void)
{
    printf("this is task function 4\n");
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    fsmType pType;
    fsmRegist(&pType,fTable);
    pType.curState = state_1;
    pType.size = sizeof(fTable)/sizeof(StateTable);

    printf("init state:%d\n\n",pType.curState);

    fsmEventHandle(&pType, event_1);
    printf("state:%d\n\n", pType.curState);

    fsmEventHandle(&pType, event_2);
    printf("state:%d\n\n", pType.curState);

    fsmEventHandle(&pType, event_3);
    printf("state:%d\n\n", pType.curState);

    fsmEventHandle(&pType, event_4);
    printf("state:%d\n\n", pType.curState);

    fsmEventHandle(&pType, event_2);
    printf("state:%d\n\n", pType.curState);
    
    return 0;
}