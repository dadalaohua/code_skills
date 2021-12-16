#include <string.h>  /* strcpy */
#include <stdlib.h>  /* malloc */
#include <stdio.h>   /* printf */

/************************************************************************/
/*                                                                      */
/************************************************************************/
//给int*类型使用
//给int []类型使用
void test_function_1(int *buf, int num)
{
    int i;
    
    for(i = 0; i < num; i++)
    {
        printf("%d : %d\n", i, buf[i]);
    }
}

//给int**类型使用
void test_function_2(int **buf, int num, int colnum)
{
    int i, j;
    
    for(i = 0; i < num; i++)
    {
        for(j = 0; j < colnum; j++)
        {
            printf("%d %d : %d\n", i, j, buf[i][j]);
            printf("%d %d : %d\n", i, j, *(buf[i] + j));
            printf("%d %d : %d\n", i, j, *(*(buf + i) + j));
            //printf("%d %d : %d\n", i, j, *((int *)buf + i * colnum + j));  //不能使用，因为指向int *的地址并不连贯
        }
    }
}

//给int [][1]强制类型转换成int**类型使用
//给int [3][1]强制类型转换成int**类型使用
void test_function_2_0(int **buf, int num, int colnum)
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

//给int [][1]强制类型转换成int*类型使用
void test_function_2_1(int *buf, int num, int colnum)
{
    int i, j;
    
    for(i = 0; i < num; i++)
    {
        for(j = 0; j < colnum; j++)
        {
            printf("%d %d : %d\n", i, j, *((int *)buf + i * colnum + j));
        }
    }
}

//给int [][2]类型使用
//给int [3][2]类型使用
void test_function_2_2(int buf[3][2], int num, int colnum)
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

//给int [][2]类型使用
//给int [3][2]类型使用
void test_function_2_3(int buf[][2], int num, int colnum)
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

//给int [][2]类型使用
//给int [3][2]类型使用
void test_function_2_4(int (*buf)[2], int num, int colnum)
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
    int *intbuf1_p = intbuf1;
    
    int intbuf2_1[][1] = {
                            {11},
                            {23},
                            {45},
                       };
    int *intbuf2_1_p = (int *)intbuf2_1;
    int intbuf2_2[3][1];
    int intbuf3[][2] = {
                            {1, 2},
                            {3, 4}
                       };
    int intbuf3_2[3][2];
    
    int buf1[2] = {0,8};
    int buf2[2] = {1,5};
    int buf3[2] = {2,6};
    int** intbuf4 = malloc(sizeof(int *) * 3);
    *intbuf4 = buf1;
    *(intbuf4 + 1) = buf2;
    *(intbuf4 + 2) = buf3;
    
    printf("int []\n");
    test_function_1(intbuf1, 2);
    printf("\n");
    
    printf("int *\n");
    test_function_1(intbuf1_p, 2);
    printf("\n");
    
    printf("int**\n");
    printf("test_function_2\n");
    test_function_2(intbuf4, 3, 2);
    printf("\n");
    free(intbuf4);
    
    printf("int [][1]\n");
    printf("test_function_2_0\n");
    test_function_2_0((int **)intbuf2_1, 3, 1);
    printf("\n");
    
    printf("test_function_2_1\n");
    test_function_2_1((int *)intbuf2_1, 3, 1);
    printf("\n");
    
    printf("int *\n");
    printf("test_function_2_1\n");
    test_function_2_1(intbuf2_1_p, 3, 1);
    printf("\n");
    
    intbuf2_2[0][0] = 11;
    intbuf2_2[1][0] = 23;
    intbuf2_2[2][0] = 45;
    test_function_2_0((int **)intbuf2_2, 3, 1);
    printf("\n");
    
    test_function_2_0((int **)intbuf3, 2, 2);
    printf("\n");
    
    intbuf3_2[0][0] = 11;
    intbuf3_2[0][1] = 96;
    intbuf3_2[1][0] = 23;
    intbuf3_2[1][1] = 58;
    intbuf3_2[2][0] = 45;
    intbuf3_2[2][1] = 76;
    test_function_2_0((int **)intbuf3_2, 3, 2);
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
    
    printf("test_function_2_4\n");
    test_function_2_4(intbuf3, 2, 2);
    printf("\n");
    
    test_function_2_4(intbuf3_2, 2, 2);
    printf("\n");
    
    return 0;
}