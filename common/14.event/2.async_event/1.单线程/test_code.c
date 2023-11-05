#include <stdio.h>

#include "async_event.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/
enum SIG_TYPE //信号类型
{
    CLICK=1,  //单击
    MOVE,     //拖动
    PRESS,    //按下
    RELEASE,  //释放
};

asyncevent_t* handle;

void event_click_func(void *args)
{
    printf("Click Event Trigger, Times=%d...\n", *(int*)args);

    //可以在事件处理函数中触发其他的信号！
    //不能在自己事件函数中触发自己，这样会一直循环触发自己，造成死循环!
    // async_event_emit(handle, 1, CLICK, args); //错误
    async_event_emit(handle, 1, MOVE, args);
    async_event_emit(handle, 1, PRESS, args);
    async_event_emit(handle, 1, RELEASE, args);
}

void event_move_func(void* args)
{
    printf("Move Event Trigger, Times=%d...\n", *(int*)args);
}

void event_press_func(void *args)
{
    printf("Press Event Trigger, Times=%d...\n", *(int*)args);
}

void event_release_func(void *args)
{
    printf("Release Event Trigger, Times=%d...\n", *(int*)args);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int cnt = 0;
    //1.创建事件句柄
    handle = create_async_event();

    //2.绑定信号
    async_event_bind(handle, CLICK, event_click_func);
    async_event_bind(handle, MOVE, event_move_func);
    async_event_bind(handle, PRESS, event_press_func);
    async_event_bind(handle, RELEASE, event_release_func);

    //3.循环调度执行
    while(1)
    {
        async_event_process(handle);
        async_event_emit(handle, 0, CLICK, &cnt);
    }

    return 0;
}