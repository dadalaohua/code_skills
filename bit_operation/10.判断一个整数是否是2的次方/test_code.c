#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef enum bool{false, true} bool;

/************************************************************************/
/*                                                                      */
/************************************************************************/
//判断一个整数是否是2的次方 
bool integer_is_a_power_of_2(unsigned int val)
{
    return (val & (val - 1)) == 0;
}

//请注意，这里错误地认为0是2的幂。
//要解决此问题，请使用： 
bool integer_is_a_power_of_2_better(unsigned int val)
{
    return val && !(val & (val - 1));
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int val1 = 512;
    int val2 = 357;
    
    printf("%d %s a power of 2\n", val1, integer_is_a_power_of_2(val1) ? "is" : "isn't");
    printf("%d %s a power of 2\n", val2, integer_is_a_power_of_2(val2) ? "is" : "isn't");
    
    printf("%d %s a power of 2\n", val1, integer_is_a_power_of_2_better(val1) ? "is" : "isn't");
    printf("%d %s a power of 2\n", val2, integer_is_a_power_of_2_better(val2) ? "is" : "isn't");
    
    printf("%d %s a power of 2\n", 0, integer_is_a_power_of_2(0) ? "is" : "isn't");
    printf("%d %s a power of 2\n", 0, integer_is_a_power_of_2_better(0) ? "is" : "isn't");
    
    return 0;
}