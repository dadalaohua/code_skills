#include <stdio.h>

int main(int argc, char* argv[])
{
    while(1)
    {
        fprintf(stdout,"一号打印");
        fprintf(stderr,"二号输出");

        sleep(2);
    }

    return 0;
}