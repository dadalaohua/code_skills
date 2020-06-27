#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{ 
    char str[50];

    strcpy(str,"This is string.h library function");
    puts(str);  //This is string.h library function

    memset(str,'$',7);
    puts(str);  //$$$$$$$ string.h library function
   
    return 0;
}