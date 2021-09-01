#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>
#include <signal.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
void dump(int signo)
{
    void *buffer[30] = {0};
    size_t size;
    char **strings = NULL;
    size_t i = 0;

    size = backtrace(buffer, 30);
    fprintf(stdout, "Obtained %zd stack frames.nm\n", size);

    strings = backtrace_symbols(buffer, size);
    if (strings == NULL)
    {
        perror("backtrace_symbols.");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < size; i++)
    {
        fprintf(stdout, "%s\n", strings[i]);
    }

    free(strings);
    strings = NULL;

    //exit(0);
}

void test_function_d(void)
{
    raise(SIGUSR1);
}

void test_function_c(void)
{
    raise(SIGUSR1);
}

void test_function_b(void)
{
    test_function_c();
}

void test_function_a(void)
{
    test_function_b();
    test_function_d();
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    if (signal(SIGUSR1, dump) == SIG_ERR)
        perror("can't catch SIGUSR1");
   
    test_function_a();
    
    return 0;
}