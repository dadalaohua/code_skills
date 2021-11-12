#include <stdio.h>
#include <stdlib.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
void getenv_test(void)
{
    char* path = NULL;
    if((path = getenv("TEST_ENV")))
        printf("TEST_ENV=%s\n", path);
    
    //printf("TEST_ENV=%s\n", path);
}

void putenv_test(void)
{
    putenv("TEST_ENV=helloworld");
}

void setenv_test(int overwrite)
{
    setenv("TEST_ENV", "123456", overwrite);
}

void unsetenv_test(void)
{
    unsetenv("TEST_ENV");
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
int main(int argc, char* argv[])
{
    getenv_test();
    
    putenv_test();
    getenv_test();
    
    setenv_test(0);
    getenv_test();
    
    setenv_test(1);
    getenv_test();
    
    unsetenv_test();
    getenv_test();
    
    return 0;
}