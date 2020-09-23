#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//编译时打印#pragma message：Compiling test_code.c...
#pragma message "Compiling " __FILE__ "..."

#define DO_PRAGMA(x) _Pragma (#x)
#define TODO(x) DO_PRAGMA(message ("TODO - " #x))

/************************************************************************/
/*                                                                      */
/************************************************************************/
int main(int argc, char* argv[])
{
    //编译时打印#pragma message：TODO - Remember to fix this
    TODO(Remember to fix this)
    printf("hello world\n");
    
    return 0;
}