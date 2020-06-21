PID控制算法的C语言实现八 变积分的PID控制算法C语言实现
   变积分PID可以看成是积分分离的PID算法的更一般的形式。在普通的PID控制算法中，由于积分系数ki是常数，所以在整个控制过程中，积分增量是不变的。但是，系统对于积分项的要求是，系统偏差大时，积分作用应该减弱甚至是全无，而在偏差小时，则应该加强。积分系数取大了会产生超调，甚至积分饱和，取小了又不能短时间内消除静差。因此，根据系统的偏差大小改变积分速度是有必要的。
   变积分PID的基本思想是设法改变积分项的累加速度，使其与偏差大小相对应：偏差越大，积分越慢; 偏差越小，积分越快。
   这里给积分系数前加上一个比例值index：
   当abs(err)<180时，index=1;
   当180<abs(err)<200时，index=（200-abs(err)）/20;
   当abs(err)>200时，index=0;
   最终的比例环节的比例系数值为ki*index;
   具体PID实现代码如下：
    pid.Kp=0.4;
    pid.Ki=0.2;    //增加了积分系数
    pid.Kd=0.2;
 
   float PID_realize(float speed){
    float index;
    pid.SetSpeed=speed;
    pid.err=pid.SetSpeed-pid.ActualSpeed;

    if(abs(pid.err)>200)                    //变积分过程
    {
    index=0.0;
    }else if(abs(pid.err)<180){
    index=1.0;
    pid.integral+=pid.err;
    }else{
    index=(200-abs(pid.err))/20;
    pid.integral+=pid.err;
    }
    pid.voltage=pid.Kp*pid.err+index*pid.Ki*pid.integral+pid.Kd*(pid.err-pid.err_last);

    pid.err_last=pid.err;
    pid.ActualSpeed=pid.voltage*1.0;
    return pid.ActualSpeed;
}