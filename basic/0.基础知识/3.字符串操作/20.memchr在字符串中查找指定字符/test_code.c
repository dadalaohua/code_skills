#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{ 
   const char str[] = "hello world!";
   const char ch = 'w';
   char *ret;
 
   ret = (char*)memchr(str, ch, strlen(str));
 
   printf("|%c| 之后的字符串是 - |%s|\n", ch, ret);//|w| 之后的字符串是 - |world!|

   return 0;
}