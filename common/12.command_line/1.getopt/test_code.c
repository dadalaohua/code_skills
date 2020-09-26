#include <stdio.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/


/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int ch;
    
    while((ch = getopt(argc, argv, "a:b")) != -1) {
        switch(ch) {
            case 'a':
                printf("option a: %s\n", optarg);
                break;
            case 'b':
                printf("option b \n");
                break;
            case '?': // 输入未定义的选项, 都会将该选项的值变为 ?
                printf("unknown option \n");
                break;
            default:
                printf("default \n");
        }
    }
    
    return 0;
}