#include <stdio.h>
#include <unistd.h>
#include <getopt.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
void use_getpot_long(int argc, char *argv[])
{
    const char *optstring = "vn:h";
    int c;
    struct option opts[] = {
        {"version", 0, NULL, 'v'},
        {"name", 1, NULL, 'n'},
        {"help", 0, NULL, 'h'}
    };

    while((c = getopt_long(argc, argv, optstring, opts, NULL)) != -1)
    {
        switch(c) {
            case 'n':
                printf("username is %s\n", optarg);
                break;
            case 'v':
                printf("version is 0.0.1\n");
                break;
            case 'h':
                printf("this is help\n");
                break;
            case '?':
                printf("unknown option\n");
                break;
            case 0 :
                printf("the return val is 0\n");
                break;
            default:
                printf("------\n");

        }
    }
}

void use_getpot_long2(int argc, char *argv[])
{
    const char *optstring = "vn:h";
    int c;

    int f_v = -1, f_n = -1, f_h = -1, opt_index = -1; 
    struct option opts[] = {
        {"version", 0, &f_v, 'v'},
        {"name", 1, &f_n, 'n'},
        {"help", 0, &f_h, 'h'}
    };

    while((c = getopt_long(argc, argv, optstring, opts, &opt_index)) != -1)
    {
        switch(c) {
            case 'n':
                printf("username is %s\n", optarg);
                break;
            case 'v':
                printf("version is 0.0.1\n");
                break;
            case 'h':
                printf("this is help\n");
                break;
            case '?':
                printf("unknown option\n");
                break;
            case 0 :
                printf("f_v is %d \n", f_v);
                printf("f_n is %d \n", f_n);
                printf("f_h is %d \n", f_h);
                break;
            default:
                printf("------\n");
        }
        printf("opt_index is %d\n\n", opt_index);
    }
}

void use_getpot_long3(int argc, char *argv[])
{
    const char *optstring = "vn:h";
    int c;
    struct option opts[] = {
        {"version", 0, NULL, 'v'},
        {"name", 1, NULL, 'n'},
        {"help", 0, NULL, 'h'}
    };

    while((c = getopt_long_only(argc, argv, optstring, opts, NULL)) != -1)
    {
        switch(c) {
            case 'n':
                printf("username is %s\n", optarg);
                break;
            case 'v':
                printf("version is 0.0.1\n");
                break;
            case 'h':
                printf("this is help\n");
                break;
            case '?':
                printf("unknown option\n");
                break;
            case 0 :
                printf("the return val is 0\n");
                break;
            default:
                printf("------\n");

        }
    }
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    use_getpot_long(argc, argv);
    
    return 0;
}