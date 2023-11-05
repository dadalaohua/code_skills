#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
int base = 0;

/************************************************************************/
/*                                                                      */
/************************************************************************/
struct foo {int a[4];};

struct foo f(int index) {
    struct foo tmp;
    tmp.a[0] = base + 0 + index;
    tmp.a[1] = base + 1 + index;
    tmp.a[2] = base + 2 + index;
    tmp.a[3] = base + 3 + index;
    return tmp;
}

int bar (int index)
{
    return f(index).a[index];
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    bar(1);
    printf("%d %d %d %d\n", bar(0), bar(1), bar(2), bar(3));
    base += 10;
    printf("%d %d %d %d\n", bar(0), bar(1), bar(2), bar(3));
    return 0;
}