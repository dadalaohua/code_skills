#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


/************************************************************************/
/*                                                                      */
/************************************************************************/
#define MVF_LENGTH  5
typedef float E_SAMPLE;
/*定义移动平均寄存器历史状态*/
typedef struct  _t_MAF
{
    E_SAMPLE buffer[MVF_LENGTH];
    E_SAMPLE sum;
    int index;
}t_MAF;

void moving_average_filter_init(t_MAF * pMaf)
{
    pMaf->index = -1;
    pMaf->sum   = 0;
}

E_SAMPLE moving_average_filter(t_MAF * pMaf,E_SAMPLE xn)
{
    E_SAMPLE yn=0;
    int i=0;

    if(pMaf->index == -1)
    {
        for(i = 0; i < MVF_LENGTH; i++)
        {
            pMaf->buffer[i] = xn;
        }
        pMaf->sum   = xn*MVF_LENGTH;
        pMaf->index = 0;
    }
    else
    {
        pMaf->sum     -= pMaf->buffer[pMaf->index];
        pMaf->buffer[pMaf->index] = xn;
        pMaf->sum     += xn;
        pMaf->index++;
        if(pMaf->index>=MVF_LENGTH)
            pMaf->index = 0;
    }
    yn = pMaf->sum/MVF_LENGTH;
    return yn;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define SAMPLE_RATE 500.0f
#define SAMPLE_SIZE 256
#define PI 3.415926f

int main(int argc, char* argv[])
{
    E_SAMPLE rawSin[SAMPLE_SIZE];
    E_SAMPLE outSin[SAMPLE_SIZE];

    E_SAMPLE rawSquare[SAMPLE_SIZE];
    E_SAMPLE outSquare[SAMPLE_SIZE];
    t_MAF mvf;

    /*正弦信号测试*/
    FILE *pFile=fopen("./simulationSin.csv","wt+");
    if(pFile==NULL)
    {
        printf("simulationSin.csv opened failed");
        return -1;
    }
    for(int i=0;i<SAMPLE_SIZE;i++)
    {
        rawSin[i] = 100*sin(2*PI*20*i/SAMPLE_RATE)+rand()%30;
    }

    /*初始化*/
    moving_average_filter_init(&mvf);
    /*滤波*/
    for(int i=0;i<SAMPLE_SIZE;i++)
    {
        outSin[i]=moving_average_filter(&mvf,rawSin[i]);
    }

    for(int i=0;i<SAMPLE_SIZE;i++)
    {
        fprintf(pFile,"%f,",rawSin[i]);
    }

    fprintf(pFile,"\n");
    for(int i=0;i<SAMPLE_SIZE;i++)
    {
        fprintf(pFile,"%f,",outSin[i]);
    }

    fclose(pFile);

    /*方波测试*/
    pFile=fopen("./simulationSquare.csv","wt+");
    if(pFile==NULL)
    {
        printf("simulationSquare.csv opened failed");
        return -1;
    }
    
    for(int i=0;i<SAMPLE_SIZE/4;i++)
    {
        rawSquare[i] = 5+rand()%10;
    }
    for(int i=SAMPLE_SIZE/4;i<3*SAMPLE_SIZE/4;i++)
    {
        rawSquare[i] = 100+rand()%10;
    }
    for(int i=3*SAMPLE_SIZE/4;i<SAMPLE_SIZE;i++)
    {
        rawSquare[i] = 5+rand()%10;
    }
    
    /*初始化*/
    moving_average_filter_init(&mvf);
    /*滤波*/
    for(int i=0;i<SAMPLE_SIZE;i++)
    {
        outSquare[i]=moving_average_filter(&mvf,rawSquare[i]);
    }

    for(int i=0;i<SAMPLE_SIZE;i++)
    {
        fprintf(pFile,"%f,",rawSquare[i]);
    }

    fprintf(pFile,"\n");
    for(int i=0;i<SAMPLE_SIZE;i++)
    {
        fprintf(pFile,"%f,",outSquare[i]);
    }

    fclose(pFile);
    
    return 0;
}