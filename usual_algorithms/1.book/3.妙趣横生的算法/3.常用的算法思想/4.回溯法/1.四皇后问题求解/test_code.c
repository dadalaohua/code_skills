#include <stdio.h>
#include <stdlib.h>

/****************************/
int count = 0;                            /*记录四皇后问题解的个数*/

int isCorrect(int i,int j,int (*Q)[4])
{
    int s,t;
    for(s=i,t=0;t<4;t++)
    if(Q[s][t]==1 && t!=j)return 0;         /*判断行*/

    for(t=j,s=0;s<4;s++)
    if(Q[s][t]==1 && s!=i)return 0;         /*判断列*/

    for(s=i-1,t=j-1;s>=0&&t>=0;s--,t--)
    if(Q[s][t] == 1)return 0;               /*判断左上方*/
    
    for(s=i+1,t=j+1;s<4&&t<4;s++,t++)
    if(Q[s][t] == 1) return 0;              /*判断右下方*/

    for(s=i-1,t=j+1;s>=0&&t<4;s--,t++)
    if(Q[s][t] == 1) return 0;              /*判断右上方*/

    for(s=i+1,t=j-1;s<4&&t>=0;s++,t--)
    if(Q[s][t] == 1) return 0;              /*判断左下方*/

    return 1;                               /*否则返回1*/
}

void Queen(int j,int (*Q)[4]){
    int i , k;
    if(j==4)
    {                                        /*得到了一个解*/
        for(i=0;i<4;i++)
        {
            for(k=0;k<4;k++)
                printf("%d ",Q[i][k]);
            printf("\n");
        }
        printf("\n");
        
        count++;
        
        return;
        
    }
    for(i=0;i<4;i++)
    {
        if(isCorrect(i,j,Q))                /*如果Q[i][j]可以放置皇后*/
        {
        
            Q[i][j] = 1;                    /*放置皇后*/
            Queen(j+1,Q) ;                  /*深度优先搜索解空间树*/
            Q[i][j] = 0;
        }
    }
}

/****************************/

int main(int argc, char* argv[])
{
    int Q[4][4];
    int i,j;
    
    for( i=0;i<4;i++)
       for( j=0;j<4;j++)
            Q[i][j] = 0;                /*初始化数组Q*/
        
    Queen(0,Q);                         /*执行四皇后求解*/
    
    printf("The number of the answers of FOUR_QUEEN are %d",count);
    
    printf("\n");
    
    return 0;
}
