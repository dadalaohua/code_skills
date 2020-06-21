#include <stdio.h>

struct _pid{
    float SetSpeed;     //定义设定值
    float ActualSpeed;  //定义实际值
    float err;          //定义偏差值
    float err_last;     //定义上一个偏差值
    float Kp,Ki,Kd;     //定义比例、积分、微分系数
    float voltage;      //定义电压值（控制执行器的变量）
    float integral;     //定义积分值
}pid;

void PID_init()
{
    printf("PID_init begin \n");
    
    pid.SetSpeed    =0.0;
    pid.ActualSpeed =0.0;
    
    pid.err         =0.0;
    pid.err_last    =0.0;
    
    pid.voltage     =0.0;
    pid.integral    =0.0;
    
    pid.Kp          =0.2;
    pid.Ki          =0.04;
    pid.Kd          =0.2;
    
    printf("PID_init end \n");
}

float PID_realize(float speed)
{
    int index = 0;
    
    pid.SetSpeed    =   speed;
    pid.err         =   pid.SetSpeed - pid.ActualSpeed;
    
    if(abs(pid.err) > 200)
    {
        index = 0;
    }
    else
    {
        index = 1;
        pid.integral += pid.err;
    }
    pid.voltage     =   pid.Kp*pid.err + index*pid.Ki*pid.integral + pid.Kd*(pid.err-pid.err_last);

    pid.err_last    =   pid.err;
    pid.ActualSpeed =   pid.voltage*1.0;
    
    return pid.ActualSpeed;
}

int main(int argc, char* argv[])
{ 
    int count = 0;
    float speed = 0;
    
    printf("System begin \n");
    
    PID_init();
    
    while(count < 100)
    {
        speed = PID_realize(200.0);
        printf("%f\n",speed);
        count++;
    }
    
    return 0;
}