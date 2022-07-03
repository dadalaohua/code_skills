#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
int add(int num1,int num2) {
  int a = num1 ^ num2;
  int b = num1 & num2;
  b = b << 1;
  
  return b == 0 ? a : add(a, b); 
}

// int add(int num1,int num2) {
    // return (((num1 & num2) << 1) == 0) ? (num1 ^ num2) : add(num1 ^ num2, (num1 & num2) << 1); 
// }
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int num1, num2;
    
    num1 = 100, num2 = 66;
    printf("%d + %d = %d\n", num1, num2, add(num1, num2));
    
    num1 = 100, num2 = -66;
    printf("%d + %d = %d\n", num1, num2, add(num1, num2));
    num1 = -100, num2 = -66;
    
    printf("%d + %d = %d\n", num1, num2, add(num1, num2));
    
    num1 = 0, num2 = -66;
    printf("%d + %d = %d\n", num1, num2, add(num1, num2));
    
    return 0;
}