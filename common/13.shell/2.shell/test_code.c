#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/


/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    char buf1[] = "LIST";
    char buf2[] = "circle . 10";
    char buf3[] = "show99 9";
    char buf4[] = "simp hello 16 2.3 w";
    
    ExternFunc_excute(buf1);
    ExternFunc_excute(buf2);
    ExternFunc_excute(buf3);
    ExternFunc_excute(buf4);
    
    return 0;
}