#include <stdio.h>
#include <stdlib.h>

#include "efsm.h"
#include "efsm_event.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
EFSM_DECLEAR(startup);
EFSM_DECLEAR(offline);
EFSM_DECLEAR(online);

/* 1. define state-machine pointer */
EFSM_PTR_CREATE(main);

extern void startup_init();
extern void offline_init();
extern void online_init();

static void event_invoke(EFSM_EVENT_TYPE event)
{
    EFSM_EVENT_HANDLER handler = NULL;

    handler = EFSM_HANDLER(main, event);
    printf("handler: %p\n", handler);
    if(handler)
        handler(event, NULL);
}


/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    startup_init();
    offline_init();
    online_init();

    /* 2. init first state */
    EFSM_PTR_BIND(main, startup);
    printf("******************************************\n");
    /* 3. get a event handler from EFSM */
    event_invoke(EVENT_STOP);

    /* 4.on condition, change state */
    EFSM_TRANSFER_ENABLE(main);
    EFSM_TRANSFER(main, offline);
    EFSM_TRANSFER_DISABLE(main);

    event_invoke(EVENT_PLAY);

    EFSM_TRANSFER_ENABLE(main);
    EFSM_TRANSFER(main, online);
    EFSM_TRANSFER_DISABLE(main);

    event_invoke(EVENT_NEXT);

    printf("******************************************\n");
    return 0;
}