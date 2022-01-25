#include <stdio.h>
#include <complex.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
void char_printf(char val) {
    printf("type char, var:%d\n", val);
}

void signed_char_printf(signed char val) {
    printf("type signed char, var:%d\n", val);
}

void signed_short_printf(signed short val) {
    printf("type signed short, var:%hd\n", val);
}

void signed_int_printf(signed int val) {
    printf("type signed int, var:%d\n", val);
}

void signed_long_int_printf(signed long int val) {
    printf("type signed long int, var:%ld\n", val);
}

void signed_long_long_int_printf(signed long long int val) {
    printf("type signed long long int, var:%lld\n", val);
}

void unsigned_char_printf(unsigned char val) {
    printf("type unsigned char, var:%d\n", val);
}

void unsigned_short_printf(unsigned short val) {
    printf("type unsigned short, var:%hu\n", val);
}

void unsigned_int_printf(unsigned int val) {
    printf("type unsigned int, var:%u\n", val);
}

void unsigned_long_int_printf(unsigned long int val) {
    printf("type unsigned long int, var:%lu\n", val);
}

void unsigned_long_long_int_printf(unsigned long long int val) {
    printf("type unsigned long long int, var:%llu\n", val);
}

void float_printf(float val) {
    printf("type float, var:%f\n", val);
}

void double_printf(double val) {
    printf("type double, var:%lf\n", val);
}

void long_double_printf(long double val) {
    printf("type long double, var:%Lf\n", val);
}

void _Bool_printf(_Bool val) {
    printf("type _Bool, var:%d\n", val);
}

void float_Complex_printf(float _Complex val) {
    printf("type float _Complex, var:%f+%fi\n", crealf(val), cimagf(val));
}

void double_Complex_printf(double _Complex val) {
    printf("type double _Complex, var:%f+%fi\n", creal(val), cimag(val));
}

void long_double_Complex_printf(long double _Complex val) {
    printf("type long double _Complex, var:%Lf+%Lfi\n", creall(val), cimagl(val));
}

void default_printf(void) {
    printf("type default!\n");
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
#define CUSTOM_GENERIC(_var_) _Generic((_var_), \
/*char*/                        char : char_printf(_var_), \
/*signed char*/                 signed char : signed_char_printf(_var_), \
/*signed short*/                signed short : signed_short_printf(_var_), \
/*signed int*/                  signed int : signed_int_printf(_var_), \
/*signed long int */            signed long int : signed_long_int_printf(_var_), \
/*signed long long int*/        signed long long int : signed_long_long_int_printf(_var_), \
/*unsigned char*/               unsigned char : unsigned_char_printf(_var_), \
/*unsigned short*/              unsigned short : unsigned_short_printf(_var_), \
/*unsigned int*/                unsigned int : unsigned_int_printf(_var_), \
/*unsigned long int*/           unsigned long int : unsigned_long_int_printf(_var_), \
/*unsigned long long int*/      unsigned long long int : unsigned_long_long_int_printf(_var_), \
/*float*/                       float : float_printf(_var_), \
/*double*/                      double : double_printf(_var_), \
/*long double*/                 long double : long_double_printf(_var_),  \
/*_Bool*/                       _Bool : _Bool_printf(_var_),  \
/*float _Complex*/              float _Complex : float_Complex_printf(_var_),  \
/*double _Complex*/             double _Complex : double_Complex_printf(_var_),  \
/*long double _Complex*/        long double _Complex : long_double_Complex_printf(_var_),  \
/*default*/                     default : default_printf() \
)
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    char a = 10;
    signed char a1 = 10;
    unsigned char a2 = 10;
    short b = 2000;
    int c = 12345;
    float f = 123.45f;
    float _Complex fCex = 100.0f + 1.0if;
    // float complex fCex = 100.0f + 1.0if; //如果包含头文件#include <complex.h>可以使用该方式

    //注意char != signed char，ANSI C 提供了3种字符类型，分别是char、signed char、unsigned char
    CUSTOM_GENERIC(a);              //type char, var:10
    CUSTOM_GENERIC(a1);             //type signed char, var:10
    CUSTOM_GENERIC(a2);             //type unsigned char, var:10
    
    CUSTOM_GENERIC(b);              //type signed short, var:2000
    CUSTOM_GENERIC(c);              //type signed int, var:12345
    CUSTOM_GENERIC(f);              //type float, var:1123.449997
    CUSTOM_GENERIC(fCex);           //type float _Complex, var:100.000000+1.000000i
    CUSTOM_GENERIC(66);             //type signed int, var:66
    return 0;
}