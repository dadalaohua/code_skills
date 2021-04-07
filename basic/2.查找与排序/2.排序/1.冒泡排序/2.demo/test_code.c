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

/* 对顺序表L作交换排序（冒泡排序初级版） */
void BubbleSort0(SqList *L)
{ 
	int i,j;
	for(i=1;i<L->length;i++)
	{
		for(j=i+1;j<=L->length;j++)
		{
			if(L->r[i]>L->r[j])
			{
				 swap(L,i,j);/* 交换L->r[i]与L->r[j]的值 */
			}
		}
	}
}

/* 对顺序表L作冒泡排序 */
void BubbleSort(SqList *L)
{ 
	int i,j;
	for(i=1;i<L->length;i++)
	{
		for(j=L->length-1;j>=i;j--)  /* 注意j是从后往前循环 */
		{
			if(L->r[j]>L->r[j+1]) /* 若前者大于后者（注意这里与上一算法的差异）*/
			{
				 swap(L,j,j+1);/* 交换L->r[j]与L->r[j+1]的值 */
			}
		}
	}
}

/* 对顺序表L作改进冒泡算法 */
void BubbleSort2(SqList *L)
{ 
	int i,j;
	Status flag=TRUE;			/* flag用来作为标记 */
	for(i=1;i<L->length && flag;i++) /* 若flag为true说明有过数据交换，否则停止循环 */
	{
		flag=FALSE;				/* 初始为False */
		for(j=L->length-1;j>=i;j--)
		{
			if(L->r[j]>L->r[j+1])
			{
				 swap(L,j,j+1);	/* 交换L->r[j]与L->r[j+1]的值 */
				 flag=TRUE;		/* 如果有数据交换，则flag为true */
			}
		}
	}
}

#define N 9
int main(int argc, char* argv[])
{ 
   int i;
   
   /* int d[N]={9,1,5,8,3,7,4,6,2}; */
   int d[N]={50,10,90,30,70,40,80,60,20};
   /* int d[N]={9,8,7,6,5,4,3,2,1}; */

   SqList l0,l1,l2,l3,l4,l5,l6,l7,l8,l9,l10;
   
   for(i=0;i<N;i++)
     l0.r[i+1]=d[i];
   l0.length=N;
   l1=l2=l0;
   printf("排序前:\n");
   print(l0);

   printf("初级冒泡排序:\n");
   BubbleSort0(&l0);
   print(l0);
   
   printf("冒泡排序:\n");
   BubbleSort(&l1);
   print(l1);
   
   printf("改进冒泡排序:\n");
   BubbleSort2(&l2);
   print(l2);
    
    return 0;
}