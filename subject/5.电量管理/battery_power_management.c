#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define BATTERY_POWER_CHANGE_BUFFER_TIME    60
#define BATTERY_POWER_LEVEL_SUM             11
#define BATTERY_POWER_LEVEL_MIN             0
#define BATTERY_POWER_LEVEL_MAX             100

#define BATTERY_POWER_TRANSITION_COUNT      5

typedef enum
{
    NORMAL,
    RECHARGE,
    NORMAL_TO_RECHARGE,
    RECHARGE_TO_NORMAL,
} battery_power_state_e;

typedef enum
{
    NOT_CHARGING,
    RECHARGING,
} battery_power_recharge_state_e;

typedef struct
{
    battery_power_state_e state;
    unsigned int offset;
    unsigned int percentage;
    unsigned int is_recharge;
    unsigned int time;
    unsigned int change_time;
    unsigned int voltage;
    unsigned int change_voltage;
    //unsigned int level;
    unsigned int transition_percentage;
    unsigned int transition_count;
    
    unsigned int level_sum;
} battery_power_api_t;

typedef struct
{
    unsigned int voltage;
    unsigned int percentage;
} battery_power_list_t;

battery_power_list_t battery_power_list[] = 
{
    { 800,    0},
    {1000,   10};
    {2000,   20};
    {3000,   30};
    {4000,   40};
    {5000,   50};
    {6000,   60};
    {7000,   70};
    {8000,   80};
    {9000,   90};
    {9500,  100};
};

volatile static battery_power_api_t battery_power_api;

unsigned int battery_power_management_level_calculation(void)
{
    unsigned int voltage;
    unsigned int percentage;
    int i;
    
    voltage = battery_power_api.voltage - battery_power_api.offset;
    
    if(voltage < battery_power_list[0].voltage)
    {
        return battery_power_list[0].percentage;
    }
    else if(voltage > battery_power_list[BATTERY_POWER_LEVEL_SUM - 1].voltage)
    {
        return battery_power_list[BATTERY_POWER_LEVEL_SUM - 1].percentage;
    }
    
    for(i = 1; i < BATTERY_POWER_LEVEL_SUM; i++)
    {
        if(voltage < battery_power_list[i].voltage)
        {
            percentage = (voltage - battery_power_list[i - 1].voltage)*(battery_power_list[i].percentage - battery_power_list[i - 1].percentage)/(battery_power_list[i].voltage - battery_power_list[i - 1].voltage) + battery_power_list[i - 1].percentage;
        }
    }
    
    return percentage;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
void battery_power_management_full_power_process(void)
{
    unsigned int voltage;
    unsigned int diff;
    unsigned int threshold_voltage;
    unsigned int percentage;
    int i;
    
    voltage = battery_power_api.voltage;
    diff = (battery_power_list[BATTERY_POWER_LEVEL_SUM - 1].voltage - battery_power_list[BATTERY_POWER_LEVEL_SUM - 2].voltage) / 2;
    threshold_voltage = battery_power_list[BATTERY_POWER_LEVEL_SUM - 2].voltage + diff;
    
    if(voltage > threshold_voltage)
    {
        
    }
    
    
    if(battery_power_api.voltage > battery_power_list[BATTERY_POWER_LEVEL_SUM - 1].voltage)
    {
        //计算电压是否稳定
    }
}

void battery_power_management_poll(void)
{
    unsigned int percentage;
    
    if(battery_power_api.state == NORMAL)
    {
        //计算当前的百分比
        percentage = battery_power_management_level_calculation();
        
        if(percentage < battery_power_api.percentage)
            battery_power_api.percentage = percentage;
        
    }
    else if(battery_power_api.state == RECHARGE)
    {
        //计算当前的百分比
        percentage = battery_power_management_level_calculation();
        
        if(percentage > battery_power_api.percentage)
            battery_power_api.percentage = percentage;
    }
    else if(battery_power_api.state == NORMAL_TO_RECHARGE)
    {
        //等待一段缓冲时间，保证电压稳定
        if((battery_power_api.time - battery_power_api.change_time) > BATTERY_POWER_CHANGE_BUFFER_TIME)
        {
            unsigned int val = 0;
            
            //是否更新了偏差电压
            if(!battery_power_api.offset)
            {
                //偏差电压 = 接入电源时的充电电压 - 充电前正常的电池电压
                battery_power_api.offset = battery_power_api.voltage - battery_power_api.change_voltage;
            }
            
            //计算当前的百分比
            percentage = battery_power_management_level_calculation();
            
            //
            if(!battery_power_api.transition_percentage)
            {
                //记录稳定时的百分比
                battery_power_api.transition_percentage = percentage；
            }

            //当前的百分比 > 上次的计算的百分比
            if(percentage > battery_power_api.transition_percentage)
            {
                //计算百分比的差值，再乘以一个系数
                val = (percentage - battery_power_api.transition_percentage) * 3 / 2;
            }
            else
            {
                val = 0;
            }
            
            if((battery_power_api.percentage + val) > percentage)
                battery_power_api.percentage = percentage;
            else
                battery_power_api.percentage += val;
            
            battery_power_api.transition_percentage = percentage;
            
            if(battery_power_api.percentage == percentage)
            {
                battery_power_api.state = RECHARGE;
                battery_power_api.transition_percentage = 0;
            }
        }
    }
    else if(battery_power_api.state == RECHARGE_TO_NORMAL)
    {
        //等待一段缓冲时间，保证电压稳定
        if((battery_power_api.time - battery_power_api.change_time) > BATTERY_POWER_CHANGE_BUFFER_TIME)
        {
            unsigned int val = 0;
            
            battery_power_api.offset = 0;
            
            //计算当前的百分比
            percentage = battery_power_management_level_calculation();
            
            //
            if(!battery_power_api.transition_percentage)
            {
                //记录稳定时的百分比
                battery_power_api.transition_percentage = percentage；
            }

            //当前的百分比 < 上次的计算的百分比
            if(percentage < battery_power_api.transition_percentage)
            {
                //计算百分比的差值，再乘以一个系数
                val = (battery_power_api.transition_percentage - percentage) * 3 / 2;
            }
            else
            {
                val = 0;
            }
            
            if(battery_power_api.percentage < (percentage + val))
                battery_power_api.percentage = percentage;
            else
                battery_power_api.percentage -= val;
            
            battery_power_api.transition_percentage = percentage;
            
            if(battery_power_api.percentage == percentage)
            {
                battery_power_api.state = NORMAL;
                battery_power_api.transition_percentage = 0;
            }
        }
    }
}

unsigned int battery_power_management_timer(void)
{
    ++battery_power_api.time;
}

unsigned int battery_power_management_get_percentage(void)
{
    return battery_power_api.percentage;
}

int battery_power_management_set_voltage(unsigned int voltage)
{
    battery_power_api.voltage = voltage;
    
    return 0;
}

int battery_power_management_set_recharge_state(unsigned int is_recharge)
{
    if(battery_power_api.is_recharge != is_recharge)
    {
        if(battery_power_api.state == NORMAL)
        {
            if(battery_power_api.is_recharge == NOT_CHARGING)
            {
                battery_power_api.state = NORMAL_TO_RECHARGE;
                
                battery_power_api.change_time = battery_power_api.time;
                battery_power_api.change_voltage = battery_power_api.voltage;
            }
        }
        else if(battery_power_api.state == RECHARGE)
        {
            if(battery_power_api.is_recharge == RECHARGING)
            {
                battery_power_api.state = RECHARGE_TO_NORMAL;
                
                battery_power_api.change_time = battery_power_api.time;
                battery_power_api.change_voltage = battery_power_api.voltage;
                battery_power_api.offset = 0;
            }
        }
        else if(battery_power_api.state == NORMAL_TO_RECHARGE)
        {
            battery_power_api.state = RECHARGE_TO_NORMAL;
        }
        else if(battery_power_api.state == RECHARGE_TO_NORMAL)
        {
            battery_power_api.state = NORMAL_TO_RECHARGE;
        }
        
        battery_power_api.is_recharge = is_recharge;
    }
    
    return 0;
}

int battery_power_management_registered(void)
{
    return 0;
}

int battery_power_management_init(void)
{
    memset(battery_power_api, 0, sizeof(battery_power_api));
    
    
    
    return 0;
}