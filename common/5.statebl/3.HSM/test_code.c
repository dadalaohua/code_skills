#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include  "hsm.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/
//--超类/父类
S_state_fun father_state[2] = {
    {{F_Static_Init, F_Static_Keep, F_Satic_Done, F_Static_Default   }},
    {{F_Run_Init,    F_Run_Keep,    F_Run_Done,   F_Run_Default      }}
};

//--子类1
S_state_fun childer_state[8] = {
    {{C_Static_Set_Init,                     C_Static_Set_Keep,                  C_Satic_Set_Done,                   C_Static_Set_Default                    }},
    {{C_Static_Distribution_Network_Init,    C_Static_Distribution_Network_Keep, C_Satic_Distribution_Network_Done,  C_Static_Distribution_Network_Default   }},
    {{C_Static_Shut_Down_Init,               C_Static_Shut_Down_Keep,            C_Satic_Shut_Down_Done,             C_Static_Shut_Down_Default              }},
    {{C_Static_Charge_Init,                  C_Static_Charge_Keep,               C_Satic_Charge_Done,                C_Static_Charge_Default                 }},
    {{C_Run_Normal_Init,                     C_Run_Normal_Keep,                  C_Run_Normal_Done,                  C_Run_Normal_Default                    }},
    {{C_Run_Dry_Init,                        C_Run_Dry_Keep,                     C_Run_Dry_Done,                     C_Run_Dry_Default                       }},
    {{C_Run_Besiege_Init,                    C_Run_Besiege_Keep,                 C_Run_Besiege_Done,                 C_Run_Besiege_Default                   }},
    {{C_Run_Avoid_Obstacles_Init,            C_Run_Avoid_Obstacles_Keep,         C_Run_Avoid_Obstacles_Done,         C_Run_Avoid_Obstacles_Default           }}
};

//--父类单个状态内部转换步骤
E_father_states s_father_step   = s_father_init ;
E_childer_states s_childer_step = s_childer_init;

//--父类初始化
E_hsm_father_state hsm_current_father_state = e_static_state;
E_hsm_father_state hsm_last_father_state    = e_static_state;

//--子类初始化
E_hsm_childer_state hsm_current_childer_state = e_set_state;
E_hsm_childer_state hsm_last_childer_state    = e_set_state;

/************************************************************************/
/*                                                                      */
/************************************************************************/
/****************************************************************************
函数  
状态函数命名规则
     例 ： C_Static_Set_Init 
              C   ＿  Static_   Set  _    Init
         Ｃ：子类 Ｆ：父类＿依附的父类＿子类本身名字＿该子类状态内部阶段
****************************************************************************/

//--子状态是否允许跳转
uint8_t Childer_State_Is_Allow_Jump(void)
{
    if(s_childer_step == s_childer_init)
        return 1;
    else   
        return 0;
}

//--子状态是否要发生状态转换
uint8_t Is_Three_A_Childer_State_Transition(void)
{
    if(hsm_last_childer_state == hsm_current_childer_state)
        return 0;
    else   
        return 1;
}

//--子类状态转换
void Childer_State_Transition(E_hsm_childer_state temp)
{
    hsm_current_childer_state = temp;
}

//--子类更新上一次状态
void Update_Childer_Last_State_Transition(void)
{
    hsm_last_childer_state = hsm_current_childer_state;
}

//--子类单个状态内部转换
void Childer_Step_Transition(E_childer_states temp)
{
    s_childer_step = temp;
}

//--父状态是否允许跳转
uint8_t Father_State_Is_Allow_Jump(void)
{
    if(s_father_step == s_father_init)
        return 1;
    else   
        return 0;
}

//--父状态是否要发生状态转换
uint8_t Is_Three_A_Father_State_Transition(void)
{
    if(hsm_last_father_state == hsm_current_father_state)
        return 0;
    else   
        return 1;
}

//--父类状态转换
void Father_State_Transition(E_hsm_father_state temp)
{
    hsm_current_father_state = temp;
}

//--父类更新上一次状态
void Update_Father_Last_State_Transition(void)
{
    hsm_last_father_state = hsm_current_father_state;
}

//--父类状态内部转换
void Father_Step_Transition(E_father_states temp)
{
    s_father_step = temp;
}

/*************************************************
 * 静止状态（父类）
 * 进入函数
 * 保持函数
 * 退出函数
 * 错误函数
 * *************************************************/
void F_Static_Init(void)
{
    Update_Father_Last_State_Transition();
    //---------------------
    //--代码段
    printf("===父类：静止状态====进入函数>>>>>>>>>>>>>>>>>>>>>\r\n");
    //--------------------
    Father_Step_Transition(s_father_keep);
}

void F_Static_Keep(void)
{
    //---------------------
    //--代码段
    // printf("===父类：静止状态====保持函数--------------------\r\n");
    //==========子类状态机调度器======================
    if(Childer_State_Is_Allow_Jump())//--如果允许跳转
    {
        //--如果父类出现类跳转，子类已经做好跳转的准备，但是父类还未做好跳转的准备，此时不执行子类跳转
        if(Is_Three_A_Father_State_Transition())
        {
            Father_Step_Transition(s_father_done);
            return;
        }  
        else
            Father_Step_Transition(s_father_keep);
        
        childer_state[hsm_current_childer_state].steps[s_childer_step]();   //--子类状态
    }
    else
        childer_state[hsm_last_childer_state].steps[s_childer_step]();      //--子类状态
}

void F_Satic_Done(void)
{
    //---------------------
    //--代码段
    printf("===父类：静止状态====退出函数<<<<<<<<<<<<<<<<<<<<<<<<\r\n");
    //--------------------
    //--内部切换
    Father_Step_Transition(s_father_init);
}

void F_Static_Default(void)
{
    ;
}

/*************************************************
 * 运行状态（父类）
 * 进入函数
 * 保持函数
 * 退出函数
 * 错误函数
 * *************************************************/
void F_Run_Init(void)
{
    Update_Father_Last_State_Transition();
    //---------------------
    //--代码段
    printf("===父类：运行状态====进入函数>>>>>>>>>>>>>>>>>>>>>>>>>>\r\n");
    //--------------------
    Father_Step_Transition(s_father_keep);
}

void F_Run_Keep(void)
{
    //---------------------
    //--代码段
    //printf("===父类：运行状态====保持函数--------------------\r\n");
    //==========子类状态机调度器======================
    if(Childer_State_Is_Allow_Jump())//--如果允许跳转
    {
        //--如果父类出现类跳转，子类已经做好跳转的准备，但是父类还未做好跳转的准备，此时不执行子类跳转
        if(Is_Three_A_Father_State_Transition())
        {
            Father_Step_Transition(s_father_done);
            return;
        }
        else
            Father_Step_Transition(s_father_keep);
        
        childer_state[hsm_current_childer_state].steps[s_childer_step]();//--子类状态
    }
    else
        childer_state[hsm_last_childer_state].steps[s_childer_step]();//--子类状态
}

void F_Run_Done(void)
{
    //---------------------
    //--代码段
    printf("===父类：运行状态====退出函数<<<<<<<<<<<<<<<<<<<<<<\r\n");
    //--------------------
    //--内部切换
    Father_Step_Transition(s_father_init);
}

void F_Run_Default(void)
{
    ;
}

/*************************************************
 * 设置状态（子类）依附静止（父类）
 * 进入函数
 * 保持函数
 * 退出函数
 * 错误函数
 * *************************************************/
void C_Static_Set_Init(void)
{
    Update_Childer_Last_State_Transition();
    //---------------------
    //--代码段
    printf("===子类：设置状态====进入函数>>>\r\n");
    //--------------------
    Childer_Step_Transition(s_childer_keep);
}

void C_Static_Set_Keep(void)
{
    //---------------------
    //--代码段
    printf("===子类：设置状态====保持函数\r\n");
    //--------------------
    if(Is_Three_A_Childer_State_Transition())
        Childer_Step_Transition(s_childer_done); 
    else
        Childer_Step_Transition(s_childer_keep);
}

void C_Satic_Set_Done(void)
{
    //---------------------
    //--代码段
    printf("===子类：设置状态====退出函数<<<\r\n");
    //--------------------
    //--内部切换
    Childer_Step_Transition(s_childer_init);
}

void C_Static_Set_Default(void)
{
    ;
}

/*************************************************
 * 配网状态（子类）依附静止（父类）
 * 进入函数
 * 保持函数
 * 退出函数
 * 错误函数
 * *************************************************/
void C_Static_Distribution_Network_Init(void)
{
    Update_Childer_Last_State_Transition();
    //---------------------
    //--代码段
    printf("===子类：陪网状态====进入函数>>>\r\n");
    //--------------------
    Childer_Step_Transition(s_childer_keep);
}

void C_Static_Distribution_Network_Keep(void)
{
    //---------------------
    //--代码段
    printf("===子类：陪网状态====保持函数\r\n");
    //--------------------
    if(Is_Three_A_Childer_State_Transition())
        Childer_Step_Transition(s_childer_done); 
    else
        Childer_Step_Transition(s_childer_keep);
}

void C_Satic_Distribution_Network_Done(void)
{
    //---------------------
    //--代码段
    printf("===子类：陪网状态====退出函数<<<\r\n");
    //--------------------
    //--内部切换
    Childer_Step_Transition(s_childer_init);
}

void C_Static_Distribution_Network_Default(void)
{
    ;
}

/*************************************************
 * 待机状态（子类）依附静止（父类）
 * 进入函数
 * 保持函数
 * 退出函数
 * 错误函数
 * *************************************************/
void C_Static_Shut_Down_Init(void)
{
    Update_Childer_Last_State_Transition();
    //---------------------
    //--代码段
    printf("===子类：待机状态====进入函数>>>\r\n");
    //--------------------
    Childer_Step_Transition(s_childer_keep);
}

void C_Static_Shut_Down_Keep(void)
{
    //---------------------
    //--代码段
    printf("===子类：待机状态====保持函数\r\n");
    //--------------------
    if(Is_Three_A_Childer_State_Transition())
        Childer_Step_Transition(s_childer_done); 
    else
        Childer_Step_Transition(s_childer_keep);
}

void C_Satic_Shut_Down_Done(void)
{
    //---------------------
    //--代码段
    printf("===子类：待机状态====退出函数<<<\r\n");
    //--------------------
    //--内部切换
    Childer_Step_Transition(s_childer_init);
}

void  C_Static_Shut_Down_Default(void)
{
    ;
}

/*************************************************
 * 充电状态（子类）依附静止（父类）
 * 进入函数
 * 保持函数
 * 退出函数
 * 错误函数
 * *************************************************/

void C_Static_Charge_Init(void)
{
    Update_Childer_Last_State_Transition();
    //---------------------
    //--代码段
    printf("===子类：充电状态====进入函数>>>\r\n");
    //--------------------
    Childer_Step_Transition(s_childer_keep);
}

void  C_Static_Charge_Keep(void)
{
    //---------------------
    //--代码段
    printf("===子类：充电状态====保持函数\r\n");
    //--------------------
    if(Is_Three_A_Childer_State_Transition())
        Childer_Step_Transition(s_childer_done); 
    else
        Childer_Step_Transition(s_childer_keep);
}

void  C_Satic_Charge_Done(void)
{
    //---------------------
    //--代码段
    printf("===子类：充电状态====退出函数<<<\r\n");
    //--------------------
    //--内部切换
    Childer_Step_Transition(s_childer_init);
}

void C_Static_Charge_Default(void)
{
    ;
}

/*************************************************
 * 正常状态（子类）依附运行（父类）
 * 进入函数
 * 保持函数
 * 退出函数
 * 错误函数
 * *************************************************/
void C_Run_Normal_Init(void)
{
    Update_Childer_Last_State_Transition();
    //---------------------
    //--代码段
    printf("===子类：正常状态====进入函数>>>\r\n");
    //--------------------
    Childer_Step_Transition(s_childer_keep);
}

void C_Run_Normal_Keep(void)
{
    //---------------------
    //--代码段
    printf("===子类：正常状态====保持函数\r\n");
    //--------------------
    if(Is_Three_A_Childer_State_Transition())
        Childer_Step_Transition(s_childer_done); 
    else
        Childer_Step_Transition(s_childer_keep);
}

void C_Run_Normal_Done(void)
{
    //---------------------
    //--代码段
    printf("===子类：正常状态====退出函数<<<\r\n");
    //--------------------
    //--内部切换
    Childer_Step_Transition(s_childer_init);
}

void C_Run_Normal_Default(void)
{
    ;
}

/*************************************************
 * 干托状态（子类）依附运行（父类）
 * 进入函数
 * 保持函数
 * 退出函数
 * 错误函数
 * *************************************************/
void C_Run_Dry_Init(void)
{
    Update_Childer_Last_State_Transition();
    //---------------------
    //--代码段
    printf("===子类：干托状态====进入函数>>>\r\n");
    //--------------------
    Childer_Step_Transition(s_childer_keep);
}

void C_Run_Dry_Keep(void)
{
    //---------------------
    //--代码段
    printf("===子类：干托状态====保持函数\r\n");
    //--------------------
    if(Is_Three_A_Childer_State_Transition())
        Childer_Step_Transition(s_childer_done); 
    else
        Childer_Step_Transition(s_childer_keep);
}

void C_Run_Dry_Done(void)
{
    //---------------------
    //--代码段
    printf("===子类：干托状态====退出函数<<<\r\n");
    //--------------------
    //--内部切换
    Childer_Step_Transition(s_childer_init);
}

void C_Run_Dry_Default(void)
{
    ;
}

/*************************************************
 * 受困状态（子类）依附运行（父类）
 * 进入函数
 * 保持函数
 * 退出函数
 * 错误函数
 * *************************************************/
void C_Run_Besiege_Init(void)
{
    Update_Childer_Last_State_Transition();
    //---------------------
    //--代码段
    printf("===子类：受困状态====进入函数>>>\r\n");
    //--------------------
    Childer_Step_Transition(s_childer_keep);
}

void C_Run_Besiege_Keep(void)
{
    //---------------------
    //--代码段
    printf("===子类：受困状态====保持函数\r\n");
    //--------------------
    if(Is_Three_A_Childer_State_Transition())
        Childer_Step_Transition(s_childer_done); 
    else
        Childer_Step_Transition(s_childer_keep);
}

void C_Run_Besiege_Done(void)
{
   //---------------------
   //--代码段
   printf("===子类：受困状态====退出函数<<<\r\n");
   //--------------------
   //--内部切换
   Childer_Step_Transition(s_childer_init);
}

void C_Run_Besiege_Default(void)
{
    ;
}

/*************************************************
 * 避障状态（子类）依附运行（父类）
 * 进入函数
 * 保持函数
 * 退出函数
 * 错误函数
 * *************************************************/
void C_Run_Avoid_Obstacles_Init(void)
{
    Update_Childer_Last_State_Transition();
    //---------------------
    //--代码段
    printf("===子类：避障状态====进入函数>>>\r\n");
    //--------------------
    Childer_Step_Transition(s_childer_keep);
}

void C_Run_Avoid_Obstacles_Keep(void)
{
    //---------------------
    //--代码段
    printf("===子类：避障状态====保持函数\r\n");
    //--------------------
    if(Is_Three_A_Childer_State_Transition())
        Childer_Step_Transition(s_childer_done); 
    else
        Childer_Step_Transition(s_childer_keep);
}

void C_Run_Avoid_Obstacles_Done(void)
{
    //---------------------
    //--代码段
    printf("===子类：避障状态====退出函数<<<\r\n");
    //--------------------
    //--内部切换
    Childer_Step_Transition(s_childer_init);
}

void C_Run_Avoid_Obstacles_Default(void)
{
    ;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int update_cnt = 10;
    
    while(1)
    {
        if(update_cnt == 80)
        {
            hsm_current_father_state    =   e_static_state;     //静止状态
            hsm_current_childer_state   =   e_set_state;        //设置状态
        }
        else if(update_cnt == 70)
        {
            hsm_current_father_state    =   e_static_state;     //静止状态
            hsm_current_childer_state   =   e_distribution_network_state;   //陪网状态
        }
        else if(update_cnt == 60)
        {
            hsm_current_father_state    =   e_static_state;     //静止状态
            hsm_current_childer_state   =   e_shut_down_state;  //待机状态
        }
        else if(update_cnt == 50)
        {
            hsm_current_father_state    =   e_static_state;     //静止状态
            hsm_current_childer_state   =   e_charge_state;     //充电状态
        }
        else if(update_cnt == 40)
        {
            hsm_current_father_state    =   e_run_state;        //运行状态
            hsm_current_childer_state   =   e_Normal_state;     //正常状态
        }
        else if(update_cnt == 30)
        {
            hsm_current_father_state    =   e_run_state;        //运行状态
            hsm_current_childer_state   =   e_dry_state;        //干托状态
        }
        else if(update_cnt == 20)
        {
            hsm_current_father_state    =   e_run_state;        //运行状态
            hsm_current_childer_state   =   e_besiege_state;    //受困状态
        }
        else if(update_cnt == 10)
        {
            hsm_current_father_state    =   e_run_state;        //运行状态
            hsm_current_childer_state   =   e_avoid_obstacles;  //避障状态
        }
        
        usleep(200*1000);
        update_cnt--;
        if(update_cnt == 0)
            update_cnt = 80;

        // printf("hsm_current_father_state:%d hsm_current_childer_state:%d\r\n",hsm_current_father_state,hsm_current_childer_state);
        //=================================父类状态机调度器=========================================
        if(Father_State_Is_Allow_Jump())//--如果允许跳转
            father_state[hsm_current_father_state].steps[s_father_step]();//--父类状态
        else
            father_state[hsm_last_father_state].steps[s_father_step]();//--父类状态
        //==========================================================================

    }
 
    return 0;
}