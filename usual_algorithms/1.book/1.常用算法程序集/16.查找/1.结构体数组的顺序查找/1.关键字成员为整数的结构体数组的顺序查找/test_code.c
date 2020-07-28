#include <stdio.h>

#define STRU    struct student
#define KEY     age

STRU
{
    int    num;
    char   name[8];
    char   sex;
    int    age;
    double score;
};
    
/*******************************************************************************
* Function Name  : isech
* Description    : 关键字成员为整数的结构体数组的顺序查找
* Input          : STRU  p[]: 结构体类型STRU的一维数组
                   int k: 在数组p中进行查找的起始下标，要求k>=0
                   int m: 在数组p中进行查找的终止下标，要求m不大于数组p的最大下标
                   int a: 存放查找的关键字值的下限值
                   int b: 存放查找的关键字值的上限值
* Output         : None.
* Return         : int i：函数返回关键字值在区间[a,b]内的第一次发现的元素下标。在主函数中
                          在主函数中可以根据返回的这个下标值继续向后查找，
                          从而可以找出关键字值在[a,b]内的所有元素。
                          若在指定范围(即[k,m])内找不到关键字值在[a,b]内的元素,
                          则返回的函数值为-1
*******************************************************************************/
int isech(STRU  p[], int k, int m, int a, int b)
{
    int i;
    
    i = k;
    
    while((i <= m) && ((p[i].KEY < a) || (p[i].KEY > b)))
        i = i + 1;

    if(i > m)
        return(-1);

    return(i);
}

int main(int argc, char* argv[])
{ 
    int i, q;
    int a, b;
    static STRU p[10] = {
        {101, "Zhang",'M', 19, 95.6},
        {102, "Wang", 'F', 18, 92.4},
        {103, "Zhao", 'M', 19, 85.7},
        {104, "Li",   'M', 20, 96.3},
        {105, "Gou",  'M', 19, 90.2},
        {106, "Lin",  'M', 18, 91.5},
        {107, "Ma",   'F', 17, 98.7},
        {108, "Zhen", 'M', 21, 90.1},
        {109, "Xu",   'M', 19, 89.8},
        {110, "Mao",  'F', 18, 94.9}};
        
    a = 18;
    b = 20;
    i = 0;
    
    printf("\n");
    
    do
    { 
        q = isech(p, i, 9, a, b);
        
        if (q != -1)
          printf("%-5d%-10s%-4c%-6d%-7.2f\n",p[q].num,
             p[q].name, p[q].sex, p[q].age, p[q].score);
             
        i = q + 1;
    }
    while (q!=-1);
    
    printf("\n");
    
    return 0;
}