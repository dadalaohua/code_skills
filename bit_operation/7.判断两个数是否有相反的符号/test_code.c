#include <stdio.h>
#include <stdbool.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
bool opposite_signs(int x, int y)
{
    return ((x ^ y) < 0);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    printf("%d and %d %s opposite signs\n", 5, -100, opposite_signs(5, -100) ? "have" : "haven't");
    
    printf("%d and %d %s opposite signs\n", 546, 34600, opposite_signs(546, 34600) ? "have" : "haven't");
    
    return 0;
}