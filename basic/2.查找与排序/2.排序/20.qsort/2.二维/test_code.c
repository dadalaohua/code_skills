#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
int compare_from_small_1(const void * a, const void * b) {
    printf("%d %d\n", *((int *)a), *((int *)a + 1));
    printf("%d %d\n", *((int *)b), *((int *)b + 1));
    
    //printf("%p %p\n", a, b);
    return *((int *)a + 1) - *((int *)b + 1);
}

int compare_from_small_2(const void * a, const void * b) {
    printf("%d %d\n", *((int *)a), *((int *)a + 1));
    printf("%d %d\n", *((int *)b), *((int *)b + 1));
    
    //printf("%p %p\n", a, b);
    return *((int *)a + 1) - *((int *)b + 1);
}

int compare_from_small_3(const void * a, const void * b) {
    int *c = (int *)a;
    int *d = (int *)b;
    printf("%d %d\n", c[0], c[1]);
    printf("%d %d\n", d[0], d[1]);
    return c[1] - d[1];
}

int compare_from_small_4(const void * a, const void * b) {
    int **c = (int **)a;
    int **d = (int **)b;
    printf("%d %d\n", c[0][0], c[0][1]);
    printf("%d %d\n", d[0][0], d[0][1]);
    return c[0][1] - d[0][1];
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int buf[3][2] = {{0,8}, {1,5}, {2,6}};
    
    qsort (buf, 3, 2 * sizeof(int *), compare_from_small_1);
    
    printf("\n");
    for(int i = 0; i < 3; i++){
        printf("%d %d\n", buf[i][0], buf[i][1]);
    }
    
    printf("\n");
    qsort (buf, 3, 2 * sizeof(int (*)[2]), compare_from_small_2);
    
    printf("\n");
    qsort (buf, 3, 2 * sizeof(int (*)[2]), compare_from_small_3);
    
    int buf1[2] = {0,8};
    int buf2[2] = {1,5};
    int buf3[2] = {2,6};
    int** courses = malloc(sizeof(int *) * 3);
    *courses = buf1;
    *(courses + 1) = buf2;
    *(courses + 2) = buf3;
    
    printf("\n");
    qsort (courses, 3, sizeof(int **), compare_from_small_4);
    
    printf("\n");
    for(int i = 0; i < 3; i++){
        printf("%d %d\n", courses[i][0], courses[i][1]);
    }
    free(courses);
    
    return 0;
}