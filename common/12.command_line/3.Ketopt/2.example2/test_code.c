#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
#include "ketopt.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
//Example 2: subcommand
//示例:子命令testsub
//./test_code -x testsub -x
//./test_code testsub -x
int main(int argc, char* argv[])
{
    ketopt_t om = KETOPT_INIT, os = KETOPT_INIT;
    int i, c;
    while ((c = ketopt(&om, argc, argv, 0, "x", 0)) >= 0)
        if (c == 'x') printf("main -x\n");
    if (om.ind == argc) {
        fprintf(stderr, "missing subcommand\n");
        return 1;
    }
    printf("subcommand: %s\n", argv[om.ind]);
    while ((c = ketopt(&os, argc - om.ind, argv + om.ind, 1, "x", 0)) >= 0)
        if (c == 'x') printf("sub -x\n");
    printf("Non-option arguments:");
    for (i = os.ind + om.ind; i < argc; ++i)
        printf(" %s", argv[i]);
    putchar('\n');
    return 0;
}