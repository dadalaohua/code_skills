/****************************************************************************
作者：小鱼儿飞丫飞
日期：2020-6-19
文件名：FSM层次状态机头文件
****************************************************************************/
#ifndef  __HSM_H__
#define  __HSM_H__

/****************************************************************************
头文件
****************************************************************************/
#include "stdio.h"

/****************************************************************************
宏定义
****************************************************************************/
#define KEPP_STATE_CNT (5)
#define uint8_t  unsigned char

/****************************************************************************
变量
****************************************************************************/
typedef void (*procedure) (void); //--函数指针

//--定义状态
typedef enum _FATHER_STATES{
    s_father_init =0,  
    s_father_keep,
    s_father_done,
    s_father_default,
}E_father_states;

E_father_states s_father_step;  //--父类单个状态内部转换步骤

typedef enum _CHILDER_STATES{
    s_childer_init = 0,  
    s_childer_keep,
    s_childer_done,
    s_childer_default,
}E_childer_states;

E_childer_states s_childer_step;    //--子类单个状态内部转换步骤

//--定义状态成员函数
typedef struct __STATES_FUN{
    procedure steps[4];         //--函数指针数组
}S_state_fun;

S_state_fun father_state[2];    //--超类集合
S_state_fun childer_state[8];   //--子类集合

typedef  enum {
    e_static_state = 0,     //静止状态
    e_run_state,            //运行状态
}E_hsm_father_state;

E_hsm_father_state hsm_current_father_state;   //--当前父状态
E_hsm_father_state hsm_last_father_state;      //-上一次父状态

typedef  enum {
    e_set_state = 0,                //设置状态
    e_distribution_network_state,   //陪网状态
    e_shut_down_state,              //待机状态
    e_charge_state,                 //充电状态
    e_Normal_state,                 //正常状态
    e_dry_state,                    //干托状态
    e_besiege_state,                //受困状态
    e_avoid_obstacles               //避障状态
}E_hsm_childer_state;

E_hsm_childer_state hsm_current_childer_state;  //--当前子状态
E_hsm_childer_state hsm_last_childer_state;     //--上一次子状态

/****************************************************************************
函数
****************************************************************************/
//--子状态是否允许跳转
uint8_t  Childer_State_Is_Allow_Jump(void);
//--子状态是否要发生状态转换
uint8_t  Is_Three_A_Childer_State_Transition(void);
//--子类状态转换
void  Childer_State_Transition(E_hsm_childer_state temp);
//--子类更新上一次状态
void  Update_Childer_Last_State_Transition(void);
//--子类单个状态内部转换
void  Childer_Step_Transition(E_childer_states temp);
//--父状态是否允许跳转
uint8_t  Father_State_Is_Allow_Jump(void);
//--父状态是否要发生状态转换
uint8_t  Is_Three_A_Father_State_Transition(void);
//--父类状态转换
void  Father_State_Transition(E_hsm_father_state temp);
//--父类更新上一次状态
void  Update_Father_Last_State_Transition(void);
//--父类状态内部转换
void  Father_Step_Transition(E_father_states temp);

/*************************************************
 * 静止状态（父类）
 * 进入函数
 * 保持函数
 * 退出函数
 * 错误函数
 * *************************************************/
void F_Static_Init(void);
void F_Static_Keep(void);
void F_Satic_Done(void);
void F_Static_Default(void);

/*************************************************
 * 运行状态（父类）
 * 进入函数
 * 保持函数
 * 退出函数
 * 错误函数
 * *************************************************/
void F_Run_Init(void);
void F_Run_Keep(void);
void F_Run_Done(void);
void F_Run_Default(void);

/*************************************************
 * 设置状态（子类）依附静止（父类）
 * 进入函数
 * 保持函数
 * 退出函数
 * 错误函数
 * *************************************************/
void C_Static_Set_Init(void);
void C_Static_Set_Keep(void);
void C_Satic_Set_Done(void);
void C_Static_Set_Default(void);

/*************************************************
 * 配网状态（子类）依附静止（父类）
 * 进入函数
 * 保持函数
 * 退出函数
 * 错误函数
 * *************************************************/
void C_Static_Distribution_Network_Init(void);
void C_Static_Distribution_Network_Keep(void);
void C_Satic_Distribution_Network_Done(void);
void C_Static_Distribution_Network_Default(void);

/*************************************************
 * 待机状态（子类）依附静止（父类）
 * 进入函数
 * 保持函数
 * 退出函数
 * 错误函数
 * *************************************************/
void C_Static_Shut_Down_Init(void);
void C_Static_Shut_Down_Keep(void);
void C_Satic_Shut_Down_Done(void);
void C_Static_Shut_Down_Default(void);
/*************************************************
 * 充电状态（子类）依附静止（父类）
 * 进入函数
 * 保持函数
 * 退出函数
 * 错误函数
 * *************************************************/
void C_Static_Charge_Init(void);
void C_Static_Charge_Keep(void);
void C_Satic_Charge_Done(void);
void C_Static_Charge_Default(void);

/*************************************************
 * 正常状态（子类）依附运行（父类）
 * 进入函数
 * 保持函数
 * 退出函数
 * 错误函数
 * *************************************************/
void C_Run_Normal_Init(void);
void C_Run_Normal_Keep(void);
void C_Run_Normal_Done(void);
void C_Run_Normal_Default(void);

/*************************************************
 * 干托状态（子类）依附运行（父类）
 * 进入函数
 * 保持函数
 * 退出函数
 * 错误函数
 * *************************************************/
void C_Run_Dry_Init(void);
void C_Run_Dry_Keep(void);
void C_Run_Dry_Done(void);
void C_Run_Dry_Default(void);

/*************************************************
 * 受困状态（子类）依附运行（父类）
 * 进入函数
 * 保持函数
 * 退出函数
 * 错误函数
 * *************************************************/
void C_Run_Besiege_Init(void);
void C_Run_Besiege_Keep(void);
void C_Run_Besiege_Done(void);
void C_Run_Besiege_Default(void);

/*************************************************
 * 避障状态（子类）依附运行（父类）
 * 进入函数
 * 保持函数
 * 退出函数
 * 错误函数
 * *************************************************/
void C_Run_Avoid_Obstacles_Init(void);
void C_Run_Avoid_Obstacles_Keep(void);
void C_Run_Avoid_Obstacles_Done(void);
void C_Run_Avoid_Obstacles_Default(void);

#endif
