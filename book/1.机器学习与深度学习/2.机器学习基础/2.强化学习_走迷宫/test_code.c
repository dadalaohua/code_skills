/********************************************/
/*         qlearning.c                      */
/*   强化学习（Q学习）的例题程序            */
/*   学习如何探索迷宫                       */
/********************************************/
#include <stdio.h>
#include <stdlib.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/* 符号常数的定义            */
#define GENMAX      1000    /*学习的重复次数*/
#define NODENO      15      /*Q值的节点数*/
#define ALPHA       0.1     /*学习系数*/
#define GAMMA       0.9     /*折扣率*/
#define EPSILON     0.3     /*确定行动选择的随机性*/
#define SEED        32767   /*随机数的seed*/

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

/****************************/
/*     rand100()函数        */
/*返回0～100的随机函数      */
/****************************/
int rand100()
{
    int rnd ;

    /*去除随机数的最大值*/
    while((rnd=rand())==RAND_MAX) ;
    /*随机数的计算*/ 
    return (int)((double)rnd/RAND_MAX*101) ;
}

/****************************/
/*       updateq()函数      */
/*       更新Q值            */
/****************************/
int updateq(int s,int qvalue[NODENO])
{
    int qv ;/*要更新的Q值*/
    int qmax ;/*Q值的最大值*/
    
    /*最末端的情形*/
    if(s > 6)
    {
        if(s == 14)/*给予奖赏*/
        qv=qvalue[s]+ALPHA*(1000-qvalue[s]) ;
        /*给予奖赏的节点Q值增加*/
        /*其他节点的Q值追加时*/
        /*去掉下面2行的注释*/
        //  else if(s==11)/*给予奖赏*/
        //   qv=qvalue[s]+ALPHA*(500-qvalue[s]) ;
        else/*无奖赏*/
        qv=qvalue[s] ;
    }
    /*最末端之外*/
    else{
        if((qvalue[2*s+1])>(qvalue[2*s+2])) 
            qmax=qvalue[2*s+1];
        else
            qmax=qvalue[2*s+2];
        
        qv=qvalue[s]+ALPHA*(GAMMA*qmax-qvalue[s]) ;
    }

    return qv ;
}

/****************************/
/*        selecta()函数     */
/*        行动选择          */
/****************************/
int selecta(int olds,int qvalue[NODENO])
{
    int s ;
    
    /*基于ε-greedy方法的行动选择*/
    if(rand1()<EPSILON){
        /*随机行动*/
        if(rand01()==0)
            s=2*olds+1 ;
        else
            s=2*olds+2 ;
    }
    else{
        /*选择Q值的最大值*/
        if((qvalue[2*olds+1])>(qvalue[2*olds+2])) 
            s=2*olds+1;
        else
            s=2*olds+2;
    }
    
    return s ;
}

/****************************/
/*    printqvalue()函数     */
/*    输出Q值               */
/****************************/
void printqvalue(int qvalue[NODENO])
{
    int i ;
    
    for (i = 1; i < NODENO; ++i)
        printf("%d\t", qvalue[i]);
    
    printf("\n");
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{ 
    int i;
    int s;/*状态*/
    int t;/*时刻*/
    int qvalue[NODENO];/*Q值*/

    srand(SEED);/*随机数的初始化*/

    /*Q值的初始化*/
    for(i=0;i<NODENO;++i)
        qvalue[i]=rand100();
    
    printqvalue(qvalue);

    /*学习的主体*/
    for(i=0;i<GENMAX;++i) {
        s=0;/*行动的初始状态*/
        
        for(t=0;t<3;++t){/*到最末端为止重复进行*/
            /*行动选择*/
            s = selecta(s,qvalue) ;
            
            /*Q值的更新*/
            qvalue[s] = updateq(s,qvalue) ;
        }
        
        /*Q值的输出*/
        printqvalue(qvalue) ;
    }

    return 0;
}