#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    printf(ANSI_COLOR_RED     "This text is RED!"     ANSI_COLOR_RESET "\r\n");
    printf(ANSI_COLOR_GREEN   "This text is GREEN!"   ANSI_COLOR_RESET "\r\n");
    printf(ANSI_COLOR_YELLOW  "This text is YELLOW!"  ANSI_COLOR_RESET "\r\n");
    printf(ANSI_COLOR_BLUE    "This text is BLUE!"    ANSI_COLOR_RESET "\r\n");
    printf(ANSI_COLOR_MAGENTA "This text is MAGENTA!" ANSI_COLOR_RESET "\r\n");
    printf(ANSI_COLOR_CYAN    "This text is CYAN!"    ANSI_COLOR_RESET "\r\n");
    
    printf("\r\n");
    
    int i;
    
    for(i = 0; i < 256; i++){
        if(i % 16 == 0)
            printf("\r\n");
        
        printf("\x1b[48;5;%dm %03d \x1b[0m", i, i);
    }
    
    printf("\r\n");
        
    return 0;
}