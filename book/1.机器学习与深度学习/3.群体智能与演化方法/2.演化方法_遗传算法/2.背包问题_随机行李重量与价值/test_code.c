/*****************************************************/
/*                  kpga.c丂丂                       */
/*          基于GA的背包问题的求解程序               */
/*          基于GA，搜索背包问题的最优解             */
/*****************************************************/
#include <stdio.h>
#include <stdlib.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*符号常数的定义*/
#define MAXVALUE 100 /*重量和价值的最大值*/
#define N 30 /*行李个数*/
#define WEIGHTLIMIT (N*MAXVALUE/4) /*重量限制*/
#define POOLSIZE 30 /*染色体个数*/
#define LASTG 50    /*终止后代*/
#define MRATE 0.01  /*突变的概率*/
#define SEED 32767    /*随机数的seed*/
#define YES 1   /*yes对应的整数值*/
#define NO 0    /*no对应的整数值*/

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*全局变量（行李数据）*/
int parcel[N][2] ;/*行李*/

/************************************************************************/
/*                                                                      */
/************************************************************************/

/************************/
/*     rndn()函数       */
/*    n以下随机数的生成 */
/************************/
int rndn(int l)
{
    int rndno ;/*生成的随机数*/

    while((rndno=((double)rand()/RAND_MAX)*l)==l) ;

    return rndno;
}

/**********************************/
/*     randdata()函数             */
/*返回MAXVALUE以下的整数的随机函数*/
/**********************************/
int randdata()
{
    int rnd ;

    /*去除随机数的最大值*/
    while((rnd=rand())==RAND_MAX) ;
    /*随机数的计算*/ 
    return (int)((double)rnd/RAND_MAX*MAXVALUE+1);
}

/****************************/
/*      initparcel()函数    */
/*      行李的初始化        */
/****************************/
void initparcel()
{
    int i=0;
    
    for(i = 0; i < N; ++i)
    {
        parcel[i][0] = randdata();
        parcel[i][1] = randdata();
    }
    
     for(i = 0; i < N; ++i)
        printf("%d %d\n", parcel[i][0], parcel[i][1]) ;
}

/***********************/
/*   initpool()函数    */
/*   生成初始染色体集合*/
/***********************/
void initpool(int pool[POOLSIZE][N])
{
    int i, j;/* 循环控制变量 */

    for(i=0;i<POOLSIZE;++i)
        for(j=0;j<N;++j)
            pool[i][j]=rndn(2) ;
}

/************************/
/*   evalfit()函数      */
/*   计算评价值         */
/************************/
int evalfit(int g[])
{
     int pos ;/*指定基因位点*/
     int value=0 ;/*评价值*/
     int weight=0 ;/*重量*/

     /*调查各个基因位点计算重量和评价值*/
     for(pos=0;pos<N;++pos){
        weight+=parcel[pos][0]*g[pos];
        value+=parcel[pos][1]*g[pos];
     }
     /*致死基因的处理*/
     if(weight>=WEIGHTLIMIT) value=0 ;
        return value;
}

/************************/
/*   selectng()函数     */
/*   选择下一代         */
/************************/
void selectng(int ngpool[POOLSIZE*2][N]
              ,int pool[POOLSIZE][N]) 
{
    int i,j,c ;/* 循环控制参数 */
    int totalfitness=0 ;/*适应度的总计值*/
    int roulette[POOLSIZE*2] ;/*存放适应度*/
    int ball ;/* 球（选择位置的数值）*/
    int acc=0 ;/*适应度的累积值*/

    /*循环进行选择*/
    for(i=0;i<POOLSIZE;++i){
        /* 生成轮盘 */
        totalfitness=0 ;
        for(c=0;c<POOLSIZE*2;++c){
            roulette[c]=evalfit(ngpool[c]) ;
            /*计算适应度的总计值*/
            totalfitness+=roulette[c] ;
        }
        /*选择一个染色体*/
        ball=rndn(totalfitness) ;
        acc=0 ;
        for(c=0;c<POOLSIZE*2;++c){
            acc+=roulette[c] ;/*累积评价值*/
            if(acc>ball) break ;/*对应的基因*/
        }

        /*染色体的复制*/
        for(j=0;j<N;++j){
            pool[i][j]=ngpool[c][j] ;
        }
    }
}

/************************/
/*   selectp()函数      */
/*    父代的选择        */
/************************/
int selectp(int roulette[POOLSIZE],int totalfitness)
{
    int i ;/* 循环的控制变量 */
    int ball ;/* 球（选择位置的数值）*/
    int acc=0 ;/*评价值的累积值*/

    ball=rndn(totalfitness) ;
    for(i=0;i<POOLSIZE;++i){
        acc+=roulette[i] ;/*评价值的累积*/
        if(acc>ball) break ;/*对应的基因*/
    }
    return i ;
}

/************************/
/*  crossing()函数      */
/* 特定2染色体的交叉    */
/************************/
void crossing(int m[],int p[],int c1[],int c2[])
{
    int j ;/* 循环控制变量 */
    int cp ;/*交叉的点*/

    /*确定交叉点*/
    cp =rndn(N) ;

    /*复制前半部分*/
    for(j=0;j<cp;++j){
        c1[j]=m[j] ;
        c2[j]=p[j] ;
    }
    /*复制后半部分*/
    for(;j<N;++j){
        c2[j]=m[j];
        c1[j]=p[j];
    }
}

/************************/
/*   mating()函数       */
/*        交叉          */
/************************/
void mating(int pool[POOLSIZE][N]
           ,int ngpool[POOLSIZE*2][N])
{
    int i ;/* 循环的控制变量 */
    int totalfitness=0 ;/*评价值的总计值*/
    int roulette[POOLSIZE] ;/*存放评价值*/
    int mama,papa ;/*父代的基因的号码*/

    /* 生成轮盘 */
    for(i=0;i<POOLSIZE;++i){
        roulette[i]=evalfit(pool[i]) ;
        /* 计算评价值的总计值*/
        totalfitness+=roulette[i] ;
    }

    /*选择和交叉的循环*/
    for(i=0;i<POOLSIZE;++i){
        do{/*父代的选择*/
            mama=selectp(roulette,totalfitness);
            papa=selectp(roulette,totalfitness);
        }while(mama==papa) ;/*删除重复的*/

        /*特定2染色体的交叉*/
        crossing(pool[mama],pool[papa]
                ,ngpool[i*2],ngpool[i*2+1]);  
    }
}

/************************/
/*   notval()函数       */
/*   真值的反转         */
/************************/
int notval(int v)
{
    if(v==YES)
        return NO;
    else
        return YES;
}

/***********************/
/*   mutation()函数    */
/*   突变              */
/***********************/
void mutation(int ngpool[POOLSIZE*2][N])
{
    int i,j ;/* 循环的控制变量 */

    for(i=0;i<POOLSIZE*2;++i)
        for(j=0;j<N;++j)
            if((double)rndn(100)/100.0<=MRATE)
                /*反转的突变*/
                ngpool[i][j]=notval(ngpool[i][j]);
}

/***********************/
/*   printp()函数      */
/*   输出结果          */
/***********************/
void printp(int pool[POOLSIZE][N])
{
    int i,j ;/* 循环的控制变量 */
    int fitness ;/* 评价值 */
    double totalfitness=0 ;/* 评价值的总计值 */
    int elite,bestfit=0 ;/*精英基因的处理用变量*/

    for(i=0;i<POOLSIZE;++i){
        for(j=0;j<N;++j)
            printf("%1d",pool[i][j]);
        
        fitness=evalfit(pool[i]);
        printf("\t%d\n",fitness);
        
        if(fitness>bestfit){/*精英解*/
            bestfit=fitness ;
            elite=i ;
        }
        totalfitness+=fitness ;
    }
    /*输出精英解的评价值*/
    printf("%d\t%d \t", elite, bestfit) ;
    /*输出平均评价值*/
    printf("%lf\n",totalfitness/POOLSIZE) ;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{ 
    int pool[POOLSIZE][N] ; /*染色体集合*/
    int ngpool[POOLSIZE*2][N] ; /*下一代染色体集合*/
    int generation;/* 现在的代数 */

    /*随机数的初始化*/
    srand(SEED) ;

    /*行李的初始化*/
    initparcel() ;

    /*生成初始染色体集合*/
    initpool(pool) ;

    /*循环直至终止子代*/
    for(generation=0;generation<LASTG;++generation){
        printf("%d代数\n",generation) ;
        mating(pool,ngpool) ;/*交叉*/
        mutation(ngpool) ;/*突变*/
        selectng(ngpool,pool) ;/*选择下一子代*/
        printp(pool) ;/*输出结果*/
    }

    return 0;
}