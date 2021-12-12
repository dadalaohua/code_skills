#include <stdio.h>
#include <stdlib.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//http://www.cplusplus.com/reference/cstdlib/qsort/
/*
int compare (const void* p1, const void* p2);

return value    meaning
    <0      The element pointed to by p1 goes before the element pointed to by p2       p1指向的元素在p2指向的元素之前
    0       The element pointed to by p1 is equivalent to the element pointed to by p2  p1指向的元素等同于p2指向的元素
    >0      The element pointed to by p1 goes after the element pointed to by p2        p1指向的元素在p2指向的元素之后
*/

int compare_from_small(const void * a, const void * b)
{
    return ( *(int*)a - *(int*)b );
}

int compare_from_large(const void * a, const void * b)
{
    return ( *(int*)b - *(int*)a );
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
int main(int argc, char* argv[])
{
    int values[] = { 40, 10, 100, 90, 20, 25 };
    int i;
    
    //从小到大排序
    qsort (values, 6, sizeof(int), compare_from_small);
    for (i = 0; i < 6; i++)
        printf("%d ",values[i]);
    printf("\n");
    
    //从大到小排序
    qsort (values, 6, sizeof(int), compare_from_large);
    for (i = 0; i < 6; i++)
        printf("%d ",values[i]);
    printf("\n");
    
    return 0;
}