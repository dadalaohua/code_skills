#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef enum {
    state_1 =   1,
    state_2,
    state_3,
    state_4
}State;

typedef enum{
    event_1  =  1,
    event_2,
    event_3,
    event_4,
    event_5
}EventID;

typedef void (*Action)(EventID);

typedef struct {
    State curState;     //当前状态
    EventID eventId;    //事件ID
    State nextState;    //下个状态
    Action action;      //具体表现
}StateTransform;

typedef struct{
  State state;
  int transNum;
  StateTransform* transform;
}StateMachine;

/************************************************************************/
/*                                                                      */
/************************************************************************/
StateTransform* findTranss(StateMachine* pSM,  const EventID evt)
{
    int i;
    
    for (i = 0; i < pSM->transNum; i++) {
        if ((pSM->transform[i].curState == pSM->state) && (pSM->transform[i].eventId == evt)) {
            return &pSM->transform[i];
        }
    }
    
    return NULL;
}

void runStateMachine(StateMachine* pSM, EventID evt)
{
    StateTransform* pTrans;
    pTrans = findTranss(pSM, evt);
    if (pTrans == NULL)
    {
        printf("CurState= %d Do not process enent: %d\r\n", pSM->state,evt);
        return;
    }
    pSM->state = pTrans->nextState;
    Action act = pTrans->action;
    if (act == NULL) {
        printf("change state to %d. No action\r\n",pSM->state);
        return;
    }
    act(evt);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

void task_function_1(EventID id)
{
    printf("this is task function 1 id %d\n", id);
}

void task_function_2(EventID id)
{
    printf("this is task function 2 id %d\n", id);
}

void task_function_3(EventID id)
{
    printf("this is task function 3 id %d\n", id);
}

void task_function_4(EventID id)
{
    printf("this is task function 4 id %d\n", id);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    StateMachine stateMachine;
    stateMachine.state = state_1;
    stateMachine.transNum = 7;
    StateTransform stateTran[] =
    {
        {state_1, event_3, state_2, task_function_1},
        {state_1, event_4, state_2, NULL},
        {state_2, event_1, state_3, task_function_2},
        {state_2, event_4, state_2, task_function_2},
        {state_3, event_2, state_1, task_function_3},
        {state_3, event_3, state_2, task_function_3},
        {state_3, event_5, state_3, task_function_4}
    };
    stateMachine.transform = stateTran;
    
    EventID inputEvent[15] = 
    {
        event_1, event_2, event_3, event_4, event_5,
        event_1, event_2, event_3, event_4, event_5,
        event_1, event_2, event_3, event_4, event_5
    };
    
    int i;
    
    for (i = 0; i < 15; i++)
    {
        runStateMachine(&stateMachine, inputEvent[i]);
    }
    
    return 0;
}
