检测有多少个bit被置位

3．  二进制中1的个数

统计二进制中1的个数可以直接移位再判断，当然像《编程之美》书中用循环移位计数或先打一个表再计算都可以。本文详细讲解一种高效的方法。以34520为例，可以通过下面四步来计算其二进制中1的个数二进制中1的个数。

第一步：每2位为一组，组内高低位相加

      10 00 01 10  11 01 10 00

  -->01 00 01 01  10 01 01 00

第二步：每4位为一组，组内高低位相加

      0100 0101 1001 0100

  -->0001 0010 0011 0001

第三步：每8位为一组，组内高低位相加

      00010010 00110001

  -->00000011 00000100

第四步：每16位为一组，组内高低位相加

      00000011 00000100

  -->00000000 00000111

这样最后得到的00000000 00000111即7即34520二进制中1的个数。类似上文中对二进制逆序的做法不难实现第一步的代码：

       x = ((x & 0xAAAA) >> 1) + (x & 0x5555);

好的，有了第一步，后面几步就请读者完成下吧，先动动笔再看下面的完整代码：
[cpp] view plaincopy

    //二进制中1的个数  by MoreWindows( http://blog.csdn.net/MoreWindows )   
    #include <stdio.h>  
    template <class T>  
    void PrintfBinary(T a)  
    {  
        int i;  
        for (i = sizeof(a) * 8 - 1; i >= 0; --i)  
        {  
            if ((a >> i) & 1)  
                putchar('1');  
            else   
                putchar('0');  
            if (i == 8)  
                putchar(' ');  
        }  
        putchar('\n');  
    }  
    int main()  
    {  
        printf("二进制中1的个数 --- by MoreWindows( http://blog.csdn.net/MoreWindows )  ---\n\n");  
          
        unsigned short a = 34520;  
        printf("原数    %6d的二进制为:  ", a);  
        PrintfBinary(a);  
          
        a = ((a & 0xAAAA) >> 1) + (a & 0x5555);  
        a = ((a & 0xCCCC) >> 2) + (a & 0x3333);  
        a = ((a & 0xF0F0) >> 4) + (a & 0x0F0F);  
        a = ((a & 0xFF00) >> 8) + (a & 0x00FF);     
        printf("计算结果%6d的二进制为:  ", a);     
        PrintfBinary(a);  
        return 0;  
    }   