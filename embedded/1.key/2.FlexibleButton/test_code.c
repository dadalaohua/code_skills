#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "flexible_button.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
volatile int button_level[4] = {1, 1, 1, 1};

void set_button_level(int id, unsigned char level)
{
    button_level[id] = level;
}

unsigned char get_button_level(int id)
{
    return button_level[id];
}

unsigned char read_button_GPIO(int id) 
{
    return get_button_level(id);
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
void thread(void* argc)  
{
    int level[4] = {1, 1, 1, 1};
    char c;
    while(1) {
        c = getchar();
        switch (c)
        {
        case '1':
            level[0] = !level[0];
            set_button_level(0, level[0]);
            break;
        case '2':
            level[1] = !level[1];
            set_button_level(1, level[1]);
            break;
        case '3':
            level[2] = !level[2];
            set_button_level(2, level[2]);
            break;
        case '4':
            level[3] = !level[3];
            set_button_level(3, level[3]);
            break;
        default:
            break;
        }
    }
}
/************************************************************************/
/*
typedef enum
{
    FLEX_BTN_PRESS_DOWN = 0,        // 按下事件
    FLEX_BTN_PRESS_CLICK,           // 单击事件
    FLEX_BTN_PRESS_DOUBLE_CLICK,    // 双击事件
    FLEX_BTN_PRESS_REPEAT_CLICK,    // 连击事件，使用 flex_button_t 中的 click_cnt 断定连击次数
    FLEX_BTN_PRESS_SHORT_START,     // 短按开始事件
    FLEX_BTN_PRESS_SHORT_UP,        // 短按抬起事件
    FLEX_BTN_PRESS_LONG_START,      // 长按开始事件
    FLEX_BTN_PRESS_LONG_UP,         // 长按抬起事件
    FLEX_BTN_PRESS_LONG_HOLD,       // 长按保持事件
    FLEX_BTN_PRESS_LONG_HOLD_UP,    // 长按保持的抬起事件
    FLEX_BTN_PRESS_MAX,
    FLEX_BTN_PRESS_NONE,
} flex_button_event_t;
                                                                        */
/************************************************************************/
#define ENUM_TO_STR(e) (#e)

typedef enum
{
    USER_BUTTON_0 = 0,
    USER_BUTTON_1,
    USER_BUTTON_2,
    USER_BUTTON_3,
    USER_BUTTON_MAX
} user_button_t;

static char *enum_event_string[] = {
    ENUM_TO_STR(FLEX_BTN_PRESS_DOWN),
    ENUM_TO_STR(FLEX_BTN_PRESS_CLICK),
    ENUM_TO_STR(FLEX_BTN_PRESS_DOUBLE_CLICK),
    ENUM_TO_STR(FLEX_BTN_PRESS_REPEAT_CLICK),
    ENUM_TO_STR(FLEX_BTN_PRESS_SHORT_START),
    ENUM_TO_STR(FLEX_BTN_PRESS_SHORT_UP),
    ENUM_TO_STR(FLEX_BTN_PRESS_LONG_START),
    ENUM_TO_STR(FLEX_BTN_PRESS_LONG_UP),
    ENUM_TO_STR(FLEX_BTN_PRESS_LONG_HOLD),
    ENUM_TO_STR(FLEX_BTN_PRESS_LONG_HOLD_UP),
    ENUM_TO_STR(FLEX_BTN_PRESS_MAX),
    ENUM_TO_STR(FLEX_BTN_PRESS_NONE),
};

static char *enum_btn_id_string[] = {
    ENUM_TO_STR(USER_BUTTON_0),
    ENUM_TO_STR(USER_BUTTON_1),
    ENUM_TO_STR(USER_BUTTON_2),
    ENUM_TO_STR(USER_BUTTON_3),
    ENUM_TO_STR(USER_BUTTON_MAX),
};

static flex_button_t user_button[USER_BUTTON_MAX];

static uint8_t common_btn_read(void *arg)
{
    uint8_t value = 0;

    flex_button_t *btn = (flex_button_t *)arg;

    switch (btn->id)
    {
    case USER_BUTTON_0:
        value = read_button_GPIO(USER_BUTTON_0);
        break;
    case USER_BUTTON_1:
        value = read_button_GPIO(USER_BUTTON_1);
        break;
    case USER_BUTTON_2:
        value = read_button_GPIO(USER_BUTTON_2);
        break;
    case USER_BUTTON_3:
        value = read_button_GPIO(USER_BUTTON_2);
        break;
    default:
        break;
    }

    return value;
}

static void common_btn_evt_cb(void *arg)
{
    flex_button_t *btn = (flex_button_t *)arg;

    printf("id: [%d - %s]  event: [%d - %30s]  repeat: %d\n", 
        btn->id, enum_btn_id_string[btn->id],
        btn->event, enum_event_string[btn->event],
        btn->click_cnt);

    //按键事件读取接口, 使用该接口获取指定按键的事件
    if ((flex_button_event_read(&user_button[USER_BUTTON_0]) == FLEX_BTN_PRESS_CLICK) &&\
        (flex_button_event_read(&user_button[USER_BUTTON_1]) == FLEX_BTN_PRESS_CLICK))
    {
        printf("[combination]: button 0 and button 1\n");
    }
}

static void user_button_init(void)
{
    int i;
    
    memset(&user_button[0], 0x00, sizeof(user_button));

    for (i = 0; i < USER_BUTTON_MAX; i ++)
    {
        user_button[i].id = i;                                              //按键编号
        user_button[i].usr_button_read = common_btn_read;                   //设置按键读值回调函数
        user_button[i].cb = common_btn_evt_cb;                              //设置按键事件回调函数
        user_button[i].pressed_logic_level = 0;                             //设置按键按下时的逻辑电平
        user_button[i].short_press_start_tick = FLEX_MS_TO_SCAN_CNT(1500);  //短按起始 tick，使用 FLEX_MS_TO_SCAN_CNT 宏转化为扫描次数
        user_button[i].long_press_start_tick = FLEX_MS_TO_SCAN_CNT(3000);   //长按起始 tick，使用 FLEX_MS_TO_SCAN_CNT 宏转化为扫描次数
        user_button[i].long_hold_start_tick = FLEX_MS_TO_SCAN_CNT(4500);    //超长按起始 tick，使用 FLEX_MS_TO_SCAN_CNT 宏转化为扫描次数

        //user_button[i].short_press_start_tick = FLEX_MS_TO_SCAN_CNT(1500); 表示按键按下开始计时，1500 ms 后按键依旧是按下状态的话，就断定为短按开始
        
        //按键注册接口
        flex_button_register(&user_button[i]);
    }
}

int main(int argc, char* argv[])
{
    printf("process id is %d\n", getpid());

    pthread_t id; 

    pthread_create(&id, NULL, (void  *)thread, NULL);  
   
    ////////////////////////////

    user_button_init();
    
    for(;;)
    {
        //按键扫描接口
        //按键扫描的核心函数，需要放到应用程序中定时扫描，扫描间隔建议 20 毫秒。
        flex_button_scan();
        usleep(20000); // 20 ms
    }

    return 0;
}