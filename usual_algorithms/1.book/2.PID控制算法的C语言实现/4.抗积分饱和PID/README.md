PID控制算法的C语言实现六 抗积分饱和的PID控制算法C语言实现
   所谓的积分饱和现象是指如果系统存在一个方向的偏差，PID控制器的输出由于积分作用的不断累加而加大，从而导致执行机构达到极限位置，若控制器输出U(k)继续增大，执行器开度不可能再增大，此时计算机输出控制量超出了正常运行范围而进入饱和区。一旦系统出现反向偏差，u(k)逐渐从饱和区退出。进入饱和区越深则退出饱和区时间越长。在这段时间里，执行机构仍然停留在极限位置而不随偏差反向而立即做出相应的改变，这时系统就像失控一样，造成控制性能恶化，这种现象称为积分饱和现象或积分失控现象。
    防止积分饱和的方法之一就是抗积分饱和法，该方法的思路是在计算u(k)时，首先判断上一时刻的控制量u(k-1)是否已经超出了极限范围： 如果u(k-1)>umax，则只累加负偏差; 如果u(k-1)<umin，则只累加正偏差。从而避免控制量长时间停留在饱和区。直接贴出代码，不懂的看看前面几节的介绍。
struct _pid{
    float SetSpeed;            //定义设定值
    float ActualSpeed;        //定义实际值
    float err;                //定义偏差值
    float err_last;            //定义上一个偏差值
    float Kp,Ki,Kd;            //定义比例、积分、微分系数
    float voltage;            //定义电压值（控制执行器的变量）
    float integral;            //定义积分值
    float umax;
    float umin;
}pid;

void PID_init(){
    printf("PID_init begin \n");
    pid.SetSpeed=0.0;
    pid.ActualSpeed=0.0;
    pid.err=0.0;
    pid.err_last=0.0;
    pid.voltage=0.0;
    pid.integral=0.0;
    pid.Kp=0.2;
   pid.Ki=0.1;       //注意，和上几次相比，这里加大了积分环节的值
    pid.Kd=0.2;
    pid.umax=400;
    pid.umin=-200;
    printf("PID_init end \n");
}
float PID_realize(float speed){
    int index;
    pid.SetSpeed=speed;
    pid.err=pid.SetSpeed-pid.ActualSpeed;

   if(pid.ActualSpeed>pid.umax)         //灰色底色表示抗积分饱和的实现
    {

       if(abs(pid.err)>200)                    //蓝色标注为积分分离过程
        {
            index=0;
        }else{
            index=1;
            if(pid.err<0)
            {
            pid.integral+=pid.err;
            }
        }
    }else if(pid.ActualSpeed<pid.umax){
        if(abs(pid.err)>200)                    //积分分离过程
        {
            index=0;
        }else{
            index=1;
            if(pid.err>0)
            {
            pid.integral+=pid.err;
            }
        }
    }else{
        if(abs(pid.err)>200)                    //积分分离过程
        {
            index=0;
        }else{
            index=1;
            pid.integral+=pid.err;
        }
    }

    pid.voltage=pid.Kp*pid.err+index*pid.Ki*pid.integral+pid.Kd*(pid.err-pid.err_last);

    pid.err_last=pid.err;
    pid.ActualSpeed=pid.voltage*1.0;
    return pid.ActualSpeed;
}
最终的测试程序运算结果如下，可以明显的看出系统的稳定时间相对前几次来讲缩短了不少。