#include <stdio.h>
#include <string.h>
#include <stdarg.h> 

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define debug(...)                  printf(__VA_ARGS__)

#define debug2(format, ...)         fprintf(stdout, format, __VA_ARGS__)
#define debug3(format, args...)     fprintf(stdout, format, args)
#define debug4(format, ...)         fprintf(stdout, format, ##__VA_ARGS__)

#define debug5(format, ...)         printf(format, __VA_ARGS__)
#define debug6(format, args...)     printf(format, args)
#define debug7(format, ...)         printf(format, ##__VA_ARGS__)

#define dbgprint(format, args...)   printf(format, ##args)

#define LOG_DBG(format, args...)    printf("LOG_DBG:"format, ##args)

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{ 
    debug("test 1\n");
    debug("test 2 %d\n", 3);
    debug("test 3 %d %d\n", 4, 5);
    
    //debug2("test 1\n");       //必须带参数
    debug2("test 2 %d\n", 3);
    debug2("test 3 %d %d\n", 4, 5);
    
    //debug3("test 1\n");       //必须带参数
    debug3("test 2 %d\n", 3);
    debug3("test 3 %d %d\n", 4, 5);
    
    debug4("test 1\n");
    debug4("test 2 %d\n", 3);
    debug4("test 3 %d %d\n", 4, 5);
    
    //debug5("test 1\n");       //必须带参数
    debug5("test 2 %d\n", 3);
    debug5("test 3 %d %d\n", 4, 5);
    
    //debug6("test 1\n");       //必须带参数
    debug6("test 2 %d\n", 3);
    debug6("test 3 %d %d\n", 4, 5);
    
    debug7("test 1\n");
    debug7("test 2 %d\n", 3);
    debug7("test 3 %d %d\n", 4, 5);
    
    dbgprint("test 1\n");
    dbgprint("test 2 %d\n", 3);
    dbgprint("test 3 %d %d\n", 4, 5);
    
    LOG_DBG("test 1\n");
    LOG_DBG("test 2 %d\n", 3);
    LOG_DBG("test 3 %d %d\n", 4, 5);
    
    return 0;
}