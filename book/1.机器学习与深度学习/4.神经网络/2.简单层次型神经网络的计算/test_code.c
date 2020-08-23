/*********************************************************/
/*                   nn.c                                */
/* 简单层次型神经网络的计算                              */
/* 1个输出的网络的计算（无学习）                         */
/*********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*符号常数的定义*/
#define INPUTNO 2  /*输入层的神经元数*/ 
#define HIDDENNO 2  /*中间层的神经元数*/ 
#define MAXINPUTNO 100    /*数据的最大个数*/ 

/**********************/
/*  getdata()函数     */
/*    读入学习数据    */
/**********************/
int getdata(double e[][INPUTNO])
{
 int n_of_e=0 ;/*数据集的个数*/
 int j=0 ;/*循环的控制用*/

    /*数据的输入*/
    while(scanf("%lf",&e[n_of_e][j])!=EOF){
        ++ j;
        if(j>=INPUTNO){/*下一个数据*/
            j=0;
            ++n_of_e;
        }
    }
    return n_of_e ;
}

//**********************/
/*    initwh()函数     */
/*中间层权重的初始化   */
/**********************/
void initwh(double wh[HIDDENNO][INPUTNO+1])
{
    /*给权重固定的数*/
    wh[0][0]=-2;
    wh[0][1]=3;
    wh[0][2]=-1;
    wh[1][0]=-2;
    wh[1][1]=1;
    wh[1][2]=0.5;
}

/**********************/
/*    initwo()函数    */
/*输出层权重的初始化  */
/**********************/
void initwo(double wo[HIDDENNO+1])
{
    /*给权重固定的数*/
    wo[0]=-60;
    wo[1]=94;
    wo[2]=-1;
} 

/*******************/
/* f()函数         */
/* 传递函数        */
/*******************/
double f(double u)
{
    /*阶梯函数的计算*/
    if(u>=0) return 1.0 ;
    else return 0.0 ;

    /*sigmoid函数的计算*/
    // return 1.0/(1.0+exp(-u)) ;
}
/**********************/
/*  forward()函数     */
/*  前向计算          */
/**********************/
double forward(double wh[HIDDENNO][INPUTNO+1]
                ,double wo[HIDDENNO+1],double hi[],double e[INPUTNO])
{
    int i,j ;/*循环的控制*/
    double u ;/*加权和的计算*/
    double o ;/*输出的计算*/

    /*hi的计算*/
    for(i=0;i<HIDDENNO;++i){
        u=0 ;/*求取加权和*/
        for(j=0;j<INPUTNO;++j)
            u+=e[j]*wh[i][j] ; 
        u-=wh[i][j] ;/*阈值的处理*/
        hi[i]=f(u) ;
    }
    /*输出o的计算*/
    o=0 ;
    for(i=0;i<HIDDENNO;++i)
        o+=hi[i]*wo[i] ;
    o-=wo[i] ;/*阈值的处理*/

    return f(o) ;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{ 
    double wh[HIDDENNO][INPUTNO+1] ;/*中间层的权重*/
    double wo[HIDDENNO+1] ;/*输出层的权重*/
    double e[MAXINPUTNO][INPUTNO] ;/*数据集*/
    double hi[HIDDENNO+1] ;/*中间层的输出*/
    double o ;/*输出*/
    int i,j ;/*循环的控制*/
    int n_of_e ;/*数据个数*/

    /*权重的初始化*/
    initwh(wh) ;
    initwo(wo) ;

    /*读入输入数据*/
    n_of_e=getdata(e) ;
    printf("数据的个数:%d\n",n_of_e) ;

    /*计算的主体*/
    for(i=0;i<n_of_e;++i){
        printf("%d ",i) ;
        for(j=0;j<INPUTNO;++j)
            printf("%lf ",e[i][j]);
        o=forward(wh,wo,hi,e[i]);
        printf("%lf\n",o) ;
    }

    return 0;
}