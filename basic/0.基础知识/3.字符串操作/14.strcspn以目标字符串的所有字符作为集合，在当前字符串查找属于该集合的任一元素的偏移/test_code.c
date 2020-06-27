#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{ 
   int len;
   const char str1[] = "ABCDEF4960910";
   const char str2[] = "013";

   len = strcspn(str1, str2);

   printf("第一个匹配的字符是在 %d\n", len + 1);//第一个匹配的字符是在 10
    
    return 0;
}