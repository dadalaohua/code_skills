#include <stdio.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status; 

#define MAXSIZE 10000  /* 用于要排序数组个数最大值，可根据需要修改 */
typedef struct
{
	int r[MAXSIZE+1];	/* 用于存储要排序数组，r[0]用作哨兵或临时变量 */
	int length;			/* 用于记录顺序表的长度 */
}SqList;

/* 交换L中数组r的下标为i和j的值 */
void swap(SqList *L,int i,int j) 
{ 
	int temp=L->r[i]; 
	L->r[i]=L->r[j]; 
	L->r[j]=temp; 
}

void print(SqList L)
{
	int i;
	for(i=1;i<L.length;i++)
		printf("%d,",L.r[i]);
	printf("%d",L.r[i]);
	printf("\n");
}

/* 对顺序表L作希尔排序 */
void ShellSort(SqList *L)
{
	int i,j,k=0;
	int increment=L->length;
	do
	{
		increment=increment/3+1;/* 增量序列 */
		for(i=increment+1;i<=L->length;i++)
		{
			if (L->r[i]<L->r[i-increment])/*  需将L->r[i]插入有序增量子表 */ 
			{ 
				L->r[0]=L->r[i]; /*  暂存在L->r[0] */
				for(j=i-increment;j>0 && L->r[0]<L->r[j];j-=increment)
					L->r[j+increment]=L->r[j]; /*  记录后移，查找插入位置 */
				L->r[j+increment]=L->r[0]; /*  插入 */
			}
		}
		printf("	第%d趟排序结果: ",++k);
		print(*L);
	}
	while(increment>1);

}

#define N 9
int main(int argc, char* argv[])
{ 
   int i;
   
   /* int d[N]={9,1,5,8,3,7,4,6,2}; */
   int d[N]={50,10,90,30,70,40,80,60,20};
   /* int d[N]={9,8,7,6,5,4,3,2,1}; */

   SqList l0;
   
   for(i=0;i<N;i++)
     l0.r[i+1]=d[i];
   l0.length=N;

   printf("排序前:\n");
   print(l0);

   printf("希尔排序:\n");
   ShellSort(&l0);
   print(l0);
    
    return 0;
}