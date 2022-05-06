#include <stdio.h>
#include <stdarg.h> 

/************************************************************************/
/*                                                                      */
/************************************************************************/
void write_log(FILE *stream, char *format, ...)
{
    va_list args;

    va_start(args, format);
    vfprintf(stream, format, args);
    va_end(args);
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    FILE *fp;

    fp = fopen("test.log", "w+");
    
    write_log(fp, "Hello %s %d \n", "world", 123456);
    
    fclose(fp);
    
    return 0;
}