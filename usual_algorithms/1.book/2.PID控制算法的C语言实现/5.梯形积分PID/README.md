PID控制算法的C语言实现七 梯形积分的PID控制算法C语言实现
   先看一下梯形算法的积分环节公式

   作为PID控制律的积分项，其作用是消除余差，为了尽量减小余差，应提高积分项运算精度，为此可以将矩形积分改为梯形积分，具体实现的语句为：
pid.voltage=pid.Kp*pid.err+index*pid.Ki*pid.integral/2+pid.Kd*(pid.err-pid.err_last);  //梯形积分
其它函数请参见本系列教程六中的介绍