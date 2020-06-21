PID控制算法的C语言实现三 位置型PID的C语言实现
   上一节中已经抽象出了位置性PID和增量型PID的数学表达式，这一节，重点讲解C语言代码的实现过程，算法的C语言实现过程具有一般性，通过PID算法的C语言实现，可以以此类推，设计其它算法的C语言实现。
   第一步：定义PID变量结构体，代码如下：
struct _pid{
    float SetSpeed;            //定义设定值
    float ActualSpeed;        //定义实际值
    float err;                //定义偏差值
    float err_last;            //定义上一个偏差值
    float Kp,Ki,Kd;            //定义比例、积分、微分系数
    float voltage;            //定义电压值（控制执行器的变量）
    float integral;            //定义积分值
}pid;
控制算法中所需要用到的参数在一个结构体中统一定义，方便后面的使用。
  第二部：初始化变量，代码如下：
void PID_init(){
    printf("PID_init begin \n");
    pid.SetSpeed=0.0;
    pid.ActualSpeed=0.0;
    pid.err=0.0;
    pid.err_last=0.0;
    pid.voltage=0.0;
    pid.integral=0.0;
    pid.Kp=0.2;
    pid.Ki=0.015;
    pid.Kd=0.2;
    printf("PID_init end \n");
}
统一初始化变量，尤其是Kp,Ki,Kd三个参数，调试过程当中，对于要求的控制效果，可以通过调节这三个量直接进行调节。
第三步：编写控制算法，代码如下：
float PID_realize(float speed){
    pid.SetSpeed=speed;
    pid.err=pid.SetSpeed-pid.ActualSpeed;
    pid.integral+=pid.err;
    pid.voltage=pid.Kp*pid.err+pid.Ki*pid.integral+pid.Kd*(pid.err-pid.err_last);
    pid.err_last=pid.err;
    pid.ActualSpeed=pid.voltage*1.0;
    return pid.ActualSpeed;
}
注意：这里用了最基本的算法实现形式，没有考虑死区问题，没有设定上下限，只是对公式的一种直接的实现，后面的介绍当中还会逐渐的对此改进。
   到此为止，PID的基本实现部分就初步完成了。下面是测试代码：
int main(){
    printf("System begin \n");
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