#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{ 
    char ch = 'A';
    char str[20] = "hello world";
    float flt = 10.235;
    int no = 150;
    double dbl = 20.123456;
    long sum = 655888;
    unsigned int num = 51654;
    float fl = 12;
    
    printf("字符为 %c \n", ch);         //字符为 A 
    printf("字符串为 %s \n" , str);     //字符串为 hello world 
    printf("浮点数为 %f \n", flt);      //浮点数为 10.235000 //对于单精度数，使用%f格式符输出时，仅前7位是有效数字，小数6位．
    printf("整数为 %d\n" , no);         //数为 150
    printf("双精度值为 %lf \n", dbl);   //双精度值为 20.123456 //对于双精度数，使用%lf格式符输出时，前16位是有效数字，小数6位．
    printf("八进制值为 %o \n", no);     //进制值为 226 
    printf("十六进制值为 %x \n", no);   //十六进制值为 96
    printf("短整型值为 %hd \n", no);    //短整型值为 150 
    printf("长整型值为 %ld \n", sum);   //长整型值为 655888
    printf("无符号整型值为 %u \n", num);//无符号整型值为 51654 
    printf("指针地址值为 %p \n", str);  //指针地址值为 0xbfdb8118 
    printf("以指数形式输出实数 %e \n", flt);      //以指数形式输出实数 1.023500e+01
    printf("自动选f格式或e格式 %g \n", flt);      //10.235 //自动选f格式或e格式中较短的一种输出，且不输出无意义的零
    printf("以指数形式输出实数 %E \n", flt);      //同%e
    printf("自动选f格式或e格式 %G \n", flt);      //同%g
    printf("整数为 %i\n" , no);         //同%i
    printf("十六进制值为 %X \n", no);   //同%x
    printf("%% \n");   //%
    printf("转义字符 \\ \\n \\r \\t \n");   //转义字符 \ \n \r \t 
    
    //用十进制正整数表示设置输出值得最少字符个数。不足则补空格，多出则按实际输出，默认按实际输出
    printf("%8d\n" , no);           //     150
    printf("%4d\n" , no);           // 150
    printf("%2d\n" , no);           //150
    
    //用“小数点”加“十进制正整数”表示
    //对“整数”，表示至少要输出的数字个数，不足补数字0，多则原样输出
    printf("%0.8d\n" , no);         //00000150
    printf("%0.6d\n" , no);         // 150
    printf("%0.2d\n" , no);         //150
    
    //对“实数”，表示小数点后至多输出的数字个数，不足则补数字0，多则做舍入处理
    printf("%0.8f\n", flt);          //10.23499966//用gcc验证表现不同
    printf("%0.6f\n", flt);          //10.235000
    printf("%0.2f\n", flt);          //10.23
    
    printf("%.8f\n", flt);          //10.23499966//用gcc验证表现不同
    printf("%.6f\n", flt);          //10.235000
    printf("%.2f\n", flt);          //10.23
    
    //对“字符串”，表示最多输出的字符个数，不足补空格，多则丢弃
    printf("%0.16s\n", str);         //hello world
    printf("%0.8s\n", str);          //hello wo
    printf("%0.2s\n", str);          //he
    
    printf("%10.8s\n", str);         //  hello wo
    printf("%*.*s\n", 10, 8, str);   //  hello wo
    printf("%*.8s\n", 10, str);      //  hello wo
    printf("%10.*s\n", 8, str);      //  hello wo
    
    // -   ——左对齐输出，默认为右对齐输出
    printf("%-8d\n" , no);           //150     
    printf("%8d\n" , no);            //     150
    
    // +   ——正数输出加号(+)，负数输出减号(-)
    printf("%+d\n" , no);            //+150    
    printf("%+d\n" , -no);           //-150
    
    //空格 ——正数输出空格代替加号(+)，负数输出减号(-)
    printf("% d\n" , no);            // 150   
    printf("% d\n" , -no);           //-150
    
    //#  ——对c,s,d,u类无影响；对o类，在输出时加前缀o；对x类，在输出时加前缀0x；
    //     对e,g,f 类会强制输出包含一个小数点，即使后边没有数字时也会显示小数点
    printf("%#o \n", no);            //0226
    printf("%#x \n", no);            //0x96
    printf("%#e \n", fl);            //1.200000e+01
    printf("%#g \n", fl);            //12.0000
    printf("%#f \n", fl);            //12.000000 
    printf("%#e \n", flt);           //1.023500e+01 
    printf("%#g \n", flt);           //10.2350 
    printf("%#f \n", flt);           //10.235000 
   
    return 0;
}