#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "mfbd.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/
volatile int button_level[4] = {0, 0, 0, 0};

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
    int level;
    char c;
    while(1) {
        c = getchar();
        switch (c)
        {
        case '1':
            level = !button_level[0];
            set_button_level(0, level);
            break;
        case '2':
            level = !button_level[1];
            set_button_level(1, level);
            break;
        case '3':
            level = !button_level[2];
            set_button_level(2, level);
            break;
        case '4':
            level = !button_level[3];
            set_button_level(3, level);
            break;
        default:
            break;
        }
    }
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void bsp_btn_value_report(mfbd_btn_code_t btn_value);
unsigned char bsp_btn_check(mfbd_btn_index_t btn_index);

#if MFBD_PARAMS_SAME_IN_GROUP

/* tbtn test */
#if MFBD_USE_TINY_BUTTON
/* MFBD_TBTN_DEFINE(NAME, BTN_INDEX, FILTER_TIME, BTN_DOWN_CODE, BTN_UP_CODE) */
MFBD_TBTN_DEFINE(test_tbtn, 1, 0x1201, 0x1200);
#endif /* MFBD_USE_TINY_BUTTON */

/* nbtn test */
#if MFBD_USE_NORMAL_BUTTON
/* MFBD_NBTN_DEFINE(NAME, BTN_INDEX, BTN_DOWN_CODE, BTN_UP_CODE, BTN_LONG_CODE) */
MFBD_NBTN_DEFINE(test_nbtn1, 3,  0x1401, 0x1400, 0x1402);

MFBD_NBTN_DEFINE(test_nbtn, 2, 0x1301, 0x1300, 0x1301);
#endif /* MFBD_USE_NORMAL_BUTTON */

/* mbtn test */
#if MFBD_USE_MULTIFUCNTION_BUTTON
/* MFBD_MBTN_DEFINE(NAME, BTN_INDEX, MAX_MULTICLICK_STATE, BTN_DOWN_CODE, BTN_UP_CODE, BTN_LONG_CODE, ...) */
MFBD_MBTN_DEFINE(test_mbtn, 4, 3, 0x1501, 0x1500, 0x1501, 0x1511, 0x1521, 0x1531);
#endif /* MFBD_USE_MULTIFUCNTION_BUTTON */

#else

/* tbtn test */
#if MFBD_USE_TINY_BUTTON
/* MFBD_TBTN_DEFINE(NAME, BTN_INDEX, FILTER_TIME, BTN_DOWN_CODE, BTN_UP_CODE) */
MFBD_TBTN_DEFINE(test_tbtn, 1, 3, 0x1201, 0x1200);
#endif /* MFBD_USE_TINY_BUTTON */

/* nbtn test */
#if MFBD_USE_NORMAL_BUTTON
/* MFBD_NBTN_DEFINE(NAME, BTN_INDEX, FILTER_TIME, REPEAT_TIME, LONG_TIME, BTN_DOWN_CODE, BTN_UP_CODE, BTN_LONG_CODE) */
MFBD_NBTN_DEFINE(test_nbtn1, 3, 3, 0, 150, 0x1401, 0x1400, 0x1402);

MFBD_NBTN_DEFINE(test_nbtn, 2, 3, 30, 150, 0x1301, 0x1300, 0x1301);
#endif /* MFBD_USE_NORMAL_BUTTON */

/* mbtn test */
#if MFBD_USE_MULTIFUCNTION_BUTTON
/* MFBD_MBTN_DEFINE(NAME, BTN_INDEX, FILTER_TIME, REPEAT_TIME, LONG_TIME, MULTICLICK_TIME, MAX_MULTICLICK_STATE, BTN_DOWN_CODE, BTN_UP_CODE, BTN_LONG_CODE, ...) */
MFBD_MBTN_DEFINE(test_mbtn, 4, 3, 30, 150, 75, 3, 0x1501, 0x1500, 0x1501, 0x1511, 0x1521, 0x1531);
#endif /* MFBD_USE_MULTIFUCNTION_BUTTON */

#endif /*MFBD_PARAMS_SAME_IN_GROUP*/

#if MFBD_USE_TINY_BUTTON
MFBD_TBTN_ARRAYLIST(test_tbtn_list, &test_tbtn);
#endif /* MFBD_USE_TINY_BUTTON */

#if MFBD_USE_NORMAL_BUTTON
MFBD_NBTN_ARRAYLIST(test_nbtn_list, &test_nbtn1, &test_nbtn);
#endif /* MFBD_USE_NORMAL_BUTTON */

#if MFBD_USE_MULTIFUCNTION_BUTTON
MFBD_MBTN_ARRAYLIST(test_mbtn_list, &test_mbtn);
#endif /* MFBD_USE_MULTIFUCNTION_BUTTON */

const mfbd_group_t test_btn_group =
{
    bsp_btn_check,
    bsp_btn_value_report,

#if MFBD_USE_TINY_BUTTON
    test_tbtn_list,
#endif /* MFBD_USE_TINY_BUTTON */

#if MFBD_USE_NORMAL_BUTTON
    test_nbtn_list,
#endif /* MFBD_USE_NORMAL_BUTTON */

#if MFBD_USE_MULTIFUCNTION_BUTTON
    test_mbtn_list,
#endif /* MFBD_USE_MULTIFUCNTION_BUTTON */

#if MFBD_PARAMS_SAME_IN_GROUP

#if MFBD_USE_TINY_BUTTON || MFBD_USE_NORMAL_BUTTON || MFBD_USE_MULTIFUCNTION_BUTTON
    3,
#endif /*  MFBD_USE_TINY_BUTTON || MFBD_USE_NORMAL_BUTTON || MFBD_USE_MULTIFUCNTION_BUTTON */

#if MFBD_USE_NORMAL_BUTTON || MFBD_USE_MULTIFUCNTION_BUTTON
    30,
    150,
#endif /* MFBD_USE_NORMAL_BUTTON || MFBD_USE_MULTIFUCNTION_BUTTON */

#if MFBD_USE_MULTIFUCNTION_BUTTON
    75,
#endif /* MFBD_USE_MULTIFUCNTION_BUTTON */

#endif /*MFBD_PARAMS_SAME_IN_GROUP*/

};

unsigned char bsp_btn_check(mfbd_btn_index_t btn_index)
{
    switch (btn_index)
    {
    case 1:
        return read_button_GPIO(0);
    case 2:
        return read_button_GPIO(1);
    case 3:
        return read_button_GPIO(2);
    case 4:
        return read_button_GPIO(3);
    default:
        break;
    }
    return 0;
}

void bsp_btn_value_report(mfbd_btn_code_t btn_value)
{
    printf("report %04x\n", btn_value);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    pthread_t id;
    pthread_create(&id, NULL, (void  *)thread, NULL);
    
    while(1) {
        mfbd_group_scan(&test_btn_group); /* scan button group */
        usleep(10000); // 10 ms
    }
    return 0;
}