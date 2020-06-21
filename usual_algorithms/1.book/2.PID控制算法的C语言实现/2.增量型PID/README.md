PID控制算法的C语言实现四 增量型PID的C语言实现
   上一节中介绍了最简单的位置型PID的实现手段，这一节主要讲解增量式PID的实现方法，位置型和增量型PID的数学公式请参见我的系列文《PID控制算法的C语言实现二》中的讲解。实现过程仍然是分为定义变量、初始化变量、实现控制算法函数、算法测试四个部分，详细分类请参加《PID控制算法的C语言实现三》中的讲解，这里直接给出代码了。
/*
 * PID.c
 *
 *  Created on: 2011-11-7
 *      Author: wang
 */
#include<stdio.h>
#include<stdlib.h>

struct _pid{
    float SetSpeed;            //定义设定值
    float ActualSpeed;        //定义实际值
    float err;                //定义偏差值
    float err_next;            //定义上一个偏差值
    float err_last;            //定义最上前的偏差值
    float Kp,Ki,Kd;            //定义比例、积分、微分系数
}pid;

void PID_init(){
    pid.SetSpeed=0.0;
    pid.ActualSpeed=0.0;
    pid.err=0.0;
    pid.err_last=0.0;
    pid.err_next=0.0;
    pid.Kp=0.2;
    pid.Ki=0.015;
    pid.Kd=0.2;
}

float PID_realize(float speed){
    pid.SetSpeed=speed;
    pid.err=pid.SetSpeed-pid.ActualSpeed;
    float incrementSpeed=pid.Kp*(pid.err-pid.err_next)+pid.Ki*pid.err+pid.Kd*(pid.err-2*pid.err_next+pid.err_last);
    pid.ActualSpeed+=incrementSpeed;
    pid.err_last=pid.err_next;
    pid.err_next=pid.err;
    return pid.ActualSpeed;
}

int main(){
    PID_init();
    int count=0;
    while(count<1000)
    {
        float speed=PID_realize(200.0);
        printf("%f\n",speed);
        count++;
    }
    return 0;
}