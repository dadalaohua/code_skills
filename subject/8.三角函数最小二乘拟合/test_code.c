#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define Pi 3.14159265358979324

/*三角函数参数类*/
typedef struct {
    double A;           //系数A
    double B;           //系数B
    double C;           //系数C
    double omiga;       //角频率
    double error_value; //目标函数值
} trigonometric_function_paramater;

#define N 3
int Gauss(double A[][N], double B[][N], int n)//这里的n指的是n*n的方阵中的n
{
    int i, j, k;
    float max, temp;
    float t[N][N];                  //临时矩阵
                                    //将A矩阵存放在临时矩阵t[n][n]中
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            t[i][j] = A[i][j];
        }
    }
    //初始化B矩阵为单位阵
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            B[i][j] = (i == j) ? (float)1 : 0;
        }
    }
    for (i = 0; i < n; i++)
    {
        //寻找主元
        max = t[i][i];
        k = i;
        for (j = i + 1; j < n; j++)
        {
            if (fabs(t[j][i]) > fabs(max))
            {
                max = t[j][i];
                k = j;
            }
        }
        //如果主元所在行不是第i行，进行行交换
        if (k != i)
        {
            for (j = 0; j < n; j++)
            {
                temp = t[i][j];
                t[i][j] = t[k][j];
                t[k][j] = temp;
                //B伴随交换
                temp = B[i][j];
                B[i][j] = B[k][j];
                B[k][j] = temp;
            }
        }
        //判断主元是否为0, 若是, 则矩阵A不是满秩矩阵,不存在逆矩阵
        if (t[i][i] == 0)
        {
            printf("There is no inverse matrix!\n");
            return -1;
        }
        //消去A的第i列除去i行以外的各行元素
        temp = t[i][i];
        for (j = 0; j < n; j++)
        {
            t[i][j] = t[i][j] / temp;        //主对角线上的元素变为1
            B[i][j] = B[i][j] / temp;        //伴随计算
        }
        for (j = 0; j < n; j++)        //第0行->第n行
        {
            if (j != i)                //不是第i行
            {
                temp = t[j][i];
                for (k = 0; k < n; k++)        //第j行元素 - i行元素*j列i行元素
                {
                    t[j][k] = t[j][k] - t[i][k] * temp;
                    B[j][k] = B[j][k] - B[i][k] * temp;
                }
            }
        }
    }
    
    return 0;
}

void Multy(double A[3][3], double B[3][1], double result[3][1])//计算A*B
{
    result[0][0] = A[0][0] * B[0][0] + A[0][1] * B[1][0] + A[0][2] * B[2][0];
    result[1][0] = A[1][0] * B[0][0] + A[1][1] * B[1][0] + A[1][2] * B[2][0];
    result[2][0] = A[2][0] * B[0][0] + A[2][1] * B[1][0] + A[2][2] * B[2][0];
}

trigonometric_function_paramater fit_trigonometric_function_paramater(double *data_buf, int data_number, double aomiga)
{
    double sc = 0, c2 = 0, s2 = 0, s = 0, c = 0, y = 0, ys = 0, yc = 0, y2 = 0;//需要计算的取值
    int i = 0;
    double ti = 0, yi = 0;
    double value_ = 0, A = 0, B = 0, C = 0;
    trigonometric_function_paramater output_parm = {0};
    for (i = 0; i < data_number; i++) { //循环赋值
        ti = i * aomiga;
        yi = data_buf[i];
        
        sc += sin(ti) * cos(ti);
        c2 += cos(ti) * cos(ti);
        s2 += sin(ti) * sin(ti);
        s += sin(ti);
        c += cos(ti);
        y += yi;
        ys += yi * sin(ti);
        yc += yi * cos(ti);
        y2 += yi * yi;
    }
    
    double A_Matrix[3][3] = {
                                {c2, sc, c}, 
                                {sc, s2, s}, 
                                {c, s, data_number}
                            };
    
    double B_Matrix[3][1] = {
                                {yc},
                                {ys},
                                {y},
                            };
    
    double A_Matrix_Inv[3][3];
    int ret = Gauss(A_Matrix, A_Matrix_Inv, 3); //计算逆矩阵
    if(ret == -1) { //不存在逆矩阵
        output_parm.error_value = 99999999;
        return output_parm;
    }

    double a_vector[3][1];
    Multy(A_Matrix_Inv, B_Matrix, a_vector); //A矩阵的逆矩阵 乘以 B矩阵
    
    A = a_vector[0][0];
    B = a_vector[1][0];
    C = a_vector[2][0];
    
    value_ = y2 + \
        A * A * c2 + \
        B * B * s2 + \
        2.0 * A * B * sc + \
        2.0 * A * C * c + \
        2.0 * B * C * s + \
        (double)(data_number) * C * C - \
        2.0 * A * yc - \
        2.0 * B * ys - \
        2.0 * C * y;
    output_parm.A = A; output_parm.B = B; output_parm.C = C; output_parm.omiga = aomiga; output_parm.error_value = value_;

    return output_parm;
}

trigonometric_function_paramater Solve_fit(double *data_buf, int data_number, int exquisite_number) {
    trigonometric_function_paramater this_parm = {0};
    
    double a = 0.5, b = 1;
    double new_position = 0;
    double value_now = 0, value_new = 0;
    double best_aomiga = 0;
    int i = 0;
    int max_number = exquisite_number;
    int max_count = 0;
    double step = 0;
    a = 2.0 * Pi / (double)(data_number);
    b = 2.0 * Pi;
    step = fabs(b - a) / (double)max_number;
    value_now = fit_trigonometric_function_paramater(data_buf, data_number, a).error_value;
    value_new = value_now;
    new_position = a;
    best_aomiga = a;

    max_count = ceil(0.5 * (double)(max_number));
    for (i = 0; i <= max_count; i++) {//利用梯度下降法
        value_new = fit_trigonometric_function_paramater(data_buf, data_number, new_position).error_value;
        
        if (value_new < value_now) {
            value_now = value_new;
            best_aomiga = new_position;
        }
        new_position += step;
        
    }
    this_parm = fit_trigonometric_function_paramater(data_buf, data_number, best_aomiga);
    
    return this_parm;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
//数据
#include "data.h"

double sin_tab[360 + 1] =
{
     0.000000,
     0.017452,  0.034899,  0.052336,  0.069756,  0.087156,  0.104528,  0.121869,  0.139173,  0.156434,  0.173648,  0.190809,  0.207912,  0.224951,  0.241922,  0.258819,  
     0.275637,  0.292372,  0.309017,  0.325568,  0.342020,  0.358368,  0.374607,  0.390731,  0.406737,  0.422618,  0.438371,  0.453990,  0.469472,  0.484810,  0.500000,  
     0.515038,  0.529919,  0.544639,  0.559193,  0.573576,  0.587785,  0.601815,  0.615661,  0.629320,  0.642788,  0.656059,  0.669131,  0.681998,  0.694658,  0.707107,  
     0.719340,  0.731354,  0.743145,  0.754710,  0.766044,  0.777146,  0.788011,  0.798636,  0.809017,  0.819152,  0.829038,  0.838671,  0.848048,  0.857167,  0.866025,  
     0.874620,  0.882948,  0.891007,  0.898794,  0.906308,  0.913545,  0.920505,  0.927184,  0.933580,  0.939693,  0.945519,  0.951057,  0.956305,  0.961262,  0.965926,  
     0.970296,  0.974370,  0.978148,  0.981627,  0.984808,  0.987688,  0.990268,  0.992546,  0.994522,  0.996195,  0.997564,  0.998630,  0.999391,  0.999848,  1.000000,  
     0.999848,  0.999391,  0.998630,  0.997564,  0.996195,  0.994522,  0.992546,  0.990268,  0.987688,  0.984808,  0.981627,  0.978148,  0.974370,  0.970296,  0.965926,  
     0.961262,  0.956305,  0.951057,  0.945519,  0.939693,  0.933580,  0.927184,  0.920505,  0.913545,  0.906308,  0.898794,  0.891007,  0.882948,  0.874620,  0.866025,  
     0.857167,  0.848048,  0.838671,  0.829038,  0.819152,  0.809017,  0.798636,  0.788011,  0.777146,  0.766044,  0.754710,  0.743145,  0.731354,  0.719340,  0.707107,  
     0.694658,  0.681998,  0.669131,  0.656059,  0.642788,  0.629320,  0.615661,  0.601815,  0.587785,  0.573576,  0.559193,  0.544639,  0.529919,  0.515038,  0.500000,  
     0.484810,  0.469472,  0.453991,  0.438371,  0.422618,  0.406737,  0.390731,  0.374607,  0.358368,  0.342020,  0.325568,  0.309017,  0.292372,  0.275637,  0.258819,  
     0.241922,  0.224951,  0.207912,  0.190809,  0.173648,  0.156434,  0.139173,  0.121869,  0.104528,  0.087156,  0.069756,  0.052336,  0.034900,  0.017452,  0.000000,  
    -0.017452, -0.034899, -0.052336, -0.069756, -0.087156, -0.104528, -0.121869, -0.139173, -0.156434, -0.173648, -0.190809, -0.207912, -0.224951, -0.241922, -0.258819, 
    -0.275637, -0.292372, -0.309017, -0.325568, -0.342020, -0.358368, -0.374607, -0.390731, -0.406737, -0.422618, -0.438371, -0.453990, -0.469472, -0.484810, -0.500000, 
    -0.515038, -0.529919, -0.544639, -0.559193, -0.573576, -0.587785, -0.601815, -0.615661, -0.629320, -0.642788, -0.656059, -0.669131, -0.681998, -0.694658, -0.707107, 
    -0.719340, -0.731354, -0.743145, -0.754710, -0.766044, -0.777146, -0.788011, -0.798636, -0.809017, -0.819152, -0.829038, -0.838671, -0.848048, -0.857167, -0.866025, 
    -0.874620, -0.882948, -0.891007, -0.898794, -0.906308, -0.913545, -0.920505, -0.927184, -0.933580, -0.939693, -0.945519, -0.951057, -0.956305, -0.961262, -0.965926, 
    -0.970296, -0.974370, -0.978148, -0.981627, -0.984808, -0.987688, -0.990268, -0.992546, -0.994522, -0.996195, -0.997564, -0.998630, -0.999391, -0.999848, -1.000000, 
    -0.999848, -0.999391, -0.998630, -0.997564, -0.996195, -0.994522, -0.992546, -0.990268, -0.987688, -0.984808, -0.981627, -0.978148, -0.974370, -0.970296, -0.965926, 
    -0.961262, -0.956305, -0.951057, -0.945519, -0.939693, -0.933580, -0.927184, -0.920505, -0.913545, -0.906308, -0.898794, -0.891007, -0.882948, -0.874620, -0.866025, 
    -0.857167, -0.848048, -0.838671, -0.829038, -0.819152, -0.809017, -0.798636, -0.788011, -0.777146, -0.766044, -0.754710, -0.743145, -0.731354, -0.719340, -0.707107, 
    -0.694658, -0.681998, -0.669131, -0.656059, -0.642788, -0.629320, -0.615661, -0.601815, -0.587785, -0.573576, -0.559193, -0.544639, -0.529919, -0.515038, -0.500000, 
    -0.484810, -0.469472, -0.453991, -0.438371, -0.422618, -0.406737, -0.390731, -0.374607, -0.358368, -0.342020, -0.325568, -0.309017, -0.292372, -0.275637, -0.258819, 
    -0.241922, -0.224951, -0.207912, -0.190809, -0.173648, -0.156434, -0.139173, -0.121869, -0.104528, -0.087156, -0.069756, -0.052336, -0.034900, -0.017452, -0.000000, 
};

int main(int argc, char* argv[])
{
    //拟合数据
    trigonometric_function_paramater parm = Solve_fit(testdata, 7100, 10000);
    printf("A %f B %f C %f omiga %f\n", parm.A, parm.B, parm.C, parm.omiga);
    
    printf("Amp %f\n", sqrt(parm.A * parm.A + parm.B * parm.B));
    printf("Pha %f\n", atan(parm.A / parm.B) * 180 / Pi);
    
    char readbuf[1024];
    char *path = "filter.txt";
    FILE* fp = fopen(path, "w+");
    if(fp == NULL) {
        perror("error: ");
    }
    fseek(fp, 0, SEEK_SET);
    for(int i = 0; i < 720; i++) {
        sprintf((char*)readbuf, "%f\n", parm.A * cos(parm.omiga * i) + parm.B * sin(parm.omiga * i) + parm.C);
        fwrite(readbuf, 1, strlen((char*)readbuf), fp);
    }
    
    fclose(fp);
    
    printf("\n");
    
    //拟合正弦波
    parm = Solve_fit(sin_tab, 361, 100);
    printf("A %f B %f C %f omiga %f\n", parm.A, parm.B, parm.C, parm.omiga);
    
    printf("Amp %f\n", sqrt(parm.A * parm.A + parm.B * parm.B));
    printf("Pha %f %f\n", atan(parm.A / parm.B), atan(parm.A / parm.B) * 180 / Pi);
    
    return 0;
}