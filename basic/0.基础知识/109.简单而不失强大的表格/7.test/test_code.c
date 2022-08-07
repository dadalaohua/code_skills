#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
#ifndef dimof
#define dimof(__array)     (sizeof(__array)/sizeof(__array[0]))
#endif


#define __impl_table(__item_type, ...)                   \
    .ptItems = (__item_type []) {                        \
        __VA_ARGS__                                      \
    },                                                   \
    .hwCount = sizeof((__item_type []) { __VA_ARGS__ })  \
             / sizeof(__item_type),                      \
    .hwItemSize = sizeof(__item_type)

#define impl_table(__item_type, ...)                     \
    __impl_table(__item_type, __VA_ARGS__)
/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef struct msg_item_t msg_item_t;

struct msg_item_t {
    uint8_t chID;                 //!< 指令
    uint8_t chAccess;             //!< 访问权限检测
    uint16_t hwValidDataSize;     //!< 数据长度要求
    bool (*fnHandler)(msg_item_t *ptMSG,   
                      void *pData, 
                      uint_fast16_t hwSize);
};

typedef struct msgmap_t msgmap_t;

struct msgmap_t {
    uint16_t hwItemSize;
    uint16_t hwCount;
    msg_item_t *ptItems;
    bool (*fnHandler)(msgmap_t *ptMSGMap,
                      uint_fast8_t chID,
                      void *pData,
                      uint_fast16_t hwSize);
};

bool msgmap_user_mode_handler(msgmap_t *ptMSGMap,
                      uint_fast8_t chID,
                      void *pData,
                      uint_fast16_t hwSize);

bool msgmap_debug_mode_handler(msgmap_t *ptMSGMap,
                      uint_fast8_t chID,
                      void *pData,
                      uint_fast16_t hwSize);

typedef enum {
    USER_MODE = 0,    //!< 普通的用户模式
    SETUP_MODE,       //!< 出厂后的安装模式
    DEBUG_MODE,       //!< 工程师专用的调试模式
    FACTORY_MODE,     //!< 最高权限的工厂模式
} comm_mode_t;

typedef struct cmd_modes_t cmd_modes_t;

struct cmd_modes_t {
    uint16_t hwItemSize;
    uint16_t hwCount;
    msgmap_t *ptItems;
};

const cmd_modes_t c_tCMDModes = {
    impl_table(msgmap_t,
        [USER_MODE] = {
            impl_table(msg_item_t,
                [0] = {
                    .chID = 0,
                    .fnHandler = NULL,
                },
                [1] = {
                    .chID = 0,
                    .fnHandler = NULL,
                },
            ),
            .fnHandler = &msgmap_user_mode_handler,
        },
        [SETUP_MODE] = {
            impl_table(msg_item_t,
                [0] = {
                    .chID = 0,
                    .fnHandler = NULL,
                },
                [1] = {
                    .chID = 0,
                    .fnHandler = NULL,
                },
            ),
            .fnHandler = NULL, //!< 使用默认的处理函数
        },
        [DEBUG_MODE] = {
            impl_table(msg_item_t,
                [0] = {
                    .chID = 0,
                    .fnHandler = NULL,
                },
            ),
            .fnHandler = &msgmap_debug_mode_handler,
        },
        [FACTORY_MODE] = {
            impl_table(msg_item_t,
                [0] = {
                    .chID = 0,
                    .fnHandler = NULL,
                },
            ),
            //.fnHandler = NULL  什么都不写，就是NULL（0）
        },
    ),
};
/************************************************************************/
/*                                                                      */
/************************************************************************/
static volatile uint8_t s_chCurrentAccessPermission;

/*! \brief 搜索消息地图，并执行对应的处理程序
 *! \retval false  消息不存在或者消息处理函数觉得内容无效
 *! \retval true   消息得到了正确的处理
 */

bool msgmap_user_mode_handler(msgmap_t *ptMSGMap,
                      uint_fast8_t chID,
                      void *pData,
                      uint_fast16_t hwSize)
{
    for (int n = 0; n < ptMSGMap->hwCount; n++) {
        msg_item_t *ptItem = (msg_item_t *)&(ptMSGMap->ptItems[n]);
        if (chID != ptItem->chID) {
            continue;
        }
        if (!(ptItem->chAccess & s_chCurrentAccessPermission)) {
            continue;  //!< 当前的访问属性没有一个符合要求
        }
        if (hwSize < ptItem->hwValidDataSize) {
            continue;  //!< 数据太小了
        }
        if (NULL == ptItem->fnHandler) {
            continue;  //!< 无效的指令？（不应该发生）
        }
        
        //! 调用消息处理函数
        return ptItem->fnHandler(ptItem, pData, hwSize);
    }
    
    return false;   //!< 没找到对应的消息
}

bool msgmap_debug_mode_handler(msgmap_t *ptMSGMap,
                      uint_fast8_t chID,
                      void *pData,
                      uint_fast16_t hwSize)
{
    for (int n = 0; n < ptMSGMap->hwCount; n++) {
        msg_item_t *ptItem = (msg_item_t *)&(ptMSGMap->ptItems[n]);
        if (chID != ptItem->chID) {
            continue;
        }
        if (!(ptItem->chAccess & s_chCurrentAccessPermission)) {
            continue;  //!< 当前的访问属性没有一个符合要求
        }
        if (hwSize < ptItem->hwValidDataSize) {
            continue;  //!< 数据太小了
        }
        if (NULL == ptItem->fnHandler) {
            continue;  //!< 无效的指令？（不应该发生）
        }
        
        //! 调用消息处理函数
        return ptItem->fnHandler(ptItem, pData, hwSize);
    }
    
    return false;   //!< 没找到对应的消息
}

bool search_msgmap(const msgmap_t *ptMSGMap,
                   uint_fast8_t chID,
                   void *pData,
                   uint_fast16_t hwSize)
{
    for (int n = 0; n < ptMSGMap->hwCount; n++) {
        msg_item_t *ptItem = (msg_item_t *)&(ptMSGMap->ptItems[n]);
        if (chID != ptItem->chID) {
            continue;
        }
        if (!(ptItem->chAccess & s_chCurrentAccessPermission)) {
            continue;  //!< 当前的访问属性没有一个符合要求
        }
        if (hwSize < ptItem->hwValidDataSize) {
            continue;  //!< 数据太小了
        }
        if (NULL == ptItem->fnHandler) {
            continue;  //!< 无效的指令？（不应该发生）
        }
        
        //! 调用消息处理函数
        return ptItem->fnHandler(ptItem, pData, hwSize);
    }
    
    return false;   //!< 没找到对应的消息
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
bool frame_process_backend(comm_mode_t tWorkMode,
                           uint_fast8_t chID,
                           void *pData,
                           uint_fast16_t hwSize)
{
    msgmap_t *ptMSGMap = &c_tCMDModes.ptItems[tWorkMode];
    if (tWorkMode > FACTORY_MODE) {
        return false;
    }
    
    //! 调用每个消息地图自己的处理程序
    if (NULL != ptMSGMap->fnHandler) {
         return ptMSGMap->fnHandler(ptMSGMap, 
                                    chID,
                                    pData,
                                    hwSize);
    }
    //! 默认的消息地图处理程序
    return search_msgmap( ptMSGMap, 
                          chID,
                          pData,
                          hwSize);
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    
    return 0;
}