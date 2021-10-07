#include <string.h>  /* strcpy */
#include <stdlib.h>  /* malloc */
#include <stdio.h>   /* printf */

/************************************************************************/
/*                                                                      */
/************************************************************************/
void test_function_1(int *buf, int num)
{
    int i;
    
    for(i = 0; i < num; i++)
    {
        printf("%d : %d\n", i, buf[i]);
    }
}

void test_function_2(int **buf, int num, int colnum)
{
    int i, j;
    
    for(i = 0; i < num; i++)
    {
        for(j = 0; j < colnum; j++)
        {
            //printf("%d %d : %d\n", i, j, buf[i][j]);          //不能使用
            //printf("%d %d : %d\n", i, j, *(buf[i] + j));      //不能使用
            //printf("%d %d : %d\n", i, j, *(*(buf + i) + j));  //不能使用
            printf("%d %d : %d\n", i, j, *((int *)buf + i * colnum + j));
        }
    }
}

void test_function_2_1(int buf[3][2], int num, int colnum)
{
    int i, j;
    
    for(i = 0; i < num; i++)
    {
        for(j = 0; j < colnum; j++)
        {
            printf("%d %d : %d\n", i, j, buf[i][j]);
            printf("%d %d : %d\n", i, j, *(buf[i] + j));
            printf("%d %d : %d\n", i, j, *(*(buf + i) + j));
            printf("%d %d : %d\n", i, j, *((int *)buf + i * colnum + j));
        }
    }
}

void test_function_2_2(int buf[][2], int num, int colnum)
{
    int i, j;
    
    for(i = 0; i < num; i++)
    {
        for(j = 0; j < colnum; j++)
        {
            printf("%d %d : %d\n", i, j, buf[i][j]);
            printf("%d %d : %d\n", i, j, *(buf[i] + j));
            printf("%d %d : %d\n", i, j, *(*(buf + i) + j));
            printf("%d %d : %d\n", i, j, *((int *)buf + i * colnum + j));
        }
    }
}

void test_function_2_3(int (*buf)[2], int num, int colnum)
{
    int i, j;
    
    for(i = 0; i < num; i++)
    {
        for(j = 0; j < colnum; j++)
        {
            printf("%d %d : %d\n", i, j, buf[i][j]);
            printf("%d %d : %d\n", i, j, *(buf[i] + j));
            printf("%d %d : %d\n", i, j, *(*(buf + i) + j));
            printf("%d %d : %d\n", i, j, *((int *)buf + i * colnum + j));
        }
    }
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int intbuf1[] = {1, 2};
    int intbuf2_1[][1] = {
                            {11},
                            {23},
                            {45},
                       };
    int intbuf2_2[3][1];
    int intbuf3[][2] = {
                            {1, 2},
                            {3, 4}
                       };
    int intbuf3_2[3][2];
    
    test_function_1(intbuf1, 2);
    printf("\n");
    
    test_function_2((int **)intbuf2_1, 3, 1);
    printf("\n");
    
    intbuf2_2[0][0] = 11;
    intbuf2_2[1][0] = 23;
    intbuf2_2[2][0] = 45;
    test_function_2((int **)intbuf2_2, 3, 1);
    printf("\n");
    
    test_function_2((int **)intbuf3, 2, 2);
    printf("\n");
    
    intbuf3_2[0][0] = 11;
    intbuf3_2[0][1] = 96;
    intbuf3_2[1][0] = 23;
    intbuf3_2[1][1] = 58;
    intbuf3_2[2][0] = 45;
    intbuf3_2[2][1] = 76;
    test_function_2((int **)intbuf3_2, 3, 2);
    printf("\n");
    
    printf("test_function_2_1\n");
    test_function_2_1(intbuf3, 2, 2);
    printf("\n");
    
    test_function_2_1(intbuf3_2, 2, 2);
    printf("\n");
    
    printf("test_function_2_2\n");
    test_function_2_2(intbuf3, 2, 2);
    printf("\n");
    
    test_function_2_2(intbuf3_2, 2, 2);
    printf("\n");
    
    printf("test_function_2_3\n");
    test_function_2_3(intbuf3, 2, 2);
    printf("\n");
    
    test_function_2_3(intbuf3_2, 2, 2);
    printf("\n");
    
    return 0;
}