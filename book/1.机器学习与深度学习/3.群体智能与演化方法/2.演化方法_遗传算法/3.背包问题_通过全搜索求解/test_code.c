/*************************************/
/*              direct.c             */
/*通过全搜索方法求解背包问题         */
/*************************************/
#include <stdio.h>
#include <stdlib.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*  符号常数的定义                 */
#define MAXVALUE 100 /*重量和价值的最大值*/
#define N 30 /*行李的个数*/
#define WEIGHTLIMIT (N*MAXVALUE/10)
             /*重量限制*/
#define SEED 32768 /*随机数的seed*/

/************************************************************************/
/*                                                                      */
/************************************************************************/
/****************************/
/*       pow2n()函数        */
/*       2的连乘            */
/****************************/
int pow2n(int n)
{
    int pow=1;
    for(;n>0;--n)
        pow*=2;
    return pow;
}

/****************************/
/*       calcval()函数      */
/*       计算评价值         */
/****************************/
int calcval(int parcel[N][2],int i)
{
    int pos ;/*指定基因位点*/
    int value=0 ;/*评价值*/
    int weight=0 ;/*重量*/

    /*调查各基因位点计算其重量和评价值*/
    for(pos=0;pos<N;++pos){
        weight+=parcel[pos][0]*((i>>pos)&0x1);
        value+=parcel[pos][1]*((i>>pos)&0x1);
    }
    /*致死基因的处理*/
    if(weight>=WEIGHTLIMIT)
        value=0;
    
    return value;
}

/****************************/
/*       solve()函数        */
/*       搜索的主体         */
/****************************/
int solve(int parcel [N][2])
{
    int i ;/*循环控制*/
    int limit ;/*搜索的上限*/
    int maxvalue=0 ;/*评价值的最大值*/
    int value ;/*评价值*/
    int solution ;/*候选解*/

    /*搜索范围的设定*/
    limit=pow2n(N);
    /*解的搜索*/
    for(i=0;i<limit;++i){
        /*计算评价值*/
        value=calcval(parcel,i);
        /*最大值的更新*/
        if(value>maxvalue){
            maxvalue=value;
            solution=i;
            printf("*** maxvalue %d\n",maxvalue);
        }
    }
    return solution ;
}

/****************************/
/*       prints()函数       */
/*      输出候选解          */
/****************************/
void prints(int solution)
{
    int i ;
    for(i=0;i<N;++i)
        printf("%1d ",(solution>>i)&0x1) ;
    printf("\n") ;
}

/****************************/
/*      initparcel()函数    */
/*      行李的初始化        */
/****************************/
void initparcel(int parcel [N][2])
{
    int i=0 ;
    
    while((i<N) && 
            (scanf("%d %d",&parcel[i][0],&parcel[i][1])!=EOF)){
        ++i ;
    }
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{ 
    int parcel[N][2] ;/*行李*/
    int solution=0xfff ;/*解*/

    /*行李的初始化*/
    initparcel(parcel) ;
    /*搜索的主体*/
    solution=solve(parcel) ;
    /*解的输出*/
    prints(solution) ;

    return 0;
}