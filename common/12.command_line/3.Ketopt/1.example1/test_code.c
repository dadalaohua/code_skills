#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
#include "ketopt.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
//Example 1: accept option -x, -y arg, --foo, --bar=arg and --opt[=arg].
//示例：
// ./test_code -x -y test_arg --foo --bar=testarg --opt=test
int main(int argc, char* argv[])
{
    static ko_longopt_t longopts[] = {
        { "foo", ko_no_argument,       301 },
        { "bar", ko_required_argument, 302 },
        { "opt", ko_optional_argument, 303 },
        { NULL, 0, 0 }
    };
    ketopt_t opt = KETOPT_INIT;
    int i, c;
    while ((c = ketopt(&opt, argc, argv, 1, "xy:", longopts)) >= 0) {
        if (c == 'x') printf("-x\n");
        else if (c == 'y') printf("-y %s\n", opt.arg);
        else if (c == 301) printf("--foo\n");
        else if (c == 302) printf("--bar %s\n", opt.arg? opt.arg : "(null)");
        else if (c == 303) printf("--opt %s\n", opt.arg? opt.arg : "(null)");
        else if (c == '?') printf("unknown opt: -%c\n", opt.opt? opt.opt : ':');
        else if (c == ':') printf("missing arg: -%c\n", opt.opt? opt.opt : ':');
    }
    printf("Non-option arguments:");
    for (i = opt.ind; i < argc; ++i)
        printf(" %s", argv[i]);
    putchar('\n');
    return 0;
}