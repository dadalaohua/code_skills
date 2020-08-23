/****************************************/
/*                aco.c                 */
/*  蚁群最优化方法(aco)程序             */
/*   基于aco学习最优值                  */
/****************************************/
#include <stdio.h>
#include <stdlib.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*   符号常数的定义                 */
#define NOA 10 /*蚂蚁的个体数*/
#define ILIMIT 50 /*循环次数*/
#define Q 3 /*信息素更新的常数*/
#define RHO 0.8 /*挥发常数*/
#define STEP 10 /*路程的步数*/
#define EPSILON 0.15 /*确定行动选择的随机性*/
#define SEED 32768 /*随机数的Seed*/

/****************************/
/*     rand1()函数          */
/*返回0～1的实数的随机函数  */
/****************************/
double rand1()
{
    /*随机数的计算*/ 
    return (double)rand()/RAND_MAX;
}

/****************************/
/*     rand01()函数         */
/*返回0、1的随机函数        */
/****************************/
int rand01()
{
    int rnd ;

    /*去除随机数的最大值*/
    while((rnd = rand())==RAND_MAX) ;
    /*随机数的计算*/ 
    return (int)((double)rnd/RAND_MAX*2) ;
}

/**************************/
/*  printmstep()函数      */
/*   显示蚂蚁的行动       */
/**************************/
void printmstep(int mstep[NOA][STEP])
{
    int i,j ;

    printf("*mstep\n");
    for(i=0;i<NOA;++i){
        for(j=0;j<STEP;++j)
            printf("%d ",mstep[i][j]);
        printf("\n") ;
    }
}

/**************************/
/*    printp()函数        */
/*   显示信息素           */
/**************************/
void printp(double pheromone[2][STEP]) 
{
    int i,j ;

    for(i=0;i<2;++i){
        for(j=0;j<STEP;++j)
            printf("%4.2lf ",pheromone[i][j]);
        printf("\n") ;
    }
}

/**************************/
/*    update()函数        */
/*    更新信息素          */
/**************************/
void update(int cost[2][STEP]
        ,double pheromone[2][STEP]
        ,int mstep[NOA][STEP] )
{
    int m ;/*蚂蚁个体的号码*/
    int lm ;/*蚂蚁步行的距离*/
    int i,j ;
    double sum_lm=0;/*蚂蚁步行的总体距离*/
 
    /*信息素的挥发*/
    for(i=0;i<2;++i)
        for(j=0;j<STEP;++j)
            pheromone[i][j]*=RHO;

    /*蚂蚁的覆盖*/
    for(m=0;m<NOA;++m){
        /*个体m的移动距离lm的计算*/
        lm=0;
        for(i=0;i<STEP;++i)
            lm+=cost[mstep[m][i]][i];

        /*信息素的覆盖*/
        for(i=0;i<STEP;++i)
            pheromone[mstep[m][i]][i]+=Q*(1.0/lm);
    
        sum_lm+=lm;
    }
    
    /*蚂蚁步行的平均距离的输出*/
    printf("%lf\n",sum_lm/NOA) ;
}

/**************************/
/*    walk()函数          */
/*    使蚂蚁步行          */
/**************************/
void walk(int cost[2][STEP]
        ,double pheromone[2][STEP],int mstep[NOA][STEP])
{
    int m ;/*蚂蚁个体的号码*/
    int s ;/*蚂蚁现在所处的位置*/

    for(m=0;m<NOA;++m){
        for(s=0;s<STEP;++s){
            /*基于ε-greedy的行动选择*/
            if((rand1()<EPSILON)
            ||(abs(pheromone[0][s]-pheromone[1][s])<1e-9))
            {/*随机行动*/
                mstep[m][s]=rand01() ;
            }
            else{/*基于信息素的选择*/
                if(pheromone[0][s]>pheromone[1][s]) 
                  mstep[m][s]=0 ;
                else
                  mstep[m][s]=1 ;
            }
        }
    }
    /*输出蚂蚁的行动*/
    printmstep(mstep) ;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{ 
    int cost[2][STEP]={/*各步的代价（距离）*/
        {1,1,1,1,1,1,1,1,1,1},
        {5,5,5,5,5,5,5,5,5,5}};
    double pheromone[2][STEP]={0} ;/*各步的信息素量*/
    int mstep[NOA][STEP] ;/*蚂蚁走过的过程*/
    int i;/*循环次数的控制*/

    /*随机数的初始化*/
    srand(SEED) ;

    /*最优化的主体*/
    for(i=0;i<ILIMIT;++i){
        /*信息素的状态的输出*/
        printf("%d:\n",i);
        printp(pheromone);
        /*使蚂蚁步行*/
        walk(cost,pheromone,mstep);
        /*更新信息素*/
        update(cost,pheromone,mstep);
    }
    /*信息素状态的输出*/
    printf("%d:\n",i) ;
    printp(pheromone) ;

    return 0;
}