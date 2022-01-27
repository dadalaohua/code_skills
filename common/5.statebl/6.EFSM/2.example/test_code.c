#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "efsmt.h"
#include "efsm_event.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
EFSM_DECLEAR(startup);
EFSM_DECLEAR(offline);
EFSM_DECLEAR(online);

/* 1.define state-machine */
EFSMT_CREATE(main);

extern void startup_init();
extern void offline_init();
extern void online_init();

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int i;

    startup_init();
    offline_init();
    online_init();

    /* 2.bind init state */
    EFSMT_BIND(main, startup);
    
    printf("******************************************\n");
    /* 3.invoke a event */
    EFSMT_INVOKE(main, EVENT_STOP, NULL);
    
    /* 4.on condition, change state */
    EFSM_TRANSFER_ENABLE(main);
    EFSM_TRANSFER(main, offline);
    EFSM_TRANSFER_DISABLE(main);

    for(i = 0; i < 5;i++)
        EFSMT_INVOKE(main, EVENT_STOP, NULL);
    
    EFSM_TRANSFER_ENABLE(main);
    EFSM_TRANSFER(main, online);
    EFSM_TRANSFER_DISABLE(main);

    for(i = 0; i < 5;i++)
        EFSMT_INVOKE(main, EVENT_NEXT, NULL);
    for(i = 0; i < 5;i++)
        EFSMT_INVOKE(main, EVENT_PLAY, NULL);

    usleep(5000); // wait a while for calling handler
    printf("******************************************\n");
    EFSMT_DESTROY(main);
    
    return 0;
}