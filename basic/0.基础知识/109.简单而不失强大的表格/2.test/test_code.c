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

/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef struct msg_item_t msg_item_t;

struct msg_item_t {
    uint8_t chID;                 //!< 指令
    uint8_t chAccess;             //!< 访问权限检测
    uint16_t hwValidDataSize;          //!< 数据长度要求
    bool (*fnHandler)(msg_item_t *ptMSG,
                      void *pData,
                      uint_fast16_t hwSize);
};

/************************************************************************/
/*                                                                      */
/************************************************************************/
const msg_item_t c_tMSGTableUserMode[] = {
    [0] = {
        .chID = 0,
        .fnHandler = NULL,
    },
    [1] = {
        .chID = 0,
        .fnHandler = NULL,
    },
};

const msg_item_t c_tMSGTableSetupMode[] = {
    [0] = {
        .chID = 0,
        .fnHandler = NULL,
    },
    [1] = {
        .chID = 0,
        .fnHandler = NULL,
    },
};

const msg_item_t c_tMSGTableDebugMode[] = {
    [0] = {
        .chID = 0,
        .fnHandler = NULL,
    },
};

const msg_item_t c_tMSGTableFactoryMode[] = {
    [0] = {
        .chID = 0,
        .fnHandler = NULL,
    },
};
/************************************************************************/
/*                                                                      */
/************************************************************************/
static volatile uint8_t s_chCurrentAccessPermission;

/*! \brief 搜索消息地图，并执行对应的处理程序
 *! \retval false  消息不存在或者消息处理函数觉得内容无效
 *! \retval true   消息得到了正确的处理
 */
bool search_msgmap(const msg_item_t *ptMSGTable,
                   uint_fast16_t hwCount,
                   uint_fast8_t chID,
                   void *pData,
                   uint_fast16_t hwSize)
{
    for (int n = 0; n < hwCount; n++) {
        msg_item_t *ptItem = (msg_item_t *)&ptMSGTable[n];
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
typedef enum {
    USER_MODE = 0,    //!< 普通的用户模式
    SETUP_MODE,       //!< 出厂后的安装模式
    DEBUG_MODE,       //!< 工程师专用的调试模式
    FACTORY_MODE,     //!< 最高权限的工厂模式
} comm_mode_t;

bool frame_process_backend(comm_mode_t tWorkMode,
                           uint_fast8_t chID,
                           void *pData,
                           uint_fast16_t hwSize)
{
    bool bHandled = false;
    switch (tWorkMode) {
        case USER_MODE:
            bHandled = search_msgmap(
                          c_tMSGTableUserMode,
                          dimof(c_tMSGTableUserMode),
                          chID,
                          pData,
                          hwSize);
            break;
         case SETUP_MODE:
            bHandled = search_msgmap(
                          c_tMSGTableSetupMode,
                          dimof(c_tMSGTableSetupMode),
                          chID,
                          pData,
                          hwSize);
            break;
         case DEBUG_MODE:
            bHandled = search_msgmap(
                          c_tMSGTableDebugMode,
                          dimof(c_tMSGTableDebugMode),
                          chID,
                          pData,
                          hwSize);
            break;
         case FACTORY_MODE:
            bHandled = search_msgmap(
                          c_tMSGTableFactoryMode,
                          dimof(c_tMSGTableFactoryMode),
                          chID,
                          pData,
                          hwSize);
            break;
    }

    return bHandled;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    
    return 0;
}