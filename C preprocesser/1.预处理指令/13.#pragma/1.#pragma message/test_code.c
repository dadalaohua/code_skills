#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/

/************************************************************************/
//不中断编译的情况下，发送一个字符串文字量到标准输出
#if defined(ANDROID20)
    #pragma message("Complie Android SDK 2.0...")
    #define VERSION "Android 2.0"
#elif defined(ANDROID23)
    #pragma message("Complie Android SDK 2.3...")
    #define VERSION "Android 2.3"
#elif defined(ANDROID40)
    #pragma message("Complie Android SDK 4.0...")
    #define VERSION "Android 4.0"
#else
    #error Compile Version is not provided!
#endif

/************************************************************************/
//messagestring 参数可以是扩展到字符串的宏
#pragma message( "Compiling " __FILE__ )                //编译时,显示被编译的文件
#pragma message( "Last modified on " __TIMESTAMP__ )    //编译时,显示文件最后一次修改的日期和时间


/************************************************************************/
//如果在 message 杂注中使用预定义的宏，则该宏应返回字符串，否则必须将该宏的输出转换为字符串
#define STRING2(x) #x  
#define STRING(x) STRING2(x)  
  
#pragma message (__FILE__ "[" STRING(__LINE__) "]: test")   //注意把行号转成了字符串

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    //gcc test_code.c -DANDROID40 输出 附注： #pragma message：Complie Android SDK 4.0...
    printf("%s\n", VERSION);
    
    return 0;
}