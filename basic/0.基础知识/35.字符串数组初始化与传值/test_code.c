#include <string.h>  /* strcpy */
#include <stdlib.h>  /* malloc */
#include <stdio.h>   /* printf */

/************************************************************************/
/*                                                                      */
/************************************************************************/
char * test_function_1(char **buf, int num)
{
    int i;
    
    for(i = 0; i < num; i++)
    {
        printf("%d : %s\n", i, buf[i]);
    }
    
    return buf[0];
}

char * test_function_2(char ***buf, int num, int colnum)
{
    int i, j;
    
    for(i = 0; i < num; i++)
    {
        for(j = 0; j < colnum; j++)
        {
            // printf("%d %d : %s\n", i, j, buf[i][j]);         //不能使用
            // printf("%d %d : %s\n", i, j, *(buf[i] + j));     //不能使用
            // printf("%d %d : %s\n", i, j, *(*(buf + i) + j)); //不能使用
            printf("%d %d : %s\n", i, j, *((char **)buf + i * colnum + j));
        }
    }
    
    return *((char **)buf);
}

char * test_function_2_1(char *buf[3][2], int num, int colnum)
{
    int i, j;
    
    for(i = 0; i < num; i++)
    {
        for(j = 0; j < colnum; j++)
        {
            printf("%d %d : %s\n", i, j, buf[i][j]);
            printf("%d %d : %s\n", i, j, *(buf[i] + j));
            printf("%d %d : %s\n", i, j, *(*(buf + i) + j));
            printf("%d %d : %s\n", i, j, *((char **)buf + i * colnum + j));
        }
    }
    
    return *((char **)buf);
}

char * test_function_2_2(char *buf[][2], int num, int colnum)
{
    int i, j;
    
    for(i = 0; i < num; i++)
    {
        for(j = 0; j < colnum; j++)
        {
            printf("%d %d : %s\n", i, j, buf[i][j]);
            printf("%d %d : %s\n", i, j, *(buf[i] + j));
            printf("%d %d : %s\n", i, j, *(*(buf + i) + j));
            printf("%d %d : %s\n", i, j, *((char **)buf + i * colnum + j));
        }
    }
    
    return *((char **)buf);
}

char * test_function_2_3(char * (*buf)[2], int num, int colnum)
{
    int i, j;
    
    for(i = 0; i < num; i++)
    {
        for(j = 0; j < colnum; j++)
        {
            printf("%d %d : %s\n", i, j, buf[i][j]);
            printf("%d %d : %s\n", i, j, *(buf[i] + j));
            printf("%d %d : %s\n", i, j, *(*(buf + i) + j));
            printf("%d %d : %s\n", i, j, *((char **)buf + i * colnum + j));
        }
    }
    
    return *((char **)buf);
}

char * test_function_4(char ****buf, int num, int colnum, int subnum)
{
    int i, j, k;
    
    for(i = 0; i < num; i++)
    {
        for(j = 0; j < colnum; j++)
        {
            for(k = 0; k < subnum; k++)
            {
                printf("%d %d %d : %s\n", i, j, k, *((char **)buf + i * (colnum + subnum) + j * subnum + k));
            }
        }
    }
    
    return *((char **)buf);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    char *buf_1[] = {"London", "New York"};
    char *buf_2[][1] = {
                            {"London"}, 
                            {"New York"}
                       };
    char *buf_3[][2] = {
                            {"London1", "New York1"},
                            {"New York2","Lima2"},
                            {"Lima3","Sao Paulo3"}
                       };
    char *buf_4[][2][2] = {
                            {
                                {"London1", "New York1"},
                                {"London2", "New York2"},
                            },
                            {
                                {"New York3","Lima3"},
                                {"New York4","Lima4"},
                            },
                            {
                                {"Lima5","Sao Paulo5"},
                                {"Lima6","Sao Paulo6"},
                            }
                          };
    
    printf("%s\n", buf_1[0]);
    printf("%s\n", buf_1[1]);
    
    printf("\n");
    
    printf("%s\n", buf_2[0][0]);
    printf("%s\n", buf_2[1][0]);
    
    printf("\n");
    
    printf("%s\n", buf_3[0][0]);
    printf("%s\n", buf_3[0][1]);
    printf("%s\n", buf_3[1][0]);
    printf("%s\n", buf_3[1][1]);
    printf("%s\n", buf_3[2][0]);
    printf("%s\n", buf_3[2][1]);
    
    printf("\n");
    
    printf("%s\n", buf_4[0][0][0]);
    printf("%s\n", buf_4[0][0][1]);
    printf("%s\n", buf_4[0][1][0]);
    printf("%s\n", buf_4[0][1][1]);
    printf("%s\n", buf_4[1][0][0]);
    printf("%s\n", buf_4[1][0][1]);
    printf("%s\n", buf_4[1][1][0]);
    printf("%s\n", buf_4[1][1][1]);
    printf("%s\n", buf_4[2][0][0]);
    printf("%s\n", buf_4[2][0][1]);
    printf("%s\n", buf_4[2][1][0]);
    printf("%s\n", buf_4[2][1][1]);
    
    printf("\n");

    printf("test_function_1\n");
    printf("%s\n", test_function_1(buf_1, sizeof(buf_1)/sizeof(char *)));
    printf("\n");
    
    printf("test_function_2\n");
    printf("%s\n", test_function_2((char * **)buf_2, 2, 1));
    printf("\n");
    
    printf("%s\n", test_function_2((char * **)buf_3, 3, 2));
    printf("\n");
    
    printf("test_function_2_1\n");
    printf("%s\n", test_function_2_1(buf_3, 3, 2));
    printf("\n");
    
    printf("test_function_2_2\n");
    printf("%s\n", test_function_2_2(buf_3, 3, 2));
    printf("\n");
    
    printf("test_function_2_3\n");
    printf("%s\n", test_function_2_3(buf_3, 3, 2));
    printf("\n");
    
    printf("test_function_4\n");
    printf("%s\n", test_function_4((char * ***)buf_4, 3, 2, 2));
    printf("\n");
    

    return 0;
}