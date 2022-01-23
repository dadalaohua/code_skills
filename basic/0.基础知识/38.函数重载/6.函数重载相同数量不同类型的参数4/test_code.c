#include <stdio.h>
#include <stdarg.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
注意，该方法传递的参数不能是char、short或者float类型

va_arg宏的第2个参数不能被指定为char、short或者float类型。
因为char和short类型的参数会被转换为int类型，而float类型的参数会被转换为double类型

type不能为以下类型：
——char、signed char、unsigned char
——short、unsigned short
——signed short、short int、signed short int、unsigned short int
——float

会默认参数提升
提升工作如下：
——float类型的实际参数将提升到double
——char、short和相应的signed、unsigned类型的实际参数提升到int
——如果int不能存储原值，则提升到unsigned int
*/

void test1(int a)
{
    printf("test1 %d\n", a);
}

void test2(double a)
{
    printf("test2 %f\n", a);
}

void __test(int typeval, ...) {
    switch(typeval)
    {
        case 1:
        {
            va_list ap;
            va_start(ap, typeval);
            
            int a = va_arg(ap, int);
            
            va_end(ap);
            
            test1(a);
        }
        break;
        
        case 2:
        {
            va_list ap;
            va_start(ap, typeval);
            
            double a = va_arg(ap, double);
            
            va_end(ap);
            
            test2(a);
        }
        break;
 
        default:
            printf("Invalid type\n");
    }
}

#define test(a) __test(__builtin_types_compatible_p(typeof(a), int) * 1 \
                        + __builtin_types_compatible_p(typeof(a), double) * 2    \
                        , a)
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int a;
    double x;
    
    a = 10;
    test(a);
    
    x = 112.34;
    test(x);
    
    return 0;
}